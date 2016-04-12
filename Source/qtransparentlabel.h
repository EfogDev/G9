#ifndef QTRANSPARENTLABLE_H
#define QTRANSPARENTLABLE_H

#include <QLabel>

class QTransparentLabel: public QLabel {
    Q_OBJECT

    public:
        explicit QTransparentLabel(double opacity, QRgb color = qRgb(20, 20, 20), QRgb frameColor = qRgb(119, 119, 119), QWidget *parent = 0);
        void updateParameters(double opacity, QRgb color = qRgb(20, 20, 20), QRgb frameColor = qRgb(119, 119, 119));

    private:
        double opacity;
        QRgb color;
        QRgb frameColor;
        void paintEvent(QPaintEvent *e);
};

#endif // QTRANSPARENTLABLE_H
