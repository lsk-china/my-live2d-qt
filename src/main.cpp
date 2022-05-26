#include "live2d.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Live2D w;
    w.showMaximized();
    int ret = a.exec();
    return ret;
}
