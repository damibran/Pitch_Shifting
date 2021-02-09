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
    if(event->text()=="q"||event->text()=="w")
    {
        if(event->text()=="q"&&shifter.octave>0)
            shifter.octave-=1;
        else if(event->text()=="w"&&shifter.octave<4)
            shifter.octave+=1;
        ui->octaveLabel->setText(QString::number(shifter.octave));
    }
    else{
        qDebug()<<shifter.keys.at(event->text().toStdString())+12*shifter.octave;
    }
}

