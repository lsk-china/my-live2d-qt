//
// Created by lsk on 10/25/22.
//

#include "configDialog.h"

#include <utility>

ConfigDialog::ConfigDialog(QString modelNameIn, QString resourceDir, QWidget *parent) : QDialog(parent) {
    this->ui = new Ui::Dialog();
    this->ui->setupUi(this);
    this->modelName = std::move(modelNameIn);
    this->resourceDir = std::move(resourceDir);
    this->ui->label_3->setText(this->resourceDir);
    vector<string> models = this->listModels();
    for (string model : models) {
        this->ui->comboBox->addItem(STQ(model));
    }
    this->ui->comboBox->setCurrentText(this->modelName);
    connect(this->ui->pushButton_2, &QPushButton::clicked, this, [this](bool clicked) {
        if (clicked) {
            okPressed(this->modelName, this->resourceDir);
        }
    });
    connect(this->ui->comboBox, &QComboBox::currentTextChanged, this, [this](QString model) {
        this->modelName = std::move(model);
    });
    connect(this->ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        this->hide();
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



vector<string> ConfigDialog::listModels() {
    vector<string> result;
    for (const auto & entry : std::filesystem::directory_iterator(this->resourceDir.toStdString())) {
        if (entry.is_directory()) {
            result.push_back(entry.path().filename());
        }
    }
    return result;
}

ConfigDialog::~ConfigDialog() noexcept {
    delete ui;
    ui = nullptr;
}