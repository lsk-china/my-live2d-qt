#include "mouseEventThread.h"

MouseEventThread::MouseEventThread(QRect screenRect, int winID, QObject *parent) : QThread(parent) {
    rootWindow = XRootWindow(display, 0);
    int event, error;
    XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error);
    unsigned char mask_bytes[(XI_LASTEVENT + 7) / 8] = {0};
    XISetMask(mask_bytes, XI_RawMotion);
    XIEventMask evmasks[1];
    evmasks[0].deviceid = XIAllMasterDevices;
    evmasks[0].mask_len = sizeof(mask_bytes);
    evmasks[0].mask = mask_bytes;
    XISelectEvents(display, rootWindow, evmasks, 1);;
    canvasRect = new QRect(screenRect.height() - 300,
                           0,
                           300,
                           300);
    this->appWindow = (Window) winID;
}

void MouseEventThread::run() {
    XEvent ev;
    while (true) {
        XNextEvent(display, &ev);
        if(ev.xcookie.type != GenericEvent || ev.xcookie.extension != xi_opcode) {
            continue;
        }
        XGetEventData(display, &ev.xcookie);
        if (ev.xcookie.evtype != XI_RawMotion) {
            XFreeEventData(display, &ev.xcookie);
            continue;
        }
        XFreeEventData(display, &ev.xcookie);
        Window root_return, child_return;
        int root_x_return, root_y_return;
        int win_x_return, win_y_return;
        unsigned int mask_return;
        int retval = XQueryPointer(display, rootWindow, &root_return, &child_return,
                                           &root_x_return, &root_y_return,
                                           &win_x_return, &win_y_return,
                                           &mask_return);
        if (!retval) {
            continue;
        }
        int local_x, local_y;
        XTranslateCoordinates(display, rootWindow, appWindow,
                              root_x_return, root_y_return,
                              &local_x, &local_y, &child_return);
        QPoint cursorPoint(local_x, local_y);
        QPoint absPosition(root_x_return, root_y_return);
//        if (canvasRect->contains(cursorPoint)) {
//            emit mouseEnter();
//        } else {
//            emit mouseLeave();
//        }
        emit mouseEvent(cursorPoint, absPosition);
        QThread::msleep(100);
    }
}

MouseEventThread::~MouseEventThread() {
    XCloseDisplay(display);
}
