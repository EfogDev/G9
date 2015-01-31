#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>

struct Settings {
    public:
        bool autoSave            = true;
        QString saveDir          = QDir::homePath() + "/Screenshots/";
        const char* saveFormat   = "png";
        unsigned int saveQuality = 100;
        bool autoCopy            = false;
        bool autoSend            = true;
        double opacity           = 0.7;
        QRgb frameColor          = qRgb(120, 120, 120);
};

class MainWindow: public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

    private:
        Settings settings;

};

#endif // MAINWINDOW_H
