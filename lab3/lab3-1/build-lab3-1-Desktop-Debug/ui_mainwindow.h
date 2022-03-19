/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *ledOneImage;
    QCheckBox *ledOneCheckBox;
    QCheckBox *ledTwoCheckBox;
    QLabel *ledTwoImage;
    QCheckBox *ledThreeCheckBox;
    QLabel *ledThreeImage;
    QCheckBox *ledFourCheckBox;
    QLabel *ledFourImage;
    QLabel *label_5;
    QPushButton *switchLedButton;
    QLineEdit *timeInput;
    QPushButton *shineLedButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(833, 565);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ledOneImage = new QLabel(centralWidget);
        ledOneImage->setObjectName(QStringLiteral("ledOneImage"));
        ledOneImage->setGeometry(QRect(60, 20, 67, 71));
        ledOneImage->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/idea.png")));
        ledOneImage->setScaledContents(true);
        ledOneCheckBox = new QCheckBox(centralWidget);
        ledOneCheckBox->setObjectName(QStringLiteral("ledOneCheckBox"));
        ledOneCheckBox->setGeometry(QRect(140, 40, 92, 23));
        ledTwoCheckBox = new QCheckBox(centralWidget);
        ledTwoCheckBox->setObjectName(QStringLiteral("ledTwoCheckBox"));
        ledTwoCheckBox->setGeometry(QRect(140, 140, 92, 23));
        ledTwoImage = new QLabel(centralWidget);
        ledTwoImage->setObjectName(QStringLiteral("ledTwoImage"));
        ledTwoImage->setGeometry(QRect(60, 110, 67, 71));
        ledTwoImage->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/idea.png")));
        ledTwoImage->setScaledContents(true);
        ledThreeCheckBox = new QCheckBox(centralWidget);
        ledThreeCheckBox->setObjectName(QStringLiteral("ledThreeCheckBox"));
        ledThreeCheckBox->setGeometry(QRect(140, 210, 92, 23));
        ledThreeImage = new QLabel(centralWidget);
        ledThreeImage->setObjectName(QStringLiteral("ledThreeImage"));
        ledThreeImage->setGeometry(QRect(60, 190, 67, 71));
        ledThreeImage->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/idea.png")));
        ledThreeImage->setScaledContents(true);
        ledFourCheckBox = new QCheckBox(centralWidget);
        ledFourCheckBox->setObjectName(QStringLiteral("ledFourCheckBox"));
        ledFourCheckBox->setGeometry(QRect(140, 310, 92, 23));
        ledFourImage = new QLabel(centralWidget);
        ledFourImage->setObjectName(QStringLiteral("ledFourImage"));
        ledFourImage->setGeometry(QRect(60, 280, 67, 71));
        ledFourImage->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/idea.png")));
        ledFourImage->setScaledContents(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(340, 60, 67, 17));
        switchLedButton = new QPushButton(centralWidget);
        switchLedButton->setObjectName(QStringLiteral("switchLedButton"));
        switchLedButton->setGeometry(QRect(340, 160, 141, 25));
        timeInput = new QLineEdit(centralWidget);
        timeInput->setObjectName(QStringLiteral("timeInput"));
        timeInput->setGeometry(QRect(340, 100, 113, 25));
        shineLedButton = new QPushButton(centralWidget);
        shineLedButton->setObjectName(QStringLiteral("shineLedButton"));
        shineLedButton->setGeometry(QRect(70, 400, 121, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        ledOneImage->setText(QString());
        ledOneCheckBox->setText(QApplication::translate("MainWindow", "LED 1", Q_NULLPTR));
        ledTwoCheckBox->setText(QApplication::translate("MainWindow", "LED 2", Q_NULLPTR));
        ledTwoImage->setText(QString());
        ledThreeCheckBox->setText(QApplication::translate("MainWindow", "LED 3", Q_NULLPTR));
        ledThreeImage->setText(QString());
        ledFourCheckBox->setText(QApplication::translate("MainWindow", "LED 4", Q_NULLPTR));
        ledFourImage->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Times", Q_NULLPTR));
        switchLedButton->setText(QApplication::translate("MainWindow", "LED Switching", Q_NULLPTR));
        shineLedButton->setText(QApplication::translate("MainWindow", "LED Shining", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
