#include "qtransparentlable.h"
#include <QPainter>

QTransparentLabel::QTransparentLabel(double opacity, QWidget *parent): QLabel(parent) {
    this->opacity = opacity;
}

void QTransparentLabel::paintEvent(QPaintEvent *e) {
    QPainter paint;
    paint.begin(this);
    paint.setBrush(QBrush(QColor(0, 0, 0, (int) (255 * opacity))));
    paint.setPen(Qt::NoPen);
    paint.drawRect(0, 0, width(), height());
    paint.end();

    Q_UNUSED(e);
}
