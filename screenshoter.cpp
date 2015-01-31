#include "screenshoter.h"

/**************************************/
/*           FullScreenshoter         */
/**************************************/

FullScreenshoter::FullScreenshoter(QWidget *parent): QWidget(parent) {

}

void FullScreenshoter::getScreehshot() {
    QScreen* screen = QApplication::primaryScreen();
    QPixmap temp = screen->grabWindow(QApplication::desktop()->winId());

    screenshot = &temp;
    qDebug() << screenshot->width() << screenshot->height();
    saveToFile("gray.jpg", "jpg", 100);
}

void FullScreenshoter::generateGrayscale() {
    QPixmap temp = *screenshot;
    QImage image = temp.toImage();

    for (int  i = 0; i < image.width(); i++) {
        for (int  j = 0; j < image.height(); j++) {
            QRgb color = image.pixel(i, j);
            int gray = (qRed(color) + qGreen(color) + qBlue(color)) / 3;
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }

    temp = QPixmap::fromImage(image);
    grayscale = &temp;
}

void FullScreenshoter::saveToFile(QString filename, const char* format, int quality) {
    qDebug() << screenshot->width() << screenshot->height();
    //screenshot->save(filename, format, quality);
    //qDebug() << grayscale->isNull() << grayscale->save(filename, format, quality);
}

/**************************************/
/*           PartScreenshoter         */
/**************************************/

PartScreenshoter::PartScreenshoter(QWidget *parent): FullScreenshoter(parent) {

}

void PartScreenshoter::getScreehshot() {

}
