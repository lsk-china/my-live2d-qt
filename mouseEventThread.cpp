#include "mouseEventThread.h"

MouseEventThread::MouseEventThread(QRect screenRect, int winID, double sensibility, QObject *parent) : QThread(parent) {
    connect(this, &QThread::finished, this, &MouseEventThread::cleanup);
    controlDisplay = XOpenDisplay(NULL);
    rootWindow = XRootWindow(controlDisplay, 0);
    appWindow = winID;
    dataDisplay = XOpenDisplay(NULL);
    if (!controlDisplay || !dataDisplay) {
        qFatal("Cannot open display!");
    }
    XSynchronize(controlDisplay, 1);

    int major, minor;
    if (!XRecordQueryVersion (controlDisplay, &major, &minor)) {
        qFatal("RECORD extension not supported on this X server!");
    }
    qInfo("Version of record extension: %d.%d", major, minor);
    this->sensibility = sensibility;
}

void MouseEventThread::run() {
    XRecordClientSpec  rcs;
    rr = XRecordAllocRange();
    if (!rr) {
        qFatal("Could not alloc record range object!");
    }

    rr->device_events.first = KeyPress;
    rr->device_events.last = MotionNotify;
    rcs = XRecordAllClients;

    ctx = XRecordCreateContext(controlDisplay, 0, &rcs, 1, &rr, 1);
    if (!ctx) {
        qFatal("Could not create a record context!");
    }
    XRecordEnableContext(dataDisplay, ctx, callback, (XPointer) this);
    while (true) {
        XRecordProcessReplies(dataDisplay);
    }
}


MouseEventThread::~MouseEventThread() {
}

void MouseEventThread::callback(XPointer closure, XRecordInterceptData *hook) {
    ((MouseEventThread *) closure)->processEvent(hook);
}

void MouseEventThread::processEvent(XRecordInterceptData *hook) {
    if (hook->category != XRecordFromServer) {
        XRecordFreeData (hook);
        return;
    }
    XRecordDatum *data = (XRecordDatum*) hook->data;
    unsigned char buttonCode = data->event.u.u.detail;
    int absX, absY, relX, relY;
    int eventType = data->type;
    switch (eventType) {
        case ButtonPress:
            if (buttonCode == 1) {
                if (queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mousePress(QPoint(relX * sensibility, relY * sensibility), QPoint(absX * sensibility, absY * sensibility));
            }
            break;
        case ButtonRelease:
            if (buttonCode == 1) {
                if (queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mouseRelease(QPoint(relX * sensibility, relY * sensibility), QPoint(absX * sensibility, absY * sensibility));
            }
            break;
        case MotionNotify:
            if (queryCursor(relX, relY, absX, absY)) {
                break;
            }
//            dx = lastx - relX;
//            dy = lasty - relY;
//            lastx = relX, lasty = relY;
//            if (abs(dx) < 10 || abs(dy) < 10) {
//                qDebug() << "motion too small, ignoring...";
//                break;
//            }
            emit mouseEvent(QPoint(relX * sensibility, relY * sensibility), QPoint(absX * sensibility, absY * sensibility));
            break;
    }
    XRecordFreeData (hook);
}

int MouseEventThread::queryCursor(int &relX, int &relY, int &absX, int &absY) {
    Window root_return, child_return;
    int root_x_return, root_y_return;
    int win_x_return, win_y_return;
    unsigned int mask_return;
    int retval = XQueryPointer(controlDisplay, rootWindow, &root_return, &child_return,
                               &root_x_return, &root_y_return,
                               &win_x_return, &win_y_return,
                               &mask_return);
    if (retval != 1) {
        return 1;
    }
    int local_x, local_y;
    XTranslateCoordinates(controlDisplay, rootWindow, appWindow,
                          root_x_return, root_y_return,
                          &local_x, &local_y, &child_return);
    relX = local_x;
    relY = local_y;
    absX = root_x_return;
    absY = root_y_return;
    return 0;
}

void MouseEventThread::cleanup() {
    if (ctx) {
        XRecordDisableContext(controlDisplay, ctx);
        XRecordFreeContext(controlDisplay, ctx);
    }
    if (rr) {
        XFree(rr);
    }
    if (controlDisplay) {
        XCloseDisplay(controlDisplay);
    }
    if (dataDisplay) {
        XCloseDisplay(dataDisplay);
    }
}
