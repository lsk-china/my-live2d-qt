#include"widget.h"
#include "runningCheck.h"
#include "configuration.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    configuration config;
    Widget w(config);
    QObject::connect(&a, &QApplication::aboutToQuit, &w, []() {
        deleteLock();
    });
    if (check()) {
        std::perror("already running!");
        return -1;
    }
    w.show();
    return QApplication::exec();
}