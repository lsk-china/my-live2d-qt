//
// Created by lsk on 7/25/22.
//

#ifndef QDESKTOPPET_2_CMAKE_WIDGET_H
#define QDESKTOPPET_2_CMAKE_WIDGET_H
#include <QtX11Extras/QX11Info>
#include "QLive2dWidget.hpp"
#include "mouseEventThread.h"
#include <X11/extensions/shape.h>
// Undef some marcos to prevent the fucking clash between qt and x.
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted
#undef min
#undef max

#include <QDebug>
#include <QActionGroup>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QEvent>
#include <QRect>

#include "configDialog.h"

using namespace std;

#define STQ(s) QString::fromStdString(s)
#define QTC(s) s.toStdString().c_str()

class Widget : public QWidget{
    Q_OBJECT
public:
    explicit Widget(QWidget *newModelName = nullptr);
    ~Widget();
    void setModel(string resourceDir, string modelName);
    void setWidgetPosition(bool widgetOnLeft);
private:
    QLive2dWidget *widget;
    MouseEventThread *th;
    bool initialized = false;
    bool hideOnHover = true;
    bool shouldShow = true;
    ConfigDialog *configDialog;
    string resourceDir = "/data/lsk/live2d/Resources/";
    string modelName = "WY6";
    bool widgetOnLeft = true;
//    vector<string> listModels();
public slots:
    void live2dInitialized(QLive2dWidget *wid);
    void mouseEvent(QPoint rel, QPoint abs);
    void mousePress(QPoint rel, QPoint abs);
    void mouseRelease(QPoint rel, QPoint abs);
};

#endif //QDESKTOPPET_2_CMAKE_WIDGET_H
