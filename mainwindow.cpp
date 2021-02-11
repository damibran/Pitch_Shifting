#include <QDebug>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <math.h>

#include <QKeyEvent>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->octaveLabel->setText(QString::number(octave));
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
    QString inputFile= ui->inputPathLineEdit->text();
    if(!inputFile.isEmpty())
    {
        QString inputFileName = inputFile.right(inputFile.size()-inputFile.lastIndexOf("/")-1);
        QString inputFileDir = inputFile.mid(0,inputFile.lastIndexOf("/")+1);
        outputFileDir = inputFileDir+inputFileName+"_Notes/";
        QDir(inputFileDir).mkdir(inputFileName+"_Notes");
        std::string temp=outputFileDir.toStdString();

        outputFileNames = shifter.create_pianoRoll_notes(temp);

        qDebug()<<"Generated";
    }
    else
        qDebug()<<"Error in fields data";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->text()=="q"||event->text()=="w")
    {
        if(event->text()=="q"&&octave>0)
            octave-=1;
        else if(event->text()=="w"&&octave<4)
            octave+=1;
        ui->octaveLabel->setText(QString::number(octave));
    }
    else{
        std::string note_file_name = outputFileNames[keys[event->text().toStdString()]+12*octave];
        qDebug()<<QString::fromStdString(note_file_name);
        QSound::play(QString::fromStdString(outputFileDir.toStdString()+note_file_name));
    }
}

