#include "init.h"
#include <QtCore>
#include <QtWidgets>
#include <screenshoter.h>
#include <QtNetwork>
#include <settingswindow.h>
#include <const.h>
#include <qxt/qxtglobalshortcut.h>

Init::Init(bool startMessage, QWidget *parent): QWidget(parent) {
    bool firstLaunch = false;
    QDir dir;
    if (!dir.exists(QDir::homePath() + "/.g9")) {
        dir.mkdir(QDir::homePath() + "/.g9");
        firstLaunch = true;
    }

    if (firstLaunch) {

    }

    loadSettings();

    if (!checkOpened()) {
        shortcutPart = new QxtGlobalShortcut(this);
        shortcutPart->setShortcut(QKeySequence(settings.hotkeyForPart));
        connect(shortcutPart, SIGNAL(activated()), this, SLOT(hotkey2clicked()));

        shortcutFull = new QxtGlobalShortcut(this);
        shortcutFull->setShortcut(QKeySequence(settings.hotkeyForFull));
        connect(shortcutFull, SIGNAL(activated()), this, SLOT(hotkey1clicked()));

        if (startMessage) {
            popup = new PopupWindow("Информация", "G9 успешно запущен. С возвращением!");
            popup->show();
        }

        createTrayIcon();
        startListen();
    } else {
        popup = new PopupWindow("Информация", "G9 уже запущен, вторая копия будет закрыта.");
        popup->show();

        connect(popup, &PopupWindow::finished, [=] () {
            close();
        });
    }
}

void Init::createTrayIcon() {
    QAction* settingsAction = new QAction(this);
    settingsAction->setText("Настройки");
    connect(settingsAction, &QAction::triggered, [=] (bool /*checked*/) {
        SettingsWindow* settingsWindow = new SettingsWindow(settings);
        connect(settingsWindow, SIGNAL(saved(Settings)), this, SLOT(settingsSaved(Settings)));
        settingsWindow->show();
    });

    QAction* exitAction = new QAction(this);
    exitAction->setText("Выход");
    connect(exitAction, &QAction::triggered, [=] (bool /*checked*/) {
        popup->close();
        close();
        qApp->exit();
    });

    QMenu* trayMenu = new QMenu(this);
    trayMenu->addActions(QList<QAction*>() << settingsAction);
    trayMenu->addSeparator();
    trayMenu->addActions(QList<QAction*>() << exitAction);

    QSystemTrayIcon* icon = new QSystemTrayIcon(this);
    icon->setIcon(QIcon(":/rc/icon.ico"));
    icon->setContextMenu(trayMenu);
    icon->setVisible(true);
}

bool Init::checkOpened() {
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 63223);
    if (!socket.waitForConnected(100))
        return false;
    else return true;
}

void Init::startListen() {
    QTcpServer server;
    server.listen(QHostAddress::Any, 63223);

    QEventLoop loop;
    loop.exec();
}

void Init::settingsSaved(Settings settings) {
    this->settings = settings;

    QFile file(QDir::homePath() + "/.g9/config.bin");
    file.open(QIODevice::WriteOnly);
    QDataStream fs(&file);
    fs.setVersion(QDataStream::Qt_5_2);
    fs << this->settings;
    file.close();

    QFile version(QDir::homePath() + "/.g9/version");
    version.open(QIODevice::WriteOnly);
    version.write(VERSION.toStdString().c_str());
    version.close();
}

void Init::loadSettings() {
    QFile file(QDir::homePath() + "/.g9/version");

    if (!file.exists())
        file.open(QIODevice::ReadWrite);
    else file.open(QIODevice::ReadOnly);

    QString version = file.readAll();
    if (version != VERSION) {
        qDebug() << "Old version! Rewriting settings!";
        settingsSaved(settings);
        return;
    }

    QFile data(QDir::homePath() + "/.g9/config.bin");
    data.open(QIODevice::ReadOnly);
    QDataStream fs(&data);
    fs.setVersion(QDataStream::Qt_5_2);
    fs >> settings;
    data.close();
}

QDataStream& operator<<(QDataStream& out, const Settings& settings) {
    out << settings.activeGrabbing << settings.autoCopy << settings.autoSave << settings.autoSend << settings.frameColor << settings.opacity << settings.saveDir << settings.saveFormat << settings.saveQuality << settings.sound;
    return out;
}

QDataStream& operator>>(QDataStream& in, Settings& settings) {
    in >> settings.activeGrabbing >> settings.autoCopy >> settings.autoSave >> settings.autoSend >> settings.frameColor >> settings.opacity >> settings.saveDir >> settings.saveFormat >> settings.saveQuality >> settings.sound;
    return in;
}

void Init::hotkey1clicked() {
    popup->close();

    fullScr = new FullScreenshoter(settings);
    fullScr->setSettings(settings);
    fullScr->makeScreenshot();
}

void Init::hotkey2clicked() {
    popup->close();

    partScr = new PartScreenshoter(settings);
    partScr->setSettings(settings);
    partScr->makeScreenshot();
}
