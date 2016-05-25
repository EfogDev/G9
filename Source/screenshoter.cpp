#include "screenshoter.h"
#include "qtransparentlabel.h"
#include "math.h"
#include "QSound"
#include "QtNetwork"

/**************************************/
/*           FullScreenshoter         */
/**************************************/

void FullScreenshoter::takeScreenshot() {
    QDesktopWidget* desktop = QApplication::desktop();
    QScreen* screen = QApplication::screens()[desktop->screenNumber(QCursor::pos())];
    screenshot = screen->grabWindow(desktop->winId(), screen->geometry().x(), screen->geometry().y(), screen->geometry().width(), screen->geometry().height());
}

void FullScreenshoter::makeScreenshot() {
    takeScreenshot();

    if (settings.autoSend) {
        sendToImgur();
    }

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

void FullScreenshoter::sendToImgur() {
    QByteArray base64image;
    QBuffer buffer(&base64image);
    buffer.open(QIODevice::WriteOnly);
    screenshot.save(&buffer, "PNG", 100);
    base64image = base64image.toBase64().toPercentEncoding();

    QByteArray data;
    QUrlQuery params;
    params.addQueryItem("type", "base64");
    params.addQueryItem("image", base64image);
    data.append(params.toString(QUrl::FullyDecoded).toUtf8());

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://api.imgur.com/3/image"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    request.setRawHeader("Authorization", "Client-ID 9a2331b493dfbb6");
    manager->post(request, data);

    popup = new PopupWindow("Информация", "Отправляю на IMGUR...");
    popup->show();

    connect(manager, &QNetworkAccessManager::finished, [=] (QNetworkReply* reply) {
        QApplication::clipboard()->setText(reply->readAll());

        popup = new PopupWindow("Информация", "Скриншот загружен, ссылка скопирована.");
        popup->show();
    });
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

    int screenWidth = QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().width();
    int screenHeight = QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().height();

    image = new QLabel(this);
    image->show();
    image->move(0, 0);
    image->resize(screenWidth, screenHeight);

    topLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);
    topRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);
    bottomLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);
    bottomRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), settings.frameColor, this);

    horizontalLine = new QLabel(this);
    verticalLine = new QLabel(this);
}

void PartScreenshoter::makeScreenshot() {
    int screenWidth = QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().width();
    int screenHeight = QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().height();

    int cursorX = cursor().pos().x() - QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().x();
    int cursorY = cursor().pos().y() - QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().y();

    rect.setX(cursorX);
    rect.setY(cursorY);
    rect.setWidth(3);
    rect.setHeight(3);

    start = QPoint(rect.x(), rect.y());
    selecting = false;

    takeScreenshot();

    image->setPixmap(screenshot);
    image->setVisible(!settings.activeGrabbing);

    topLeftOverlay->updateParameters(settings.opacity, qRgb(20, 20, 20), settings.frameColor);
    topRightOverlay->updateParameters(settings.opacity, qRgb(20, 20, 20), settings.frameColor);
    bottomLeftOverlay->updateParameters(settings.opacity, qRgb(20, 20, 20), settings.frameColor);
    bottomRightOverlay->updateParameters(settings.opacity, qRgb(20, 20, 20), settings.frameColor);

    QString red = QString::number(qRed(settings.frameColor));
    QString green = QString::number(qGreen(settings.frameColor));
    QString blue = QString::number(qBlue(settings.frameColor));
    QString color = "rgb(" + red + ", " + green + ", " + blue + ")";

    horizontalLine->setGeometry(0, 0, screenWidth, 1);
    horizontalLine->setStyleSheet("background: " + color + ";");

    verticalLine->setGeometry(0, 0, 1, screenHeight);
    verticalLine->setStyleSheet("background: " + color + ";");

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
    int screenWidth = QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().width();
    int screenHeight = QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().height();

    int cursorX = cursor().pos().x() - QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().x();
    int cursorY = cursor().pos().y() - QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().y();

    if (!isSelecting) {
        topLeftOverlay->move(-1, -1);
        topLeftOverlay->resize(screenWidth + 2, screenHeight + 2);

        horizontalLine->move(0, cursorY - 1);
        verticalLine->move(cursorX - 1, 0);
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
        int tempX = ((QHoverEvent*) event)->pos().x();// - QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().x();
        int tempY = ((QHoverEvent*) event)->pos().y();// - QApplication::screens()[qApp->desktop()->screenNumber(QCursor::pos())]->geometry().y();

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
            takeScreenshot();
        }

        QImage temp = QImage(rect.width(), rect.height(), QImage::Format_RGB32);
        for (int i = rect.x(); i < rect.x() + rect.width(); i++) {
            for (int j = rect.y(); j < rect.y() + rect.height(); j++) {
                temp.setPixel(i - rect.x(), j - rect.y(), screenshot.toImage().pixel(i, j));
            }
        }

        QPixmap pixmap = QPixmap::fromImage(temp);

        if (settings.autoSend) {
            sendToImgur();
        }

        if (settings.autoSave) {
            screenshot = pixmap;
            saveToFile(settings.saveDir, settings.saveFormat, settings.saveQuality);
        }

        if (settings.autoCopy) {
            QApplication::clipboard()->setImage(temp);
        }

        playSound();

        selecting = false;
        hide();
    }

    return QMainWindow::eventFilter(obj, event);
}
