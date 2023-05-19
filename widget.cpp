//
// Created by lsk on 7/25/22.
//

#include "widget.h"

using namespace std;

Widget::Widget(configuration configuration, QWidget *parent) : QWidget(parent) {
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
    this->currentConfiguration = configuration;
    // 菜单初始化
    auto *icon = new QSystemTrayIcon(this);
    icon->setToolTip("Live2d");
    icon->setIcon(QIcon::fromTheme("show_table_row"));
    auto *trayIconMenu = new QMenu(this);
    auto *enableHideOnHoverAction = new QAction("悬浮隐藏", this);
    enableHideOnHoverAction->setCheckable(true);
    enableHideOnHoverAction->setChecked(true);
    connect(enableHideOnHoverAction, &QAction::toggled, this, [this](bool checked) {
       this->currentConfiguration.setHideOnHover(checked);
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
    this->configDialog = new ConfigDialog(this->currentConfiguration, nullptr);
    connect(this->configDialog, &ConfigDialog::okPressed, this, [this](class configuration conf) {
        this->currentConfiguration = conf;
        this->th->setMouseSensibility(conf.getMouseSensibility());
        delete this->widget;
        this->widget = new QLive2dWidget(this);
        this->widget->resize(currentConfiguration.getWidgetSize());
        this->widget->move(0, this->height() - this->widget->height());
        connect(this->widget, SIGNAL(initialized(QLive2dWidget*)), this, SLOT(live2dInitialized(QLive2dWidget*)));
    });
    auto *configOption = new QAction("设置", this);
    connect(configOption, &QAction::triggered, this, [this]() {
        this->configDialog->show();
    });
    trayIconMenu->addAction(configOption);
    auto *quitAction = new QAction("退出", this);
    quitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(quitAction, &QAction::triggered, this, &QCoreApplication::quit, Qt::QueuedConnection);
    trayIconMenu->addAction(quitAction);
    icon->setContextMenu(trayIconMenu);
    icon->setVisible(true);
    icon->show();
    // Live2d组件初始化
    this->widget = new QLive2dWidget(this);
    this->widget->resize(currentConfiguration.getWidgetSize());
    this->widget->move(0, this->height() - this->widget->height());
    connect(this->widget, SIGNAL(initialized(QLive2dWidget*)), this, SLOT(live2dInitialized(QLive2dWidget*)));
    // 开启鼠标事件监听线程
    this->th = new MouseEventThread(this->geometry(), this->winId(), this->currentConfiguration.getMouseSensibility(), this);
    connect(this->th, SIGNAL(mouseEvent(QPoint,QPoint)), this, SLOT(mouseEvent(QPoint,QPoint)), Qt::QueuedConnection);
    connect(this->th, &MouseEventThread::mousePress, this, &Widget::mousePress, Qt::QueuedConnection);
    connect(this->th, &MouseEventThread::mouseRelease, this, &Widget::mouseRelease, Qt::QueuedConnection);
    this->th->start();
    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, [this]() {this->th->exit();});
}

Widget::~Widget() {
    delete this->widget;
    delete this->th;
    delete this->configDialog;
    this->widget = nullptr;
    this->th = nullptr;
    this->configDialog = nullptr;
}

void Widget::live2dInitialized(QLive2dWidget *wid) {
    cout << "Starting with model " << this->currentConfiguration.getModelName().toStdString() << " in " << this->currentConfiguration.getResourceDir().toStdString() << "." << endl;
    wid->setResDir(this->currentConfiguration.getResourceDir().toStdString());
    wid->setModel(this->currentConfiguration.getModelName().toStdString());
    this->initialized = true;
}
void Widget::mouseEvent(QPoint rel, QPoint raw) {
    //cout<<"rel: "<<rel.x()<<", "<<rel.y()<<endl;
    //cout<<"abs: "<<raw.x()<<", "<<raw.y()<<endl;
    widget->mouseMove(rel);
    //widget->mouseMove(rel);
    if (this->currentConfiguration.isHideOnHover()) {
        if (widget->geometry().contains(raw) && widget->isVisible()) {
            widget->hide();
        }
        if (!widget->geometry().contains(raw) && !widget->isVisible()) {
            widget->show();
        }
    }
}

void Widget::setModel(std::string resourceDir, std::string modelName) {
    this->currentConfiguration.setResourceDir(QString::fromStdString(resourceDir));
    this->currentConfiguration.setModelName(QString::fromStdString(modelName));
}

void Widget::setWidgetPosition(bool widgetOnLeft) {
    if (!widgetOnLeft) {
        this->widget->move(this->width() - 300, this->height() - 300);
    }
}

void Widget::mousePress(QPoint rel, QPoint raw) {
    if (this->widget->geometry().contains(rel)) {
        if (this->currentConfiguration.isHideOnHover()) {
            this->widget->mousePress(QPoint(rel.x(), this->height() - rel.y()));
        } else {
            int spaceBetweenLeftAndWidget = this->width() - this->widget->width();
            this->widget->mousePress(QPoint(rel.x() - spaceBetweenLeftAndWidget, this->height() - rel.y()));
        }
    }
}

void Widget::mouseRelease(QPoint rel, QPoint raw) {
    if (this->widget->geometry().contains(rel)) {
        if (this->currentConfiguration.isHideOnHover()) {
            this->widget->mouseRelease(QPoint(rel.x(), this->height() - rel.y()));
        } else {
            int spaceBetweenLeftAndWidget = this->width() - this->widget->width();
            this->widget->mouseRelease(QPoint(rel.x() - spaceBetweenLeftAndWidget, this->height() - rel.y()));
        }
    }
}
