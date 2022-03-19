#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(switchLEDs()));

    imageArray[0] = ui->ledOneImage;
    imageArray[1] = ui->ledTwoImage;
    imageArray[2] = ui->ledThreeImage;
    imageArray[3] = ui->ledFourImage;

    checkBoxArray[0] = ui->ledOneCheckBox;
    checkBoxArray[1] = ui->ledTwoCheckBox;
    checkBoxArray[2] = ui->ledThreeCheckBox;
    checkBoxArray[3] = ui->ledFourCheckBox;

    for (int i = 0; i < 4; i++) {
        imageArray[i]->hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::turnOnGroupOne()
{
    imageArray[0]->show();
    checkBoxArray[0]->setChecked(true);
    imageArray[1]->show();
    checkBoxArray[1]->setChecked(true);
}

void MainWindow::turnOffGroupOne()
{
    imageArray[0]->hide();
    checkBoxArray[0]->setChecked(false);
    imageArray[1]->hide();
    checkBoxArray[1]->setChecked(false);
}

void MainWindow::turnOnGroupTwo()
{
    imageArray[2]->show();
    checkBoxArray[2]->setChecked(true);
    imageArray[3]->show();
    checkBoxArray[3]->setChecked(true);
}

void MainWindow::turnOffGroupTwo()
{
    imageArray[2]->hide();
    checkBoxArray[2]->setChecked(false);
    imageArray[3]->hide();
    checkBoxArray[3]->setChecked(false);
}

void MainWindow::switchLEDs() {
    bool isGroupOneOn = checkBoxArray[0]->isChecked() && checkBoxArray[1]->isChecked();
    bool isGroupTwoOn = checkBoxArray[2]->isChecked() && checkBoxArray[3]->isChecked();

    if (isGroupTwoOn) {
       turnOffGroupTwo();
       turnOnGroupOne();
    } else if (isGroupOneOn) {
        turnOffGroupOne();
        turnOnGroupTwo();
    }

    counter--;
    if (counter == 0) {
        timer->stop();
        turnOffGroupOne();
    }
}

void MainWindow::on_switchLedButton_clicked()
{
    counter = ui->timeInput->text().toInt() * 2;
    turnOffGroupTwo();
    turnOnGroupOne();
    timer->start(1000);
}

void MainWindow::on_shineLedButton_clicked()
{
    for (int i = 0; i < 4; i++) {
        if (checkBoxArray[i]->isChecked()) {
            imageArray[i]->show();
        } else {
            imageArray[i]->hide();
        }
    }
}
