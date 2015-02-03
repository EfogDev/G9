#include "qtransparentlabel.h"
#include <QPainter>

QTransparentLabel::QTransparentLabel(double opacity, QRgb color, QRgb frameColor, QWidget *parent): QLabel(parent) {
    this->opacity = opacity;
    this->color = color;
    this->frameColor = frameColor;
}

void QTransparentLabel::paintEvent(QPaintEvent *e) {
    QPainter paint;
    paint.begin(this);

    if (width() > 3 && height() > 3) {
        paint.setPen(frameColor);
        paint.drawLine(0, 0, width() - 1, 0);
        paint.drawLine(0, 0, 0, height() - 1);
        paint.drawLine(width() - 1, 0, width() - 1, height() - 1);
        paint.drawLine(0, height() - 1, width() - 1, height() - 1);

        paint.setBrush(QBrush(QColor(qRed(color), qGreen(color), qBlue(color), (int) (255 * opacity))));
        paint.setPen(Qt::NoPen);
        paint.drawRect(1, 1, width() - 2, height() - 2);
    }

    paint.end();
    Q_UNUSED(e);
}
