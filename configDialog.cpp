//
// Created by lsk on 10/25/22.
//

#include "configDialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent) {
    this->ui = new Ui::Dialog();
    this->ui->setupUi(this);
    connect(this->ui->pushButton_2, &QPushButton::clicked, this, [this](bool clicked) {
        if (clicked) {
            okPressed(this->modelName, this->resourceDir);
        }
    });
    connect(this->ui->comboBox, &QComboBox::currentTextChanged, this, [this](QString model) {
        this->modelName = model;
    });
    connect(this->ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        this->closeDialog();
    });
    connect(this->ui->pushButton, &QPushButton::clicked, this, [this]() {
        this->resourceDir = QFileDialog::getExistingDirectory(this, "Choose resource directory", this->resourceDir);
        this->ui->comboBox->clear();
        vector<string> models = this->listModels();
        for (string model : models) {
            this->ui->comboBox->addItem(modelName);
        }
    });
    resize(670, 140);
    setWindowModality(Qt::WindowModality::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose, false);
}

void ConfigDialog::showDialog(QWidget *parent, QString currentModelName, const QString& currentResourceDir) {
    this->resourceDir = currentResourceDir;
    this->modelName = std::move(currentModelName);
    this->ui->label_3->setText(currentResourceDir);
    vector<string> models = this->listModels();
    for (string model : models) {
        this->ui->comboBox->addItem(modelName);
    }

}

vector<string> ConfigDialog::listModels() {
    DIR *modelDir = opendir(this->resourceDir.toStdString().c_str());
    struct dirent *ptr;
    vector<string> result;
    while ((ptr = readdir(modelDir)) != nullptr) {
        if (ptr->d_type == DT_DIR) {
            result.emplace_back(ptr->d_name);
        }
    }
    closedir(modelDir);
    return result;
}