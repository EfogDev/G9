#include "mainwindow.h"
#include <QtCore>
#include <QtWidgets>
#include <screenshoter.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    show();

    FullScreenshoter sh;
    sh.getScreehshot();
    sh.saveToFile("gray.png", "png", 100);
}
