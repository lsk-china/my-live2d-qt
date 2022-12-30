#include "mouseEventThread.h"

MouseEventThread::MouseEventThread(QRect screenRect, int winID, QObject *parent) : QThread(parent) {
    rootWindow = XRootWindow(display, 0);
    int event, error;
    XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error);
    unsigned char mask_bytes[(XI_LASTEVENT + 7) / 8] = {0};
    XISetMask(mask_bytes, XI_RawMotion);
    XISetMask(mask_bytes, XI_RawButtonPress);
    XISetMask(mask_bytes, XI_RawButtonRelease);
    XIEventMask evmasks[1];
    evmasks[0].deviceid = XIAllMasterDevices;
    evmasks[0].mask_len = sizeof(mask_bytes);
    evmasks[0].mask = mask_bytes;
    XISelectEvents(display, rootWindow, evmasks, 1);
    canvasRect = new QRect(screenRect.height() - 300,
                           0,
                           300,
                           300);
    this->appWindow = (Window) winID;
}

void MouseEventThread::run() {
    XEvent ev;
    int relX, relY, absX, absY;
    while (true) {
        XNextEvent(display, &ev);
        if(ev.xcookie.type != GenericEvent || ev.xcookie.extension != xi_opcode) {
            continue;
        }
        XGetEventData(display, &ev.xcookie);
        switch (ev.xcookie.evtype) {
            case XI_RawMotion:
                if (!queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mouseEvent(QPoint(relX, relY), QPoint(absX, absY));
                break;
            case XI_RawButtonPress:
                if (!queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mousePress(QPoint(relX, relY), QPoint(absX, absY));
                break;
            case XI_RawButtonRelease:
                if (!queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mouseRelease(QPoint(relX, relY), QPoint(absX, absY));
                break;
            default:
                break;
        }
        XFreeEventData(display, &ev.xcookie);
        QThread::msleep(50);
    }
}

MouseEventThread::~MouseEventThread() {
    XCloseDisplay(display);
}

int MouseEventThread::queryCursor(int &relX, int &relY, int &absX, int &absY) {
    Window root_return, child_return;
    int root_x_return, root_y_return;
    int win_x_return, win_y_return;
    unsigned int mask_return;
    int retval = XQueryPointer(display, rootWindow, &root_return, &child_return,
                               &root_x_return, &root_y_return,
                               &win_x_return, &win_y_return,
                               &mask_return);
    if (!retval) {
        return retval;
    }
    int local_x, local_y;
    XTranslateCoordinates(display, rootWindow, appWindow,
                          root_x_return, root_y_return,
                          &local_x, &local_y, &child_return);
    relX = local_x;
    relY = local_y;
    absX = root_x_return;
    absY = root_y_return;
    return 1;
}
