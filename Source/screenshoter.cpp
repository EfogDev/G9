#include "screenshoter.h"
#include "qtransparentlabel.h"
#include "math.h"
#include "QSound"

/**************************************/
/*           FullScreenshoter         */
/**************************************/

void FullScreenshoter::makeScreenshot() {
    QScreen* screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(QApplication::desktop()->winId());

    if (settings.autoSave) {
        saveToFile(settings.saveDir, settings.saveFormat, settings.saveQuality);
    }

    if (settings.autoCopy) {
        QApplication::clipboard()->setImage(screenshot.toImage());
    }

    playSound();
}

void FullScreenshoter::saveToFile(QString filename, QString format, int quality) {
    QDir directory;
    if (!directory.exists(filename))
        directory.mkdir(filename);

    QDateTime time = QDateTime::currentDateTime();

    if (format == "jpg" || format == "gif")
        screenshot.save(filename + "/Screenshot " + time.toString("dd.MM.yyyy hh:mm:ss") + "." + format, format.toUtf8().constData(), quality);
    else
        screenshot.save(filename + "/Screenshot " + time.toString("dd.MM.yyyy hh:mm:ss") + "." + format, format.toUtf8().constData(), 40); //magic number

    popup = new PopupWindow("Информация", "Скриншот успешно сохранен.");
    popup->show();
}

void FullScreenshoter::playSound() {
    if (settings.sound) {
        QFile::copy(":/rc/sound.wav", QDir::tempPath() + "/sound.wav");

        #ifdef Q_OS_LINUX
            QProcess *p = new QProcess(this);
            p->startDetached("play", QStringList() << QDir::tempPath() + "/sound.wav");
        #else
            QSound::play(QDir::tempPath() + "/sound.wav");
        #endif
    }
}

void FullScreenshoter::setSettings(Settings settings) {
    this->settings = settings;
}

/**************************************/
/*           PartScreenshoter         */
/**************************************/

PartScreenshoter::PartScreenshoter(Settings settings): FullScreenshoter(settings) {
    setMouseTracking(true);

    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    image = new QLabel(this);
    image->show();
    image->move(0, 0);
    image->resize(screenWidth, screenHeight);

    if (settings.activeGrabbing)
        image->setVisible(false);

    topLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);
    topRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);
    bottomLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);
    bottomRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);

    QString red = QString::number(qRed(settings.frameColor));
    QString green = QString::number(qGreen(settings.frameColor));
    QString blue = QString::number(qBlue(settings.frameColor));
    QString color = "rgb(" + red + ", " + green + ", " + blue + ")";

    horizontalLine = new QLabel(this);
    horizontalLine->setGeometry(0, 0, screenWidth, 1);
    horizontalLine->setStyleSheet("background: " + color + ";");

    verticalLine = new QLabel(this);
    verticalLine->setGeometry(0, 0, 1, screenHeight);
    verticalLine->setStyleSheet("background: " + color + ";");
}

void PartScreenshoter::makeScreenshot() {
    rect.setX(cursor().pos().x());
    rect.setY(cursor().pos().y());
    rect.setWidth(3);
    rect.setHeight(3);

    start = QPoint(rect.x(), rect.y());
    selecting = false;

    QScreen* screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(QApplication::desktop()->winId());
    image->setPixmap(screenshot);

    moveOverlays();

    installEventFilter(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    showFullScreen();
    setCursor(QCursor(QPixmap(":/rc/cursor.ico")));

    verticalLine->setVisible(true);
    horizontalLine->setVisible(true);

    topRightOverlay->setVisible(false);
    bottomLeftOverlay->setVisible(false);
    bottomRightOverlay->setVisible(false);
}

void PartScreenshoter::moveOverlays(bool isSelecting) {
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    if (!isSelecting) {
        topLeftOverlay->move(-1, -1);
        topLeftOverlay->resize(screenWidth + 2, screenHeight + 2);

        horizontalLine->move(0, cursor().pos().y() - 1);
        verticalLine->move(cursor().pos().x() - 1, 0);
    } else {
        topLeftOverlay->move(-1, -1);
        topLeftOverlay->resize(rect.x() + rect.width() + 1, rect.y() + 2);

        topRightOverlay->move(rect.x() + rect.width() - 1, -1);
        topRightOverlay->resize(screenWidth - rect.x() - rect.width() + 3, rect.y() + rect.height() + 1);

        bottomLeftOverlay->move(-1, rect.y());
        bottomLeftOverlay->resize(rect.x() + 1, screenHeight - rect.y() + 3);

        bottomRightOverlay->move(rect.x() - 1, rect.y() + rect.height() - 1);
        bottomRightOverlay->resize(screenWidth - rect.x() + 3, screenHeight - rect.y() - rect.height() + 3);
    }
}

bool PartScreenshoter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        switch (((QKeyEvent*) event)->key()) {
            case Qt::Key_Escape: {
                selecting = false;
                hide();
                return false;
                break;
            }
            default:
                break;
        }
    }

    if (event->type() == QEvent::MouseButtonPress) {
        start = QPoint(((QMouseEvent*) event)->x(), ((QMouseEvent*) event)->y());

        if (!selecting) {
            rect.setX(cursor().pos().x());
            rect.setY(cursor().pos().y());
            rect.setWidth(2);
            rect.setHeight(2);
        }

        selecting = true;
        moveOverlays(true);

        topRightOverlay->setVisible(true);
        bottomLeftOverlay->setVisible(true);
        bottomRightOverlay->setVisible(true);

        horizontalLine->move(-1, -1);
        verticalLine->move(-1, -1);
    }

    if (event->type() == QEvent::HoverMove) {
        int tempX = ((QHoverEvent*) event)->pos().x();
        int tempY = ((QHoverEvent*) event)->pos().y();

        if (tempX < start.x()) {
            rect.setX(tempX);
            rect.setWidth(start.x() - tempX);
        } else {
            rect.setX(start.x());
            rect.setWidth(tempX - start.x());
        }

        if (tempY < start.y()) {
            rect.setY(tempY);
            rect.setHeight(start.y() - tempY);
        } else {
            rect.setY(start.y());
            rect.setHeight(tempY - start.y());
        }

        moveOverlays(selecting);
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        if (rect.width() < 5 || rect.height() < 5) return QMainWindow::eventFilter(obj, event);
        if (!selecting) return QMainWindow::eventFilter(obj, event);

        if (settings.activeGrabbing) {
            QScreen* screen = QApplication::primaryScreen();
            screenshot = screen->grabWindow(QApplication::desktop()->winId());
        }

        QImage temp = QImage(rect.width(), rect.height(), QImage::Format_RGB32);
        for (int i = rect.x(); i < rect.x() + rect.width(); i++) {
            for (int j = rect.y(); j < rect.y() + rect.height(); j++) {
                temp.setPixel(i - rect.x(), j - rect.y(), screenshot.toImage().pixel(i, j));
            }
        }

        QPixmap pixmap = QPixmap::fromImage(temp);

        if (settings.autoSave) {
            screenshot = pixmap;
            saveToFile(settings.saveDir, settings.saveFormat, settings.saveQuality);
        }

        if (settings.autoCopy) {
            QApplication::clipboard()->setImage(temp);
        }

        if (settings.autoSend) {
            //как-нибудь потом
        }

        playSound();


        selecting = false;
        close();
    }

    return QMainWindow::eventFilter(obj, event);
}
