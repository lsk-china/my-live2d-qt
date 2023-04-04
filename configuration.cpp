//
// Created by lsk on 3/23/23.
//

#include "configuration.h"

bool configuration::isHideOnHover() const {
    return hideOnHover;
}

void configuration::setHideOnHover(bool hideOnHover) {
    configuration::hideOnHover = hideOnHover;
}

const QString &configuration::getResourceDir() const {
    return resourceDir;
}

void configuration::setResourceDir(const QString &resourceDir) {
    configuration::resourceDir = resourceDir;
}

const QString &configuration::getModelName() const {
    return modelName;
}

void configuration::setModelName(const QString &modelName) {
    configuration::modelName = modelName;
}

bool configuration::isWidgetOnLeft() const {
    return widgetOnLeft;
}

void configuration::setWidgetOnLeft(bool widgetOnLeft) {
    configuration::widgetOnLeft = widgetOnLeft;
}

double configuration::getMouseSensibility() const {
    return mouseSensibility;
}

void configuration::setMouseSensibility(double mouseSensibility) {
    configuration::mouseSensibility = mouseSensibility;
}

configuration::configuration() {

    this->settings = new QSettings(QSettings::UserScope, "lsk", "QDesktopPet");
    this->settings->beginGroup("Widget");
    this->hideOnHover = this->settings->value("hideOnHover", true).toBool();
    this->widgetOnLeft = this->settings->value("widgetOnLeft", true).toBool();
    this->mouseSensibility = this->settings->value("mouseSensibility", 1.0).toDouble();
    this->widgetSize = this->settings->value("size", QSize(200, 200)).toSize();
    this->settings->endGroup();
    this->settings->beginGroup("Resource");
    this->modelName = this->settings->value("modelName", "WY6").toString();
    this->resourceDir = this->settings->value("resourceDir", "/data/lsk/live2d/Resources/").toString();
    this->settings->endGroup();
}

configuration::~configuration() {
//    delete this->settings;
}

void configuration::save() {
    this->settings->beginGroup("Widget");
    this->settings->setValue("hideOnHover", this->hideOnHover);
    this->settings->setValue("widgetOnLeft", this->widgetOnLeft);
    this->settings->setValue("mouseSensibility", this->mouseSensibility);
    this->settings->setValue("size", this->widgetSize);
    this->settings->endGroup();
    this->settings->beginGroup("Resource");
    this->settings->setValue("modelName", this->modelName);
    this->settings->setValue("resourceDir", this->resourceDir);
    this->settings->endGroup();
}

const QSize &configuration::getWidgetSize() const {
    return widgetSize;
}

void configuration::setWidgetSize(const QSize &widgetSize) {
    configuration::widgetSize = widgetSize;
}
