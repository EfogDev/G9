#include "mainwindow.h"
#include <QtCore>
#include <QtWidgets>
#include <screenshoter.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    PartScreenshoter* ps = new PartScreenshoter(settings);
    ps->makeScreenshot();
}
