#ifndef QQGLWIDGET_H
#define QQGLWIDGET_H

#define QCOREEVENT_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

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
    void mouseMove(QMouseEvent *ev);

    inline static float ratio;
    inline static QElapsedTimer elapsedTimer;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateMotions();

signals:
    void initialized(QLive2dWidget *wid);
};
#endif // QLIVE2DWIDGET_H
