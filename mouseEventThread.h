#ifndef MOUSEEVENTTHREAD_H
#define MOUSEEVENTTHREAD_H

#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QObject>
#include <QX11Info>
#include <QRect>
#include <QPoint>

#include <X11/X.h>
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/cursorfont.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/record.h>
#include <X11/extensions/XTest.h>

#define WheelUp			4
#define WheelDown		5
#define WheelLeft		6
#define WheelRight		7

typedef union {
    unsigned char    type ;
    xEvent           event ;
    xResourceReq     req   ;
    xGenericReply    reply ;
    xError           error ;
    xConnSetupPrefix setup;
} XRecordDatum;

using namespace std;

class MouseEventThread : public QThread {
    Q_OBJECT
public:
    MouseEventThread(QRect screenRect, int winID, QObject *parent = nullptr);
    ~MouseEventThread();
    static void callback(XPointer closure, XRecordInterceptData* hook);
    void processEvent(XRecordInterceptData* hook);
    int queryCursor(int &relX, int &relY, int &absX, int &absY);

public slots:
    void cleanup();

private:
    void run() override;

    Display *controlDisplay;
    Display *dataDisplay;
    XRecordContext ctx;
    XRecordRange *rr;
    Window rootWindow;
    Window appWindow;

signals:
    void mouseEvent(QPoint relPosition, QPoint absPosition);
    void mousePress(QPoint relPosition, QPoint absPosition);
    void mouseRelease(QPoint relPosition, QPoint absPosition);
};


#endif // MOUSEEVENTTHREAD_H
