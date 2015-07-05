#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>

class PopupWindow: public QWidget {
    Q_OBJECT

    public:
        explicit PopupWindow(QString title, QString text, QWidget* parent = 0);

    signals:
        void finished();

    public slots:
        void lowerOpacity();
        void timer();
        void check();

    private:
        QTimer* startTimer = 0;
        QTimer* tempTimer = 0;
        QTimer* checkTimer = 0;

        QGraphicsBlurEffect* blurEffect;
};

#endif // POPUPWINDOW_H
