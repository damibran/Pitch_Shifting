#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <shifter.h>

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

    void on_outputBrowseButton_clicked();

    void on_processButton_clicked();

    void on_inputPathLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    Shifter shifter;

};
#endif // MAINWINDOW_H
