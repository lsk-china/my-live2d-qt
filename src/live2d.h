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

class Live2D : public QWebEngineView
{
    Q_OBJECT
public:
    Live2D(QWidget *parent = nullptr);

private:
    QString makeHtml(QString modelname);
    QRect *canvasRect;

protected:
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // LIVE2D_H
