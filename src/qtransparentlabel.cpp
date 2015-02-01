#include "qtransparentlabel.h"
#include <QPainter>

QTransparentLabel::QTransparentLabel(double opacity, QRgb color, QWidget *parent): QLabel(parent) {
    this->opacity = opacity;
    this->color = color;
}

void QTransparentLabel::paintEvent(QPaintEvent *e) {
    QPainter paint;
    paint.begin(this);
    paint.setBrush(QBrush(QColor(qRed(color), qGreen(color), qBlue(color), (int) (255 * opacity))));
    paint.setPen(Qt::NoPen);
    paint.drawRect(0, 0, width(), height());
    paint.end();

    Q_UNUSED(e);
}
