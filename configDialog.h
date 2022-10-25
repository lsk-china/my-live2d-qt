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
#include <dirent.h>

using namespace std;

namespace Ui {
    class Dialog;
}

class ConfigDialog : public QDialog {
Q_OBJECT
public:
    ConfigDialog(QWidget *parent = nullptr);
    ~ConfigDialog();
    void showDialog(QWidget *parent, QString currentModelName, const QString& currentResourceDir);
signals:
    void okPressed(QString modelName, QString resourceDir);
private:
    QString modelName;
    QString resourceDir;
    Ui::Dialog *ui;
    vector<string> listModels();
    void closeDialog();
};

#endif //QDESKTOPPET_2_CMAKE_CONFIGDIALOG_H
