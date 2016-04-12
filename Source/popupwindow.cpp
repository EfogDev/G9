#include "popupwindow.h"
#include "QFile"
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

PopupWindow::PopupWindow(QString title, QString text, QWidget* parent) : QWidget(parent) {
    QFile f(":/rc/popup.qss");
    f.open(QIODevice::ReadOnly);
    QString style = f.readAll();
    f.close();

    setStyleSheet(style);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowTransparentForInput | Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setFocusPolicy(Qt::NoFocus);
    setParent(0);
    move(QApplication::desktop()->width() - 400 - 20, 40);
    setFixedSize(400, 60);

    QLabel *titleLabel = new QLabel(this);
    titleLabel->setText(title);
    titleLabel->setGeometry(65, 7, 380, 25);
    titleLabel->setStyleSheet("font-weight: bold; color: white;");

    QLabel *textLabel = new QLabel(this);
    textLabel->setText(text);
    textLabel->setGeometry(65, 25, 380, 25);
    textLabel->setStyleSheet("color: #ccc;");

    QLabel *logo = new QLabel(this);
    logo->setPixmap(QPixmap(":/rc/logo.png").scaled(32, 32));
    logo->setGeometry(16, 14, 32, 32);

    startTimer = new QTimer();
    startTimer->start(3000);
    connect(startTimer, SIGNAL(timeout()), this, SLOT(timer()));

    checkTimer = new QTimer();
    checkTimer->start(70);
    connect(checkTimer, SIGNAL(timeout()), this, SLOT(check()));

    blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(7);
    blurEffect->setEnabled(false);
    blurEffect->setBlurHints(QGraphicsBlurEffect::AnimationHint | QGraphicsBlurEffect::QualityHint);

    setGraphicsEffect(blurEffect);
}

void PopupWindow::lowerOpacity() {
    if (windowOpacity() <= 0) {
        emit finished();
        close();
    } else
        setWindowOpacity(windowOpacity() - 0.005);
}

void PopupWindow::timer() {
    tempTimer = new QTimer();
    tempTimer->setInterval(10);
    tempTimer->start();
    connect(tempTimer, SIGNAL(timeout()), this, SLOT(lowerOpacity()));
}

void PopupWindow::check() {
    int X = cursor().pos().x();
    int Y = cursor().pos().y();

    if (X > (QApplication::desktop()->width() - width() - 20 - 50) && Y < (height() + 70)) {
        if (startTimer != 0)
            startTimer->stop();

        if (tempTimer != 0)
            tempTimer->stop();

        setWindowOpacity(0.3);
        blurEffect->setEnabled(true);
    } else {
        if (!startTimer->isActive()) {
            setWindowOpacity(1);
            blurEffect->setEnabled(false);

            startTimer = new QTimer();
            startTimer->start(3000);
            connect(startTimer, SIGNAL(timeout()), this, SLOT(timer()));
        }
    }
}
