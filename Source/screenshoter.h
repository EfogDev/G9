#ifndef FULLSCREENSHOTER_H
#define FULLSCREENSHOTER_H

#include <QObject>
#include <QWidget>
#include <QtCore>
#include <QtWidgets>
#include <const.h>
#include <qtransparentlabel.h>
#include <popupwindow.h>

class FullScreenshoter: public QMainWindow {
    Q_OBJECT

    public:
        FullScreenshoter(Settings settings) { this->settings = settings; }
        virtual void makeScreenshot();
        void setSettings(Settings settings);
        void saveToFile(QString filename, QString format, int quality = 100);
        QPixmap screenshot;

    protected:
        PopupWindow* popup;
        Settings settings;
        void playSound();
};

class PartScreenshoter: public FullScreenshoter {
    Q_OBJECT

    public:
        PartScreenshoter(Settings settings);
        void makeScreenshot();

    private:
        bool selecting;
        QPoint start;
        QTransparentLabel* topLeftOverlay;
        QTransparentLabel* topRightOverlay;
        QTransparentLabel* bottomLeftOverlay;
        QTransparentLabel* bottomRightOverlay;
        QRect rect;
        QLabel* image;

        /* TEST SELECTING MODE */
        QLabel* horizontalLine;
        QLabel* verticalLine;
        /* TEST SELECTING MODE */

        bool eventFilter(QObject* obj, QEvent* event);
        void moveOverlays(bool isSelecting = false);
};

#endif // FULLSCREENSHOTER_H
