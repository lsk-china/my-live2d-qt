#include "live2d.h"

Live2D::Live2D(QWidget *parent)
    : QWebEngineView(parent)
{
    // 窗口属性
    this->setGeometry(0, 0,
                      QApplication::desktop()->width(),
                      QApplication::desktop()->height());
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint
                         |Qt::WindowStaysOnTopHint
                         |Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);

    // 利用X11接口穿透鼠标事件，使其不影响正常操作
    XShapeCombineRectangles(QX11Info::display(),
                            this->winId(),
                            ShapeInput, 0, 0, nullptr, 0, ShapeSet, YXBanded);
    this->page()->setBackgroundColor(Qt::transparent);

    // 默认加载model
    this->setHtml(this->makeHtml("shizuku"));

    // 托盘图标右键菜单
    QAction *shizukuAction = new QAction("shizuku", this);
    shizukuAction->setCheckable(true);
    shizukuAction->setChecked(true);
    connect(shizukuAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("shizuku"));
    });
    QAction *mikuAction = new QAction("miku", this);
    mikuAction->setCheckable(true);
    connect(mikuAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("miku"));
    });
    QAction *haru01Action = new QAction("haru01", this);
    haru01Action->setCheckable(true);
    connect(haru01Action, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("haru01"));
    });
    QAction *haru02Action = new QAction("haru02", this);
    haru02Action->setCheckable(true);
    connect(haru02Action, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("haru02"));
    });
    QAction *hijikiAction = new QAction("hijiki", this);
    hijikiAction->setCheckable(true);
    connect(hijikiAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("hijiki"));
    });
    QAction *tororoAction = new QAction("tororo", this);
    tororoAction->setCheckable(true);
    connect(tororoAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("tororo"));
    });
    QAction *z16Action = new QAction("z16", this);
    z16Action->setCheckable(true);
    connect(z16Action, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("z16"));
    });
    QAction *epsilon2_1Action = new QAction("epsilon2_1", this);
    epsilon2_1Action->setCheckable(true);
    connect(epsilon2_1Action, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("epsilon2_1"));
    });
    QAction *hibikiAction = new QAction("hibiki", this);
    hibikiAction->setCheckable(true);
    connect(hibikiAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("hibiki"));
    });
    QAction *wankoAction = new QAction("wanko", this);
    wankoAction->setCheckable(true);
    connect(wankoAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("wanko"));
    });
    QAction *kazuhaAction = new QAction("kazuha",this);
    kazuhaAction->setCheckable(true);
    connect(kazuhaAction, &QAction::triggered, this, [this](){
        this->setHtml(this->makeHtml("kazuha"));
    });
    QMenu *modelMenu = new QMenu("切换模型", this);
    modelMenu->setIcon(QIcon::fromTheme("view-refresh-symbolic"));
    modelMenu->addAction(shizukuAction);
    modelMenu->addAction(mikuAction);
    modelMenu->addAction(haru01Action);
    modelMenu->addAction(haru02Action);
    modelMenu->addAction(hijikiAction);
    modelMenu->addAction(tororoAction);
    modelMenu->addAction(z16Action);
    modelMenu->addAction(epsilon2_1Action);
    modelMenu->addAction(hibikiAction);
    modelMenu->addAction(wankoAction);
    modelMenu->addAction(kazuhaAction);

    QActionGroup *modelGroup = new QActionGroup(modelMenu);
    modelGroup->setExclusive(true);
    modelGroup->addAction(shizukuAction);
    modelGroup->addAction(mikuAction);
    modelGroup->addAction(haru01Action);
    modelGroup->addAction(haru02Action);
    modelGroup->addAction(hijikiAction);
    modelGroup->addAction(tororoAction);
    modelGroup->addAction(z16Action);
    modelGroup->addAction(epsilon2_1Action);
    modelGroup->addAction(hibikiAction);
    modelGroup->addAction(wankoAction);
    modelGroup->addAction(kazuhaAction);

    QAction *quitAction = new QAction("退出", this);
    quitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(quitAction, &QAction::triggered, this, &QCoreApplication::quit);

    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addMenu(modelMenu);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    // 托盘图标属性
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("Live2D");
    trayIcon->setIcon(QIcon::fromTheme("show_table_row"));
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon, &QSystemTrayIcon::activated, this, [this, trayIcon](){
        if(this->isVisible())
        {
            trayIcon->setIcon(QIcon::fromTheme("hide_table_row"));
            this->hide();
        }
        else
        {
            trayIcon->setIcon(QIcon::fromTheme("show_table_row"));
            this->show();
        }
    });
    trayIcon->setVisible(true);
    trayIcon->show();
}

// 切换model时用到的html
QString Live2D::makeHtml(QString modelname)
{
    QString modelConfig;
    if(modelname == "shizuku")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-shizuku@1.0.5/assets/shizuku.model.json\","
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 190,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "miku")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-miku@1.0.5/assets/miku.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 130,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "haru01")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-haru@1.0.5/01/assets/haru01.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 200,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "haru02")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-haru@1.0.5/02/assets/haru02.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 200,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "hijiki")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-hijiki@1.0.5/assets/hijiki.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 100,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "tororo")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-tororo@1.0.5/assets/tororo.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 100,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "z16")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-z16@1.0.5/assets/z16.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 170,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "epsilon2_1")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-epsilon2_1@1.0.5/assets/Epsilon2.1.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 150,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "hibiki")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-hibiki@1.0.5/assets/hibiki.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 210,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "wanko")
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-wanko@1.0.5/assets/wanko.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 70,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";
    else if(modelname == "kazuha")
        return "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><script src=\"bundle.js\"></script><script src=\"live2dcubismcore.js\"></script></head><body><canvas id=\"live2d\" width=\"500\" height=\"500\"></canvas><script>initDefine(\"/live2d/\", \"\", [\"WY6\"])</script></body></html>";
    else
        modelConfig =   "'model': {"
                          "'jsonPath': \"https://cdn.jsdelivr.net/npm/live2d-widget-model-shizuku@1.0.5/assets/shizuku.model.json\""
                        "},"
                        "'display': {"
                          "'superSample': 2,"
                          "'width': 100,"
                          "'height': 190,"
                          "'position' : \"right\","
                          "'hOffset': 0,"
                          "'vOffset': 0"
                        "},"
                        "'react': {"
                          "'opacityDefault': 1,"
                          "'opacityOnHover': 1"
                        "}";

    QString html = ""
"<!DOCTYPE html>"
  "<html>"
    "<head>"
      "<script src =\"https://cdn.jsdelivr.net/npm/live2d-widget@3.0.5/lib/L2Dwidget.min.js\"></script>"
    "</head>"
    "<body>"
    "<script type=\"text/javascript\">"
      "var currL2Dwidget = new L2Dwidget.init({"
        + modelConfig +
      "});"
    "</script>"
  "</body>"
"</html>";
    return html;
}
