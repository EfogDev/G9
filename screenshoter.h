#ifndef FULLSCREENSHOTER_H
#define FULLSCREENSHOTER_H

#include <QObject>
#include <QWidget>
#include <QtCore>
#include <QtWidgets>

class FullScreenshoter: public QWidget {
    Q_OBJECT

    public:
        FullScreenshoter(QWidget *parent = 0);
        virtual void getScreehshot();
        void saveToFile(QString filename, const char* format, int quality = 100);
        QPixmap* screenshot = 0;
        QPixmap* grayscale = 0;

    private:
        void generateGrayscale();
};

class PartScreenshoter: public FullScreenshoter {
    Q_OBJECT

    public:
        PartScreenshoter(QWidget *parent = 0);
        void getScreehshot();
};

#endif // FULLSCREENSHOTER_H
