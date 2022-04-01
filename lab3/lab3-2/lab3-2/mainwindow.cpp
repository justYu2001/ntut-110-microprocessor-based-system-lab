#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QShortcut>
#include "gpio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    MAX_PERIOD(5000)
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

    leds[0] = 396;
    leds[1] = 392;
    leds[2] = 481;
    leds[3] = 398;

    for (int i = 0; i < 4; i++) {
        imageArray[i]->hide();
    }

    ui->periodBar->setValue(50);

    QShortcut *keyJ = new QShortcut(QKeySequence(Qt::Key_J), this);
    QObject::connect(keyJ, &QShortcut::activated, this, &MainWindow::decreasePeriod);

    QShortcut *keyK = new QShortcut(QKeySequence(Qt::Key_K), this);
    QObject::connect(keyK, &QShortcut::activated, this, &MainWindow::increasePeriod);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::increasePeriod() {
    ui->periodSpinBox->stepUp();
}

void MainWindow::decreasePeriod() {
    ui->periodSpinBox->stepDown();
}

void MainWindow::turnOnLED(unsigned int gpio) {
    setExport(gpio);
    setDirection(gpio, "out");
    setValue(gpio, 1);
    setUnexport(gpio);
}

void MainWindow::turnOffLED(unsigned int gpio) {
    setUnexport(gpio);
    setExport(gpio);
    setDirection(gpio, "out");
    setValue(gpio, 0);
    setUnexport(gpio);
}

void MainWindow::turnOnGroupOne()
{
    imageArray[0]->show();
    checkBoxArray[0]->setChecked(true);
    imageArray[1]->show();
    checkBoxArray[1]->setChecked(true);

    turnOnLED(leds[0]);
    turnOnLED(leds[1]);
}

void MainWindow::turnOffGroupOne()
{
    imageArray[0]->hide();
    checkBoxArray[0]->setChecked(false);
    imageArray[1]->hide();
    checkBoxArray[1]->setChecked(false);

    turnOffLED(leds[0]);
    turnOffLED(leds[1]);
}

void MainWindow::turnOnGroupTwo()
{
    imageArray[2]->show();
    checkBoxArray[2]->setChecked(true);
    imageArray[3]->show();
    checkBoxArray[3]->setChecked(true);

    turnOnLED(leds[2]);
    turnOnLED(leds[3]);
}

void MainWindow::turnOffGroupTwo()
{
    imageArray[2]->hide();
    checkBoxArray[2]->setChecked(false);
    imageArray[3]->hide();
    checkBoxArray[3]->setChecked(false);

    turnOffLED(leds[2]);
    turnOffLED(leds[3]);
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
}

void MainWindow::on_shineLedButton_clicked()
{
    for (int i = 0; i < 4; i++) {
        if (checkBoxArray[i]->isChecked()) {
            imageArray[i]->show();
            turnOnLED(leds[i]);
        } else {
            imageArray[i]->hide();
            turnOffLED(leds[i]);
        }
    }
}

void MainWindow::on_switchingOnButton_clicked()
{
    double periodPercentage = ui->periodSlider->value() * 0.01;
    int period = MAX_PERIOD * periodPercentage;

    turnOffGroupTwo();
    turnOnGroupOne();
    timer->start(period);
}

void MainWindow::on_switchingOffButon_clicked()
{
    timer->stop();
    turnOffGroupOne();
    turnOffGroupTwo();
}

void MainWindow::on_periodSlider_valueChanged(int value)
{
    double periodPercentage = value * 0.01;
    int period = MAX_PERIOD * periodPercentage;
    timer->setInterval(period);
}
