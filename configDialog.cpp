//
// Created by lsk on 10/25/22.
//

#include "configDialog.h"

#include <utility>

ConfigDialog::ConfigDialog(configuration currentConfiguration, QWidget *parent) : QDialog(parent) {
    this->ui = new Ui::Dialog();
    this->ui->setupUi(this);
    this->currentConfiguration = currentConfiguration;
//    this->modelName = std::move(modelNameIn);
//    this->resourceDir = std::move(resourceDir);
//    this->ui->label_3->setText(this->resourceDir);
//    vector<string> models = this->listModels();
//    for (const string& model : models) {
//        this->ui->comboBox->addItem(STQ(model));
//    }
//    this->ui->comboBox->setCurrentText(this->modelName);
//    connect(this->ui->pushButton_2, &QPushButton::clicked, this, [this](bool clicked) {
//        okPressed(this->modelName, this->resourceDir);
//        this->hide();
//    });
//    connect(this->ui->comboBox, &QComboBox::currentTextChanged, this, [this](QString model) {
//        this->modelName = std::move(model);
//    });
//    connect(this->ui->pushButton_3, &QPushButton::clicked, this, [this]() {
//        this->hide();
//    });
//    connect(this->ui->pushButton, &QPushButton::clicked, this, [this]() {
//        this->resourceDir = QFileDialog::getExistingDirectory(this, "Choose resource directory", this->resourceDir);
//        this->ui->label_3->setText(this->resourceDir);
//        this->ui->comboBox->clear();
//        vector<string> models = this->listModels();
//        for (string model : models) {
//            this->ui->comboBox->addItem(modelName);
//        }
//    });
    vector<string> models = this->listModels();
    for (const string& model : models) {
        this->ui->comboBox->addItem(STQ(model));
    }
    this->ui->comboBox->setCurrentText(this->currentConfiguration.getModelName());
    connect(this->ui->pushButton_2, &QPushButton::clicked, this, [this](bool clicked) {
        emit okPressed(this->currentConfiguration);
        this->hide();
    });
    connect(this->ui->comboBox, &QComboBox::currentTextChanged, this, [this](QString model) {
        this->currentConfiguration.setModelName(model);
    });
    connect(this->ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        this->hide();
    });
    connect(this->ui->pushButton, &QPushButton::clicked, this, [this]() {
        this->currentConfiguration.setResourceDir(QFileDialog::getExistingDirectory(this, "Choose resource directory", this->currentConfiguration.getResourceDir()));
        this->ui->label_3->setText(this->currentConfiguration.getResourceDir());
        vector<string> models = this->listModels();
        for (const string& model : models) {
            this->ui->comboBox->addItem(QString::fromStdString(model));
        }
    });
    resize(670, 140);
    setWindowModality(Qt::WindowModality::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose, false);
}

vector<string> ConfigDialog::listModels() {
    vector<string> result;
    for (const auto & entry : std::filesystem::directory_iterator(this->currentConfiguration.getModelName().toStdString())) {
        if (entry.is_directory()) {
            result.push_back(entry.path().filename());
        }
    }
    return result;
}

ConfigDialog::~ConfigDialog() noexcept {
    delete ui;
    ui = nullptr;
    this->currentConfiguration.save();
}