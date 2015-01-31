#ifndef QTRANSPARENTLABLE_H
#define QTRANSPARENTLABLE_H

#include <QLabel>

class QTransparentLabel: public QLabel {
    Q_OBJECT

    public:
        explicit QTransparentLabel(double opacity, QWidget *parent = 0);

    private:
        double opacity;
        void paintEvent(QPaintEvent *e);
};

#endif // QTRANSPARENTLABLE_H
