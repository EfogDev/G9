#ifndef QTRANSPARENTLABLE_H
#define QTRANSPARENTLABLE_H

#include <QLabel>

class QTransparentLabel: public QLabel {
    Q_OBJECT

    public:
        explicit QTransparentLabel(double opacity, QRgb color = qRgb(20, 20, 20), QWidget *parent = 0);

    private:
        double opacity;
        QRgb color;
        void paintEvent(QPaintEvent *e);
};

#endif // QTRANSPARENTLABLE_H
