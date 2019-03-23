#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Index.h"

#include <QCommonStyle>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    auto* index = new Index;
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    connect(ui->startButton, SIGNAL(released()), this, SLOT(handleStartButton()));
    connect(this, &MainWindow::startIndexing, index, &Index::startIndexing);
    connect(index, &Index::changeStatus, this, &MainWindow::changeStatus);
    connect(ui->findButton, SIGNAL(released()),this, SLOT(findFiles()));
    connect(this, SIGNAL(findFiles(QString)), index, SLOT(findFilesStupid(QString)));
    connect(index, SIGNAL(ready(QVector<QString>)), this, SLOT(showResult(QVector<QString>)));
    ui->statusLabel->setText(QString("waiting directory..."));

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::handleStartButton() {
    rootPath = QFileDialog::getExistingDirectory(this, "Select Directory", QString(),
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->statusLabel->setText(QString("indexing..."));
    if (!rootPath.isEmpty()) {
        ui->resultListWidget->clear();
        emit startIndexing(rootPath);
    }
}

void MainWindow::changeStatus(QString status) {
    ui->statusLabel->setText(status);
}

void MainWindow::findFiles(){
    ui->resultListWidget->clear();
    QString stt = ui->queryEdit->text();
    std::string str = stt.toStdString();
    ui->countLabel->setText(QString("Total: 0"));
    ui->statusLabel->setText(QString("Finding"));
    emit findFiles(ui->queryEdit->text());
}
//abaaba
void MainWindow::showResult(QVector<QString> ans) {
    ui->resultListWidget->clear();
    for (auto &s : ans) {
        auto *item = new QListWidgetItem(ui->resultListWidget);
        ui->resultListWidget->addItem(item);
        QDir file(s);
        item->setText(file.absolutePath());
    }
    ui->countLabel->setText(QString("Total: ") + QString::number(ans.size()));
    ui->statusLabel->setText(QString("Finded"));
}