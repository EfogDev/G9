#ifndef FULLSCREENSHOTER_H
#define FULLSCREENSHOTER_H

#include <QObject>
#include <QWidget>
#include <QtCore>
#include <QtWidgets>
#include <mainwindow.h>
#include <qtransparentlabel.h>

class FullScreenshoter: public QMainWindow {
    Q_OBJECT

    public:
        FullScreenshoter(Settings settings) { this->settings = settings; }
        virtual void makeScreenshot();
        void saveToFile(QString filename, const char* format, int quality = 100);
        QPixmap screenshot;

    protected:
        Settings settings;
        void playSound();
};

class PartScreenshoter: public FullScreenshoter {
    Q_OBJECT

    public:
        PartScreenshoter(Settings settings): FullScreenshoter(settings) {}
        void makeScreenshot();

    private:
        bool selecting = false;
        QPoint  start;
        QTransparentLabel* topLeftOverlay;
        QTransparentLabel* topRightOverlay;
        QTransparentLabel* bottomLeftOverlay;
        QTransparentLabel* bottomRightOverlay;
        Settings settings;
        QRect rect;

        bool eventFilter(QObject* obj, QEvent* event);
        void moveOverlays(bool isSelecting = false);
};

#endif // FULLSCREENSHOTER_H
