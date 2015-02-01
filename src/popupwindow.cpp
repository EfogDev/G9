#include "popupwindow.h"
#include "QFile"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

PopupWindow::PopupWindow(QString title, QString text, QWidget *parent) : QWidget(parent) {
    QFile f(":/rc/popup.qss");
    f.open(QIODevice::ReadOnly);
    QString style = f.readAll();
    f.close();

    setStyleSheet(style);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    move(QApplication::desktop()->width() - 400 - 20, 40);
    setFixedSize(400, 60);

    QLabel* titleLabel = new QLabel(this);
    titleLabel->setText(title);
    titleLabel->setGeometry(65, 7, 380, 25);
    titleLabel->setStyleSheet("font-weight: bold; color: white;");

    QLabel* textLabel = new QLabel(this);
    textLabel->setText(text);
    textLabel->setGeometry(65, 25, 380, 25);
    textLabel->setStyleSheet("color: #ccc;");

    QLabel *logo = new QLabel(this);
    logo->setPixmap(QPixmap(":/rc/logo.png").scaled(32, 32));
    logo->setGeometry(16, 14, 32, 32);

    QTimer *temp = new QTimer();
    temp->start(4000);
    connect(temp, SIGNAL(timeout()), this, SLOT(timer()));
}

void PopupWindow::lowerOpacity() {
    if (windowOpacity() <= 0)
        close();
    else
        setWindowOpacity(windowOpacity() - 0.005);
}

void PopupWindow::timer() {
    QTimer* timer = new QTimer();
    timer->setInterval(10);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(lowerOpacity()));
}
