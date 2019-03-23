#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QtCore/QFileSystemWatcher>
#include "Index.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleStartButton();
    void changeStatus(QString);
    void findFiles();
    void showResult(QVector<QString>);

signals:
    void startIndexing(QString rootDir);
    void findFiles(QString string);

private:
    Ui::MainWindow *ui;
    QString rootPath;
    QFileSystemWatcher watcher;

};


#endif // MAINWINDOW_H
