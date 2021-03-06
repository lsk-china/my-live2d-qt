#ifndef LIVE2D_H
#define LIVE2D_H

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QtX11Extras/QX11Info>
#include <QWebEngineView>
#include <X11/extensions/shape.h>
#include <QMouseEvent>
#include <QRect>
#include "mouseEventThread.h"
#include <QDebug>
#include <QEvent>

class Live2D : public QWebEngineView
{
    Q_OBJECT
public:
    Live2D(QWidget *parent = nullptr);

private:
    QString makeHtml(QString modelname);

public slots:
    void mouseEnter();
    void mouseLeave();
    void mouseEvent(QPoint relPosition, QPoint absPosition);
};

#endif // LIVE2D_H
