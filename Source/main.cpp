#include "init.h"

int main(int argc, char *argv[]) {
    bool startMessage = true;
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]) == "--without-message")
            startMessage = false;
    }

    QApplication a(argc, argv);
    Init init(startMessage);

    Q_UNUSED(init);
    return a.exec();
}
