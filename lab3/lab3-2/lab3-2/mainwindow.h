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
    void on_shineLedButton_clicked();
    void switchLEDs();
    void on_switchingOnButton_clicked();
    void on_switchingOffButon_clicked();
    void on_periodSlider_valueChanged(int value);
    void increasePeriod();
    void decreasePeriod();

private:
    Ui::MainWindow *ui;
    QLabel *imageArray[4];
    QCheckBox *checkBoxArray[4];
    QTimer *timer;
    int leds[4];
    const int MAX_PERIOD;

    void turnOnLED(unsigned int);
    void turnOffLED(unsigned int);
    void turnOnGroupOne();
    void turnOffGroupOne();
    void turnOnGroupTwo();
    void turnOffGroupTwo();
};

#endif // MAINWINDOW_H
