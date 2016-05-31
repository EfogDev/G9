#include "qtransparentlabel.h"
#include <QPainter>
#include <QRgb>
#include <QDebug>

QTransparentLabel::QTransparentLabel(double opacity, QRgb color, QRgb frameColor, QWidget *parent): QLabel(parent) {
    this->opacity = opacity;
    this->color = color;
    this->frameColor = frameColor;
    this->paint = new QPainter();

    auto red = QString::number(qRed(color));
    auto green = QString::number(qGreen(color));
    auto blue = QString::number(qBlue(color));
    auto opacityPercent = QString::number((int) (opacity * 100));

    setStyleSheet("background-color: rgba(" + red + ", " + green + ", " + blue + ", " + opacityPercent + "%)");
}

void QTransparentLabel::updateParameters(double opacity, QRgb color, QRgb frameColor) {
    this->opacity = opacity;
    this->color = color;
    this->frameColor = frameColor;

    auto red = QString::number(qRed(color));
    auto green = QString::number(qGreen(color));
    auto blue = QString::number(qBlue(color));
    auto opacityPercent = QString::number((int) (opacity * 100));

    setStyleSheet("background-color: rgba(" + red + ", " + green + ", " + blue + ", " + opacityPercent + "%)");
}

void QTransparentLabel::paintEvent(QPaintEvent* /*e*/) {
    paint->begin(this);
    paint->setPen(frameColor);

    if (width() > 3 && height() > 3) {
        paint->drawLine(0, 0, width() - 1, 0);
        paint->drawLine(0, 0, 0, height() - 1);
        paint->drawLine(width() - 1, 0, width() - 1, height() - 1);
        paint->drawLine(0, height() - 1, width() - 1, height() - 1);
    }

    paint->end();
}
