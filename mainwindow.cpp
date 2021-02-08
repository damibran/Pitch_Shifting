#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <math.h>

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

void MainWindow::on_outputBrowseButton_clicked()
{
    QString fileName;
    if(!ui->inputPathLineEdit->text().isEmpty())
        fileName = QFileDialog::getSaveFileName(this, tr("Open Wav"), ui->inputPathLineEdit->text(), tr("*.wav"));
    else
        fileName = QFileDialog::getSaveFileName(this, tr("Open Wav"), "/", tr("*.wav"));
    ui->outputPathLineEdit->setText(fileName);
}

void MainWindow::on_processButton_clicked()
{
    if(!ui->inputPathLineEdit->text().isEmpty() &&
       !ui->outputPathLineEdit->text().isEmpty() &&
        ui->halfstepsEnter->value()!= 0)
    {
        shifter.make_shift(ui->outputPathLineEdit->text().toStdString(),
                           pow(2.0,((float)ui->halfstepsEnter->value())/12.0));
    }
    else
        qDebug()<<"Error in fields data";
}

void MainWindow::on_inputPlayButton_clicked()
{
    QSound::play(ui->inputPathLineEdit->text());
}

void MainWindow::on_outputPlayButton_clicked()
{
    QSound::play(ui->outputPathLineEdit->text());
}
