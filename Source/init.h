#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <qxt/qxtglobalshortcut.h>
#include "screenshoter.h"
#include "const.h"
#include <popupwindow.h>

class Init: public QWidget {
    Q_OBJECT

    public:
        Init(bool startMessage, QWidget *parent = 0);

    private:
        Settings settings;
        QxtGlobalShortcut *shortcutPart;
        QxtGlobalShortcut *shortcutFull;
        PopupWindow* popup;

        PartScreenshoter* partScr;
        FullScreenshoter* fullScr;

        bool checkOpened();
        void startListen();
        void loadSettings();
        void createTrayIcon();

    private slots:
        void settingsSaved(Settings settings);
        void hotkey1clicked();
        void hotkey2clicked();
};

QDataStream& operator<<(QDataStream& out, const Settings& settings);
QDataStream& operator>>(QDataStream& in, Settings& settings);

#endif // MAINWINDOW_H
