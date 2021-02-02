#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fftw3.h"
#include "AudioFile.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputBrowseButton_clicked();

    void on_halfstepsEnter_editingFinished();

    void on_outputBrowseButton_clicked();

    void on_processButton_clicked();

private:
    const int N = 4096;
    Ui::MainWindow *ui;
    AudioFile<double> inputAudio;
    float factor;
    std::vector<double> tempBuffer;
    fftw_complex *inputSpectr;
    fftw_complex *outputSpectr;
    fftw_plan forward;
    fftw_plan backward;
    void make_window(std::vector<double> buffer);
    void scale_spector(float factor, fftw_complex *inputSpectr, fftw_complex *outputSpectr);
};
#endif // MAINWINDOW_H
