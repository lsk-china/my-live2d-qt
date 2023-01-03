//
// Created by lsk on 7/25/22.
//

#include "widget.h"

using namespace std;

Widget::Widget(QWidget *parent) : QWidget(parent) {
    // 初始化窗口，设置鼠标事件穿透
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
    // 菜单初始化
    auto *icon = new QSystemTrayIcon(this);
    icon->setToolTip("Live2d");
    icon->setIcon(QIcon::fromTheme("show_table_row"));
    auto *trayIconMenu = new QMenu(this);
    auto *enableHideOnHoverAction = new QAction("悬浮隐藏", this);
    enableHideOnHoverAction->setCheckable(true);
    enableHideOnHoverAction->setChecked(true);
    connect(enableHideOnHoverAction, &QAction::toggled, this, [this](bool checked) {
       this->hideOnHover = checked;
    });
    trayIconMenu->addAction(enableHideOnHoverAction);
    auto *showAction = new QAction("显示", this);
    showAction->setCheckable(true);
    showAction->setChecked(true);
    connect(showAction, &QAction::toggled, this, [this](bool checked){
        if (checked) {
            this->show();
        } else {
            this->hide();
        }
    });
    trayIconMenu->addAction(showAction);
    this->configDialog = new ConfigDialog(this);
    auto *configOption = new QAction("设置", this);
    connect(configOption, &QAction::toggled, this, [this]() {
        this->configDialog->show();
    });
    trayIconMenu->addAction(configOption);
    auto *quitAction = new QAction("退出", this);
    quitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(quitAction, &QAction::triggered, this, &QCoreApplication::quit);
    trayIconMenu->addAction(quitAction);
    icon->setContextMenu(trayIconMenu);
    icon->setVisible(true);
    icon->show();
    // Live2d组件初始化
    this->widget = new QLive2dWidget(this);
    this->widget->resize(300, 300);
    this->widget->move(0, this->height() - 300);
    connect(this->widget, SIGNAL(initialized(QLive2dWidget*)), this, SLOT(live2dInitialized(QLive2dWidget*)));
    // 开启鼠标事件监听线程
    this->th = new MouseEventThread(this->geometry(), this->winId(), this);
    connect(this->th, SIGNAL(mouseEvent(QPoint,QPoint)), this, SLOT(mouseEvent(QPoint,QPoint)), Qt::QueuedConnection);
    connect(this->th, &MouseEventThread::mousePress, this, &Widget::mousePress, Qt::QueuedConnection);
    connect(this->th, &MouseEventThread::mouseRelease, this, &Widget::mouseRelease, Qt::QueuedConnection);
    this->th->start();
}

Widget::~Widget() {
    delete this->widget;
    delete this->th;
    delete this->configDialog;
    this->widget = nullptr;
    this->th = nullptr;
    this->configDialog = nullptr;
}

QPoint Widget::transformPoint(QPoint in) const {
    if (this->widgetOnLeft) {
        int x = in.x();
        int y = in.y();
        if (x > 300) {
            x = 300;
        }
//    y = this->height() - y;
//    if (y > 300) {
//        y = 300;
//    }
        y = y - 500 < 0 ? y : y - 500;
        return {x, y};
    } else {
        int x = in.x();
        int y = in.y();
//        if (x > 300) {
//            x = 300;
//        }
//    y = this->height() - y;
//    if (y > 300) {
//        y = 300;
//    }
        y = y - 500 < 0 ? y : y - 500;
        return {x, y};
    }
}

//vector<string> Widget::listModels() {
//    DIR *modelDir = opendir(this->resourceDir.c_str());
//    struct dirent *ptr;
//    vector<string> result;
//    while ((ptr = readdir(modelDir)) != nullptr) {
//        if (ptr->d_type == DT_DIR) {
//            result.emplace_back(ptr->d_name);
//        }
//    }
//    closedir(modelDir);
//    return result;
//}

void Widget::live2dInitialized(QLive2dWidget *wid) {
    cout << "Starting with model " << this->modelName << " in " << this->resourceDir << "." << endl;
    wid->setResDir(this->resourceDir);
    widget->setModel(this->modelName);
    this->initialized = true;
}
void Widget::mouseEvent(QPoint rel, QPoint abs) {
    //cout<<"rel: "<<rel.x()<<", "<<rel.y()<<endl;
    //cout<<"abs: "<<abs.x()<<", "<<abs.y()<<endl;
    widget->mouseMove(this->transformPoint(rel));
    //widget->mouseMove(rel);
    if (this->hideOnHover) {
        if (widget->geometry().contains(rel) && widget->isVisible()) {
            widget->hide();
        }
        if (!widget->geometry().contains(rel) && !widget->isVisible()) {
            widget->show();
        }
    }
}

void Widget::setModel(std::string resourceDir, std::string modelName) {
    this->resourceDir = resourceDir;
    this->modelName = modelName;
}

void Widget::setWidgetPosition(bool widgetOnLeft) {
    if (!widgetOnLeft) {
        this->widget->move(this->width() - 300, this->height() - 300);
    }
}

void Widget::mousePress(QPoint rel, QPoint abs) {
    if (!this->hasFocus() || !this->widget->isVisible()) {
        return;
    }
    if (this->widget->geometry().contains(rel)) {
        this->widget->mousePress(transformPoint(rel));
    }
}

void Widget::mouseRelease(QPoint rel, QPoint abs) {
    if (!this->hasFocus() || !this->widget->isVisible()) {
        return;
    }
    if (this->widget->geometry().contains(rel)) {
        this->widget->mouseRelease(transformPoint(rel));
    }
}
