#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <shifter.h>
#include <QSound>

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

    void on_processButton_clicked();

    void on_inputPathLineEdit_editingFinished();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    Shifter shifter;

};
#endif // MAINWINDOW_H
