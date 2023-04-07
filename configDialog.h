//
// Created by lsk on 10/25/22.
//

#ifndef QDESKTOPPET_2_CMAKE_CONFIGDIALOG_H
#define QDESKTOPPET_2_CMAKE_CONFIGDIALOG_H

#include "ui_configDialog.h"
#include <QWidget>
#include <QDialog>
#include <QAction>
#include <QFileDialog>
#include "configuration.h"
#include <filesystem>
#define STQ(s) QString::fromStdString(s)

using namespace std;

namespace Ui {
    class Dialog;
}

class ConfigDialog : public QDialog {
Q_OBJECT
public:
    ConfigDialog(configuration currentConfiguration, QWidget *parent = nullptr);
    ~ConfigDialog();
signals:
    void okPressed(configuration result);
private:
    void reloadMouseSensibilityValue();
    Ui::Dialog *ui;
    vector<string> listModels();
    configuration currentConfiguration;
};

#endif //QDESKTOPPET_2_CMAKE_CONFIGDIALOG_H
