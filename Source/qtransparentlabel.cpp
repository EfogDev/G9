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
    auto borderColor = QColor(frameColor).name();

    setStyleSheet("background-color: rgba(" + red + ", " + green + ", " + blue + ", " + opacityPercent + "%); border: 1px solid " + borderColor +";");
}

void QTransparentLabel::updateParameters(double opacity, QRgb color, QRgb frameColor) {
    this->opacity = opacity;
    this->color = color;
    this->frameColor = frameColor;

    auto red = QString::number(qRed(color));
    auto green = QString::number(qGreen(color));
    auto blue = QString::number(qBlue(color));
    auto opacityPercent = QString::number((int) (opacity * 100));
    auto borderColor = QColor(frameColor).name();

    setStyleSheet("background-color: rgba(" + red + ", " + green + ", " + blue + ", " + opacityPercent + "%); border: 1px solid " + borderColor +";");
}
