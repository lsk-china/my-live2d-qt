#include "mouseEventThread.h"

MouseEventThread::MouseEventThread(QRect screenRect, int winID, QObject *parent) : QThread(parent) {
//    rootWindow = XRootWindow(display, 0);
//    int event, error;
//    XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error);
//    // unsigned char mask_bytes[(XI_LASTEVENT + 7) / 8] = {0};
//    // XISetMask(mask_bytes, XI_RawMotion);
//    // XISetMask(mask_bytes, XI_ButtonPress);
//    // XISetMask(mask_bytes, XI_ButtonRelease);
//    // XIEventMask evmasks[1];
//    // evmasks[0].deviceid = XIAllMasterDevices;
//    // evmasks[0].mask_len = sizeof(mask_bytes);
//    // evmasks[0].mask = mask_bytes;
//    // XISelectEvents(display, rootWindow, evmasks, 2);
//    XIEventMask mask[1];
//    XIEventMask *m = &mask[0];
//    m->deviceid = XIAllDevices;
//    m->mask_len = XIMaskLen(XI_LASTEVENT);
//    m->mask = static_cast<unsigned char *>(calloc(m->mask_len, sizeof(char)));
//    XISetMask(m->mask, XI_ButtonPress);
//    XISetMask(m->mask, XI_ButtonRelease);
//    XISetMask(m->mask, XI_Motion);
//    XISelectEvents(display, rootWindow, mask, 1);
//    XSync(display, 0);
//    this->appWindow = (Window) winID;
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
    XRecordDisableContext(controlDisplay, ctx);
    XRecordFreeContext(controlDisplay, ctx);
    XFree(rr);
    XCloseDisplay(controlDisplay);
    XCloseDisplay(dataDisplay);
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
                emit mousePress(QPoint(relX, relY), QPoint(absX, absY));
            }
            break;
        case ButtonRelease:
            if (buttonCode == 1) {
                if (queryCursor(relX, relY, absX, absY)) {
                    break;
                }
                emit mouseRelease(QPoint(relX, relY), QPoint(absX, absY));
            }
            break;
        case MotionNotify:
            if (queryCursor(relX, relY, absX, absY)) {
                break;
            }
            emit mouseEvent(QPoint(relX, relY), QPoint(absX, absY));
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
