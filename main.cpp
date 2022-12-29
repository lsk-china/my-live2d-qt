#include "widget.h"
#include <QApplication>
#include <string.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    cout << "argc: " << argc << endl;
    if (argc == 3) {
        w.setModel(argv[1], argv[2]);
    }
    if (argc == 4) {
        w.setModel(argv[1], argv[2]);
        w.setWidgetPosition(strcmp("left", argv[3]) == 0);
    }
    w.show();
    return QApplication::exec();
}
