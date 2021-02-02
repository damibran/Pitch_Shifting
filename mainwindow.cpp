#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846 /* pi */

void scale_spector(float factor, fftw_complex *inputSpectr, fftw_complex *outputSpectr);
void make_window(std::vector<double> buffer);


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->processButton->setEnabled(false);

    tempBuffer.resize(N);
    inputSpectr = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N / 2 + 1);
    outputSpectr = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N / 2 + 1);
    forward = fftw_plan_dft_r2c_1d(N, tempBuffer.data(), inputSpectr, FFTW_ESTIMATE);
    backward = fftw_plan_dft_c2r_1d(N, outputSpectr, tempBuffer.data(), FFTW_ESTIMATE);


}

MainWindow::~MainWindow()
{
    if(forward)fftw_destroy_plan(forward);
    if(backward)fftw_destroy_plan(backward);
    //fftw_free(outputSpectr);
    //fftw_free(inputSpectr);
    delete ui;
}

void MainWindow::make_window(std::vector<double> buffer)
{
    for (int k = 0; k < N; ++k)
    {
        buffer[k] = (0.54 - 0.46 * cos((2 * M_PI * k) / N)) * buffer[k];
        //buffer[k] = (0.355768 - 0.487396 * cos((2 * M_PI * k) / N) + 0.144232 * cos((4 * M_PI * k) / N) - 0.012604 * cos((6 * M_PI * k) / N))* buffer[k];
    }
}

void MainWindow::scale_spector(float factor, fftw_complex *inputSpectr, fftw_complex *outputSpectr)
{

    for (int i = 0; i < N / 2 + 1; ++i)
    {
        outputSpectr[i][0] = 0;
        outputSpectr[i][1] = 0;
    }

    for (int i = 0; i < N / 2 + 1; ++i)
    {
        if (i * factor > 0 && i * factor < N / 2 + 1)
        {
            outputSpectr[(int)(i * factor)][0] = inputSpectr[i][0];
            outputSpectr[(int)(i * factor)][1] = inputSpectr[i][1];
            //std::cout << (int)(i * factor) << " : " << i<<"\n";
        }
    }
}

void MainWindow::on_inputBrowseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Wav"), "/", tr("*.wav"));
    ui->inputPathLineEdit->setText(fileName);
}

void MainWindow::on_halfstepsEnter_editingFinished()
{
    int value = ui->halfstepsEnter->value();
    if(ui->inputPathLineEdit->text()!=nullptr && ui->outputPathLineEdit->text()!=nullptr && value!= 0)
    {
        ui->processButton->setEnabled(true);
        factor = pow(2.0,((float)value)/12.0);
    }
}

void MainWindow::on_outputBrowseButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Wav"), "/", tr("*.wav"));
    ui->outputPathLineEdit->setText(fileName);
}

void MainWindow::on_processButton_clicked()
{
    AudioFile<double> outputAudio;
    AudioFile<double>::AudioBuffer outputBuffer;

    inputAudio.load(ui->inputPathLineEdit->text().toStdString());
    std::cout<<"\nBuff size"<<inputAudio.samples[0].size()<<"\n";
    int numChannel = inputAudio.getNumChannels();
    int numSamples = inputAudio.getNumSamplesPerChannel();

    inputAudio.printSummary();

    outputAudio.setBitDepth(inputAudio.getBitDepth());
    outputAudio.setSampleRate(inputAudio.getSampleRate());

    outputBuffer.resize(numChannel);
    for (int i = 0; i < numChannel; ++i)
        outputBuffer[i].resize(numSamples);


    int processed_samples;
    for (int i = 0; i < numChannel; ++i)
    {
        processed_samples = 0;
        while (numSamples - processed_samples >= N)
        {
            std::copy(inputAudio.samples[i].begin() + processed_samples,
                      inputAudio.samples[i].begin() + processed_samples + N,
                      tempBuffer.begin());

            make_window(tempBuffer);
            fftw_execute(forward);

            scale_spector(factor, inputSpectr, outputSpectr);

            fftw_execute(backward);
            for (int j = 0; j < (int)tempBuffer.size(); ++j)
                tempBuffer[j] = tempBuffer[j] / N;
            outputBuffer[i].insert(outputBuffer[i].begin() + processed_samples,
                                   tempBuffer.begin(),
                                   tempBuffer.end());
            processed_samples += N;
        }
        if (numSamples != processed_samples)
        {
            std::copy(inputAudio.samples[i].begin() + processed_samples,
                      inputAudio.samples[i].end(),
                      tempBuffer.begin());
            while ((int)tempBuffer.size() != N)
                tempBuffer.push_back(0);

            make_window(tempBuffer);
            fftw_execute(forward);

            scale_spector(factor, inputSpectr, outputSpectr);

            fftw_execute(backward);
            for (int j = 0; j < (int)tempBuffer.size(); ++j)
                tempBuffer[j] = tempBuffer[j] / N;
            outputBuffer[i].insert(outputBuffer[i].begin() + processed_samples,
                                   tempBuffer.begin(),
                                   tempBuffer.end());
        }
    }

    if (outputAudio.setAudioBuffer(outputBuffer))
    {
        outputAudio.save(ui->outputPathLineEdit->text().toStdString());
        std::cout << "OK";
    }

}
