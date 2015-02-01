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

    QSound sound(":/rc/sound.wav");
    sound.play();
}

void FullScreenshoter::saveToFile(QString filename, const char* format, int quality) {
    QDir directory;
    if (!directory.exists(filename))
        directory.mkdir(filename);

    QDateTime time = QDateTime::currentDateTime();

    if (!strcmp(format, "jpg") && !strcmp(format, "gif")) {
        screenshot.save(filename + "Screenshot " + time.toString("dd.MM.yyyy hh:mm:ss") + "." + format, format, quality);
    }
    else
        screenshot.save(filename + "Screenshot " + time.toString("dd.MM.yyyy hh:mm:ss") + "." + format, format, 40); //magic number
}

void FullScreenshoter::playSound() {

    QFile::copy(":/rc/sound.wav", QDir::tempPath() + "/sound.wav");
#ifdef Q_OS_LINUX
    QProcess::startDetached("play " + QDir::tempPath() + "/sound.wav");
#else
    QSound::play(QDir::tempPath() + "/sound.wav");
#endif

}

/**************************************/
/*           PartScreenshoter         */
/**************************************/

void PartScreenshoter::makeScreenshot() {
    QScreen* screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(QApplication::desktop()->winId());

    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    QLabel* image = new QLabel(this);
    image->show();
    image->setPixmap(screenshot);
    image->move(0, 0);
    image->resize(screenWidth, screenHeight);

    /* Overlays */

    QString borderStyle = "border: 1px solid gray;";

    topLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    topLeftOverlay->setStyleSheet(borderStyle);

    topRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    topRightOverlay->setStyleSheet(borderStyle);

    bottomLeftOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    bottomLeftOverlay->setStyleSheet(borderStyle);

    bottomRightOverlay = new QTransparentLabel(settings.opacity, qRgb(20, 20, 20), this);
    bottomRightOverlay->setStyleSheet(borderStyle);

    moveOverlays();

    /* End overlays */

    installEventFilter(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowTitle("Screenshot");
    showFullScreen();

    setCursor(QCursor(QPixmap(":/rc/cursor.ico")));
}

void PartScreenshoter::moveOverlays(bool isSelecting) {
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    if (!isSelecting) {
        topLeftOverlay->move(0, 0);
        topLeftOverlay->resize(cursor().pos().x(), cursor().pos().y());

        topRightOverlay->move(cursor().pos().x() - 1, 0);
        topRightOverlay->resize(screenWidth - cursor().pos().x(), cursor().pos().y());

        bottomLeftOverlay->move(0, cursor().pos().y() - 1);
        bottomLeftOverlay->resize(cursor().pos().x(), screenHeight - cursor().pos().y());

        bottomRightOverlay->move(cursor().pos().x() - 1, cursor().pos().y() - 1);
        bottomRightOverlay->resize(screenWidth - cursor().pos().x(), screenHeight - cursor().pos().y());
    } else { //тут происходит жуткая магия
        topLeftOverlay->move(0, 0);
        topLeftOverlay->resize(rect.x() + rect.width(), rect.y());

        topRightOverlay->move(rect.x() + rect.width() - 1, 0);
        topRightOverlay->resize(screenWidth - rect.x() - rect.width(), rect.y() + rect.height());

        bottomLeftOverlay->move(0, rect.y() - 1);
        bottomLeftOverlay->resize(rect.x(), screenHeight - rect.y());

        bottomRightOverlay->move(rect.x() - 1, rect.y() + rect.height() - 1);
        bottomRightOverlay->resize(screenWidth - rect.x(), screenHeight - rect.y() - rect.height());
    }
}

bool PartScreenshoter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        switch (((QKeyEvent*) event)->key()) {
            case Qt::Key_Escape:
                close();
                break;
        }
    }

    if (event->type() == QEvent::MouseButtonPress) {
        start = QPoint(((QMouseEvent*) event)->x(), ((QMouseEvent*) event)->y());
        selecting = true;
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
