/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *directoryLabel;
    QListWidget *resultListWidget;
    QLabel *countLabel;
    QLabel *statusLabel;
    QPushButton *startButton;
    QLineEdit *queryEdit;
    QPushButton *findButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(553, 405);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        directoryLabel = new QLabel(centralwidget);
        directoryLabel->setObjectName(QString::fromUtf8("directoryLabel"));

        gridLayout->addWidget(directoryLabel, 1, 0, 1, 2);

        resultListWidget = new QListWidget(centralwidget);
        resultListWidget->setObjectName(QString::fromUtf8("resultListWidget"));

        gridLayout->addWidget(resultListWidget, 4, 0, 1, 2);

        countLabel = new QLabel(centralwidget);
        countLabel->setObjectName(QString::fromUtf8("countLabel"));

        gridLayout->addWidget(countLabel, 5, 0, 1, 1);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        gridLayout->addWidget(statusLabel, 0, 0, 1, 1);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        gridLayout->addWidget(startButton, 0, 1, 1, 1);

        queryEdit = new QLineEdit(centralwidget);
        queryEdit->setObjectName(QString::fromUtf8("queryEdit"));

        gridLayout->addWidget(queryEdit, 3, 0, 1, 1);

        findButton = new QPushButton(centralwidget);
        findButton->setObjectName(QString::fromUtf8("findButton"));

        gridLayout->addWidget(findButton, 3, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 553, 29));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        directoryLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        countLabel->setText(QApplication::translate("MainWindow", "Total: 0", nullptr));
        statusLabel->setText(QApplication::translate("MainWindow", "Empty query", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "select directory", nullptr));
        findButton->setText(QApplication::translate("MainWindow", "find", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
