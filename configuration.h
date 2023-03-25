//
// Created by lsk on 3/23/23.
//

#ifndef QDESKTOPPET_2_CMAKE_CONFIGURATION_H
#define QDESKTOPPET_2_CMAKE_CONFIGURATION_H

#include <QSettings>
#include <QApplication>
#include <QSize>

class configuration {
public:
    configuration();
    ~configuration();

    void save();

    [[nodiscard]] bool isHideOnHover() const;

    void setHideOnHover(bool hideOnHover);

    [[nodiscard]] const QString &getResourceDir() const;

    void setResourceDir(const QString &resourceDir);

    [[nodiscard]] const QString &getModelName() const;

    void setModelName(const QString &modelName);

    [[nodiscard]] bool isWidgetOnLeft() const;

    void setWidgetOnLeft(bool widgetOnLeft);

    [[nodiscard]] double getMouseSensibility() const;

    void setMouseSensibility(double mouseSensibility);

    [[nodiscard]] const QSize &getWidgetSize() const;

    void setWidgetSize(const QSize &widgetSize);

private:
    bool hideOnHover;
    QString resourceDir;
    QString modelName;
    bool widgetOnLeft;
    double mouseSensibility;
    QSize widgetSize;

    QSettings *settings;
};


#endif //QDESKTOPPET_2_CMAKE_CONFIGURATION_H
