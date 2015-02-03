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
        void check();

    private:
        QTimer *startTimer = 0;
        QTimer *tempTimer = 0;
        QTimer *checkTimer = 0;
};

#endif // POPUPWINDOW_H
