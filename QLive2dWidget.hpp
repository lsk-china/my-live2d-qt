#ifndef QQGLWIDGET_H
#define QQGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QList>
#include <iostream>

using namespace std;

class QLive2dWidget :
        public QOpenGLWidget
{
    Q_OBJECT
public:
    QLive2dWidget(QWidget *parent = nullptr);
    void initializeGL()override;
    void resizeGL(int width, int height)override;
    void paintGL()override;
    void clear();
    void setResDir(string resDir);
    void setModel(string model);
    void mouseMove(QPoint rel);

    inline static float ratio;
    inline static float ratio_x = 1;
    inline static float ratio_y = 1;
    inline static QElapsedTimer elapsedTimer;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateMotions();
private:
    void calcRatios();
    std::string resourceDir = "Resources";

signals:
    void initialized(QLive2dWidget *wid);
};
#endif // QLIVE2DWIDGET_H
