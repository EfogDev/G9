#include "screenshoter.h"
#include "qtransparentlabel.h"

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

/**************************************/
/*           PartScreenshoter         */
/**************************************/

void PartScreenshoter::makeScreenshot() {
    QScreen* screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(QApplication::desktop()->winId());

    QLabel* image = new QLabel(this);
    image->show();
    image->setPixmap(screenshot);
    image->move(0, 0);
    image->resize(QApplication::desktop()->width(), QApplication::desktop()->height());

    QTransparentLabel* overlay = new QTransparentLabel(settings.opacity, this);
    overlay->show();
    overlay->move(0, 0);
    overlay->resize(QApplication::desktop()->width(), QApplication::desktop()->height());

    selected.setParent(this);
    selected.show();
    selected.move(0, 0);

    installEventFilter(this);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowTitle("Screenshot");
    showFullScreen();

    setCursor(QCursor(QPixmap(":/img/cursor.ico")));
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
        selected.setGeometry(start.x(), start.y(), 20, 20);
        selected.show();
    }

    if (event->type() == QEvent::MouseMove && selecting) {
        int tempX = ((QMouseEvent*) event)->x();
        int tempY = ((QMouseEvent*) event)->y();

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

        QImage temp = QImage(rect.width(), rect.height(), QImage::Format_RGB32);
        for (int i = rect.x(); i < rect.x() + rect.width(); i++) {
            for (int j = rect.y(); j < rect.y() + rect.height(); j++) {

                //рисуем рамку
                if (i == rect.x() || i == rect.x() + rect.width() - 1) {
                    temp.setPixel(i - rect.x(), j - rect.y(), settings.frameColor);
                    continue;
                }

                if (j == rect.y() || j == rect.y() + rect.height() - 1) {
                    temp.setPixel(i - rect.x(), j - rect.y(), settings.frameColor);
                    continue;
                }
                //закончили рисовать

                temp.setPixel(i - rect.x(), j - rect.y(), screenshot.toImage().pixel(i, j));
            }
        }

        selected.setPixmap(QPixmap::fromImage(temp));
        selected.setGeometry(rect);
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

        selecting = false;
        close();
    }

    return QMainWindow::eventFilter(obj, event);
}
