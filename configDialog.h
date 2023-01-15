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

#include <filesystem>
#define STQ(s) QString::fromStdString(s)

using namespace std;

namespace Ui {
    class Dialog;
}

class ConfigDialog : public QDialog {
Q_OBJECT
public:
    ConfigDialog(QString modelName, QString resourceDir, QWidget *parent = nullptr);
    ~ConfigDialog();
signals:
    void okPressed(QString modelName, QString resourceDir);
private:
    QString modelName;
    QString resourceDir;
    Ui::Dialog *ui;
    vector<string> listModels();
};

#endif //QDESKTOPPET_2_CMAKE_CONFIGDIALOG_H
