# 原项目README
## live2d-qt
使用QWebEngineView在桌面上显示live2d模型。

### 原理
使用QWebEngineView加载一个只包含live2d模型的html页面，设其为全屏，并设置窗口背景透明，忽略鼠标键盘事件。

### 注意
* 使用了`X11`提供的`XShapeCombineRectangles()`实现鼠标键盘操作的穿透，因此程序的通用性不强。
* 设置了鼠标键盘操作的穿透，因此网页上live2d的交互效果无法实现。
* 使用QWebEngineView，测试过程中CPU占用10%以上，影响较大。
* 托盘图标左键点击可隐藏/显示，右键切换模型或者退出。

### 相关链接
该程序的最重要部分其实是live2d的js部分，直接引用了以下项目提供的链接：
* [live2d-widget.js](https://github.com/xiazeyu/live2d-widget.js)
* [live2d-widget-models](https://github.com/xiazeyu/live2d-widget-models)

# 我准备进行的修改
* 添加万叶的Live2D V3 模型
* 在新的线程里面通过X11 XInput监听鼠标事件 实现当鼠标滑动到模型上方时隐藏模型
* 通过上面的方法 使模型能够和鼠标交互
* 使用Live2D Cubism Framework Native 重构（？

# 借物表
* 万叶的模型来自 [Bilibili](https://www.bilibili.com/video/BV1xq4y1k7QR)

# V2.0

基本功能已经实现，离release不远了（话说似乎除了我也没人关注这个项目）

变动：

- 弃用占用奇高的QWebEngineView，完全使用基于OpenGL的Live2d Cubism Framework for Native实现

- 鼠标交互（虽然有点傻）

- 可控制鼠标在模型上是否隐藏

  

### 构建

需要：

- libLive2dWidget.a libFramework.a [仓库](https://github.com/lsk-china/QtLive2d)

  注意，这里的Framework是修改过的，不可以用官方提供的替代。

- libLive2DCubismCore.so 到live2d官网可下载

先cmake生成构建目录，把这些库文件放到构建目录里面，把你的模型放到构建目录/Resources下面，把widget.cpp中第87行的模型改成你自己的模型，然后编译运行即可。

### TODO

- 设置资源目录，模型选择
- 重构代码以支持wayland
