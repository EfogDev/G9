#include "mainwindow.h"
#include <QtCore>
#include <QtWidgets>
#include <screenshoter.h>
#include <popupwindow.h>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    PopupWindow* popup;
    if (!checkOpened()) {
        popup = new PopupWindow("Информация", "G9 успешно запущен. С возвращением!");
        popup->show();
    } else {
        popup = new PopupWindow("Прости, братишка", "G9 уже запущен, зачем вам еще один?");
        popup->show();
    }

    startListen();
}

bool MainWindow::checkOpened() {
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 63223);
    if (!socket.waitForConnected(100))
        return false;
    else return true;
}

void MainWindow::startListen() {
    QTcpServer server;
    server.listen(QHostAddress::Any, 63223);

    QEventLoop loop;
    loop.exec();
}
