//
// Created by lsk on 7/25/22.
//

#ifndef QDESKTOPPET_2_CMAKE_WIDGET_H
#define QDESKTOPPET_2_CMAKE_WIDGET_H

// I want to use QActionGroup as a model selector, but there is something wrong with my qt environment and I can't use it...

#define QCOREEVENT_H
#define QACTIONGROUP_H
#define QDIR_H

#include <QWidget>
#include "QLive2dWidget.hpp"
#include <QApplication>
#include <QDesktopWidget>
#include <X11/extensions/shape.h>
#include <QtX11Extras/QX11Info>
#include <QPoint>
#include <iostream>
#include "mouseEventThread.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include "configDialog.h"

using namespace std;

class Widget : public QWidget{
    Q_OBJECT
public:
    Widget(QWidget *newModelName = nullptr);
    ~Widget();
private:
    QLive2dWidget *widget;
    MouseEventThread *th;
    bool initialized = false;
    bool hideOnHover = true;
    bool shouldShow = true;
    ConfigDialog *configDialog;
    string resourceDir = "/data/lsk/live2d/Resources/";
    string modelName = "WY6";
    static QPoint transformPoint(QPoint in);
    vector<string> listModels();
public slots:
    void live2dInitialized(QLive2dWidget *wid);
    void mouseEvent(QPoint rel, QPoint abs);
};

#endif //QDESKTOPPET_2_CMAKE_WIDGET_H
