/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QLineEdit *inputPathLineEdit;
    QPushButton *inputBrowseButton;
    QPushButton *processButton;
    QLabel *inputLabel;
    QLabel *octaveLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(692, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        inputPathLineEdit = new QLineEdit(centralwidget);
        inputPathLineEdit->setObjectName(QString::fromUtf8("inputPathLineEdit"));
        inputPathLineEdit->setGeometry(QRect(10, 30, 541, 21));
        inputBrowseButton = new QPushButton(centralwidget);
        inputBrowseButton->setObjectName(QString::fromUtf8("inputBrowseButton"));
        inputBrowseButton->setGeometry(QRect(560, 30, 121, 21));
        processButton = new QPushButton(centralwidget);
        processButton->setObjectName(QString::fromUtf8("processButton"));
        processButton->setGeometry(QRect(10, 90, 661, 21));
        inputLabel = new QLabel(centralwidget);
        inputLabel->setObjectName(QString::fromUtf8("inputLabel"));
        inputLabel->setGeometry(QRect(10, 10, 91, 16));
        octaveLabel = new QLabel(centralwidget);
        octaveLabel->setObjectName(QString::fromUtf8("octaveLabel"));
        octaveLabel->setGeometry(QRect(20, 60, 47, 13));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 692, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        inputBrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
        processButton->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        inputLabel->setText(QCoreApplication::translate("MainWindow", "Input file path:", nullptr));
        octaveLabel->setText(QCoreApplication::translate("MainWindow", "Octave", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
