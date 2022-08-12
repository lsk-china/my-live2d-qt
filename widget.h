//
// Created by lsk on 7/25/22.
//

#ifndef QDESKTOPPET_2_CMAKE_WIDGET_H
#define QDESKTOPPET_2_CMAKE_WIDGET_H

#define QCOREEVENT_H
#define QACTIONGROUP_H

#include <QWidget>
#include "QLive2dWidget.hpp"
#include <QApplication>
#include <QDesktopWidget>
#include <X11/extensions/shape.h>
#include <QtX11Extras/QX11Info>
#include <QPoint>
//#include <QDebug>
#include <iostream>
#include "mouseEventThread.h"
#include <QSystemTrayIcon>
#include <QMenu>


using namespace std;

class Widget : public QWidget{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QLive2dWidget *widget;
    MouseEventThread *th;
    bool initialized = false;
    bool hideOnHover = true;
    bool shouldShow = true;
    QPoint transformPoint(QPoint in);
public slots:
    void live2dInitialized(QLive2dWidget *wid);
    void mouseEvent(QPoint rel, QPoint abs);
};

#endif //QDESKTOPPET_2_CMAKE_WIDGET_H
