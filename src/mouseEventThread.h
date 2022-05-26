#ifndef MOUSEEVENTTHREAD_H
#define MOUSEEVENTTHREAD_H

#include <QThread>
#include <QObject>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <QRect>
#include <QPoint>

class MouseEventThread : public QThread {
    Q_OBJECT
public:
    MouseEventThread(QRect screenRect, QObject *parent = nullptr);
    ~MouseEventThread();
private:
    void run();
    Display *display = QX11Info::display();
    Window rootWindow;
    int xi_opcode;
    QRect *canvasRect;
signals:
    void mouseEnter();
    void mouseLeave();
};


#endif // MOUSEEVENTTHREAD_H
