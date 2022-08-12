//
// Created by lsk on 7/25/22.
//

#include "widget.h"

using namespace std;

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->setGeometry(0,
                      0,
                      QApplication::desktop()->width(),
                      QApplication::desktop()->height());
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint
    |Qt::WindowStaysOnTopHint
    |Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    XShapeCombineRectangles(QX11Info::display(),
                            this->winId(),
                            ShapeInput, 0, 0, nullptr, 0, ShapeSet, YXBanded);
    this->widget = new QLive2dWidget(this);
    this->widget->resize(300, 300);
    this->widget->move(0, this->height() - 300);
    connect(this->widget, SIGNAL(initialized(QLive2dWidget*)), this, SLOT(live2dInitialized(QLive2dWidget*)));
    this->th = new MouseEventThread(this->geometry(), this->winId(), this);
    connect(this->th, SIGNAL(mouseEvent(QPoint, QPoint)), this, SLOT(mouseEvent(QPoint, QPoint)), Qt::QueuedConnection);
    this->th->start();
}

Widget::~Widget() {
    delete this->widget;
    delete this->th;
}

QPoint Widget::transformPoint(QPoint in) {
    int x = in.x();
    int y = in.y();
    if (x > 300) {
        x = 300;
    }
//    y = this->height() - y;
//    if (y > 300) {
//        y = 300;
//    }
    y = y - 100 < 0 ? y : y - 100;
    return QPoint(x, y);
}

void Widget::live2dInitialized(QLive2dWidget *wid) {
    //wid->setResDir("Resource");
    widget->setModel("WY6");
}
void Widget::mouseEvent(QPoint rel, QPoint abs) {
    //cout<<"rel: "<<rel.x()<<", "<<rel.y()<<endl;
    //cout<<"abs: "<<abs.x()<<", "<<abs.y()<<endl;
    widget->mouseMove(this->transformPoint(rel));
    if (widget->geometry().contains(rel) && widget->isVisible()) {
        widget->hide();
    }
    if (!widget->geometry().contains(rel) && !widget->isVisible()) {
        widget->show();
    }
}
