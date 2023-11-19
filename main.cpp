#include"widget.h"
#include "runningCheck.h"
#include "configuration.h"
#include <QApplication>
#include "configDialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget *w;
    if (!QFile::exists(QDir::homePath() + QString("/.config/lsk/QDesktopPet.conf"))) {
        ConfigDialog configDialog(configuration(), true);
        w = new Widget(configDialog.getConfiguration());
    } else {
        configuration configuration;
        w = new Widget(configuration);
    }
    QObject::connect(&a, &QApplication::aboutToQuit, w, []() {
        deleteLock();
    });
    if (check()) {
        std::perror("already running!");
        return -1;
    }
    w->show();
    return QApplication::exec();
}