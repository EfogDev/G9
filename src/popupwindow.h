#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>

class PopupWindow: public QWidget {
    Q_OBJECT

    public:
        explicit PopupWindow(QString title, QString text, QWidget *parent = 0);

    signals:

    public slots:
        void lowerOpacity();
        void timer();
};

#endif // POPUPWINDOW_H
