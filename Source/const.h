#ifndef CONST
#define CONST

#define VERSION QString::number(0.12)
#include <QString>
#include <QRgb>
#include <QDir>

struct Settings {
    public:
        bool autoSave            = true;
        QString saveDir          = QDir::homePath() + "/Screenshots/";
        QString saveFormat       = "png";
        unsigned int saveQuality = 99;
        bool autoCopy            = false;
        bool autoSend            = false;
        double opacity           = 0.75;
        QRgb frameColor          = qRgb(119, 119, 119);
        bool sound               = true;
        bool activeGrabbing      = false;

        QString hotkeyForFull    = "";
        QString hotkeyForPart    = "";
};

#endif // CONST

