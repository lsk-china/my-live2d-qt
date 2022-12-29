#ifndef MOUSEEVENTTHREAD_H
#define MOUSEEVENTTHREAD_H

#include <QThread>
#include <QObject>
#include <QX11Info>
//#include <X11/Xlib.h>
#include <QRect>
#include <QPoint>
#include <iostream>
#include <X11/extensions/XInput2.h>
using namespace std;

class MouseEventThread : public QThread {
    Q_OBJECT
public:
    MouseEventThread(QRect screenRect, int winID, QObject *parent = nullptr);
    ~MouseEventThread();
private:
    void run();
    Display *display = XOpenDisplay(0);
    Window rootWindow;
    int xi_opcode;
    QRect *canvasRect;
    Window appWindow;
signals:
    void mouseEnter();
    void mouseLeave();
    void mouseEvent(QPoint relPosition, QPoint absPosition);
};


#endif // MOUSEEVENTTHREAD_H
