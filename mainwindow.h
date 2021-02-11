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
    int octave=2;
    std::map<std::string,int> keys {{ "z" , 0 },
                                    { "s" , 1 },
                                    { "x" , 2 },
                                    { "d" , 3 },
                                    { "c" , 4 },
                                    { "v" , 5 },
                                    { "g" , 6 },
                                    { "b" , 7 },
                                    { "h" , 8 },
                                    { "n" , 9 },
                                    { "j" , 10 },
                                    { "m" , 11 }
                                   };
    Ui::MainWindow *ui;
    Shifter shifter;
    QString outputFileDir;
    std::vector<std::string> outputFileNames;

};
#endif // MAINWINDOW_H
