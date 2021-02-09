#include <QDir>
#include <QDebug>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <math.h>

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputBrowseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Wav"), "/", tr("*.wav"));
    ui->inputPathLineEdit->setText(fileName);

    shifter.load_input_file(fileName.toStdString());
}

void MainWindow::on_inputPathLineEdit_editingFinished()
{
    shifter.load_input_file(ui->inputPathLineEdit->text().toStdString());
}

void MainWindow::on_processButton_clicked()
{
    if(!ui->inputPathLineEdit->text().isEmpty())
    {

    }
    else
        qDebug()<<"Error in fields data";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->text();
}

