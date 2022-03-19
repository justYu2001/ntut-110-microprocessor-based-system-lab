#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCheckBox>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_switchLedButton_clicked();
    void on_shineLedButton_clicked();
    void switchLEDs();

private:
    Ui::MainWindow *ui;
    QLabel *imageArray[4];
    QCheckBox *checkBoxArray[4];
    QTimer *timer;
    int counter;

    void turnOnGroupOne();
    void turnOffGroupOne();
    void turnOnGroupTwo();
    void turnOffGroupTwo();
};

#endif // MAINWINDOW_H
