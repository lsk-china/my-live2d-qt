#include "mouseEventThread.h"

bool filterWheelEvent(int detail) {
    return detail != WheelUp && detail != WheelDown && detail != WheelLeft && detail != WheelRight;
}

MouseEventThread::MouseEventThread(QRect screenRect, int winID, QObject *parent) : QThread(parent) {
    rootWindow = XRootWindow(display, 0);
    int event, error;
    XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error);
    // unsigned char mask_bytes[(XI_LASTEVENT + 7) / 8] = {0};
    // XISetMask(mask_bytes, XI_RawMotion);
    // XISetMask(mask_bytes, XI_ButtonPress);
    // XISetMask(mask_bytes, XI_ButtonRelease);
    // XIEventMask evmasks[1];
    // evmasks[0].deviceid = XIAllMasterDevices;
    // evmasks[0].mask_len = sizeof(mask_bytes);
    // evmasks[0].mask = mask_bytes;
    // XISelectEvents(display, rootWindow, evmasks, 2);
    XIEventMask mask[1];
    XIEventMask *m = &mask[0];
    m->deviceid = XIAllDevices;
    m->mask_len = XIMaskLen(XI_LASTEVENT);
    m->mask = static_cast<unsigned char *>(calloc(m->mask_len, sizeof(char)));
    XISetMask(m->mask, XI_ButtonPress);
    XISetMask(m->mask, XI_ButtonRelease);
    XISetMask(m->mask, XI_Motion);
    XISelectEvents(display, rootWindow, mask, 1);
    XSync(display, 0);
    this->appWindow = (Window) winID;
}

void MouseEventThread::run() {
    qDebug() << "Mouse event thread started";
    XEvent ev;
    int relX, relY, absX, absY;
    while (true) {
        XNextEvent(display, &ev);  
        if(ev.xcookie.type != GenericEvent || ev.xcookie.extension != xi_opcode) {
            continue;
        }
        XGetEventData(display, &ev.xcookie);
        switch (ev.xcookie.evtype) {
            case XI_Motion:
                if (queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mouseEvent(QPoint(relX, relY), QPoint(absX, absY));
                break;
            case XI_ButtonPress:
                printPressedButtons(((XIDeviceEvent *) ev.xcookie.data)->buttons);
                if (filterWheelEvent(((XIDeviceEvent *) ev.xcookie.data)->detail)) { // check if left button is pressed. 1 mean left button.
                    break;
                }
                qDebug() << "left press";
                if (queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                qDebug() << "emit mousePress";
                emit mousePress(QPoint(relX, relY), QPoint(absX, absY));
                break;
            case XI_ButtonRelease:
                if (!XIMaskIsSet(((XIDeviceEvent *) ev.xcookie.data)->buttons.mask, 1)) { // check if left button is released. 1 mean left button.
                    break;
                }
                if (queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mouseRelease(QPoint(relX, relY), QPoint(absX, absY));
                break;
        }
        XFreeEventData(display, &ev.xcookie);
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
    if (retval != 1) {
        return 1;
    }
    int local_x, local_y;
    XTranslateCoordinates(display, rootWindow, appWindow,
                          root_x_return, root_y_return,
                          &local_x, &local_y, &child_return);
    relX = local_x;
    relY = local_y;
    absX = root_x_return;
    absY = root_y_return;
    return 0;
}
void MouseEventThread::printPressedButtons(XIButtonState buttons) {
    for (int i = 0; i < buttons.mask_len * 8; i++) {
        if (XIMaskIsSet(buttons.mask, i)) {
            qDebug() << i;
        }
    }
}