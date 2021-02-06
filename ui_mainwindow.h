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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *inputPathLineEdit;
    QPushButton *inputBrowseButton;
    QSpinBox *halfstepsEnter;
    QLabel *halfstepsLabel;
    QPushButton *processButton;
    QPushButton *outputBrowseButton;
    QLineEdit *outputPathLineEdit;
    QLabel *inputLabel;
    QLabel *outputLabel;
    QPushButton *inputPlayButton;
    QPushButton *outputPlayButton;
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
        halfstepsEnter = new QSpinBox(centralwidget);
        halfstepsEnter->setObjectName(QString::fromUtf8("halfstepsEnter"));
        halfstepsEnter->setGeometry(QRect(140, 110, 42, 22));
        halfstepsEnter->setMinimum(-99);
        halfstepsLabel = new QLabel(centralwidget);
        halfstepsLabel->setObjectName(QString::fromUtf8("halfstepsLabel"));
        halfstepsLabel->setGeometry(QRect(10, 110, 121, 16));
        processButton = new QPushButton(centralwidget);
        processButton->setObjectName(QString::fromUtf8("processButton"));
        processButton->setGeometry(QRect(10, 140, 661, 21));
        outputBrowseButton = new QPushButton(centralwidget);
        outputBrowseButton->setObjectName(QString::fromUtf8("outputBrowseButton"));
        outputBrowseButton->setGeometry(QRect(560, 80, 121, 21));
        outputPathLineEdit = new QLineEdit(centralwidget);
        outputPathLineEdit->setObjectName(QString::fromUtf8("outputPathLineEdit"));
        outputPathLineEdit->setGeometry(QRect(10, 80, 541, 21));
        inputLabel = new QLabel(centralwidget);
        inputLabel->setObjectName(QString::fromUtf8("inputLabel"));
        inputLabel->setGeometry(QRect(10, 10, 91, 16));
        outputLabel = new QLabel(centralwidget);
        outputLabel->setObjectName(QString::fromUtf8("outputLabel"));
        outputLabel->setGeometry(QRect(10, 60, 91, 16));
        inputPlayButton = new QPushButton(centralwidget);
        inputPlayButton->setObjectName(QString::fromUtf8("inputPlayButton"));
        inputPlayButton->setGeometry(QRect(10, 180, 311, 25));
        outputPlayButton = new QPushButton(centralwidget);
        outputPlayButton->setObjectName(QString::fromUtf8("outputPlayButton"));
        outputPlayButton->setGeometry(QRect(360, 180, 311, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 692, 25));
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
        halfstepsLabel->setText(QCoreApplication::translate("MainWindow", "Enter numer of halfsteps", nullptr));
        processButton->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        outputBrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
        inputLabel->setText(QCoreApplication::translate("MainWindow", "Input file path:", nullptr));
        outputLabel->setText(QCoreApplication::translate("MainWindow", "Output file path:", nullptr));
        inputPlayButton->setText(QCoreApplication::translate("MainWindow", "Play input sound", nullptr));
        outputPlayButton->setText(QCoreApplication::translate("MainWindow", "Play output sound", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
