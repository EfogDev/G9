#include "init.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Init init;

    Q_UNUSED(init);
    return a.exec();
}
