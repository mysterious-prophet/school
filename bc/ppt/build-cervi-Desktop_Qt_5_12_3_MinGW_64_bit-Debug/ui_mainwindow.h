/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNova_hra;
    QAction *actionKonec;
    QAction *actionNastaveni_Hry;
    QAction *actionHra;
    QAction *actionO_autorovi;
    QWidget *centralWidget;
    QPushButton *novaHraBt;
    QLineEdit *hrac1Le;
    QLineEdit *hrac2Le;
    QLabel *hrac1Lb;
    QLabel *hrac2Lb;
    QMenuBar *menuBar;
    QMenu *menuHra;
    QMenu *menuNastaveni;
    QMenu *menuInformace;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 750);
        MainWindow->setMinimumSize(QSize(650, 500));
        MainWindow->setMaximumSize(QSize(750, 750));
        actionNova_hra = new QAction(MainWindow);
        actionNova_hra->setObjectName(QString::fromUtf8("actionNova_hra"));
        actionKonec = new QAction(MainWindow);
        actionKonec->setObjectName(QString::fromUtf8("actionKonec"));
        actionNastaveni_Hry = new QAction(MainWindow);
        actionNastaveni_Hry->setObjectName(QString::fromUtf8("actionNastaveni_Hry"));
        actionHra = new QAction(MainWindow);
        actionHra->setObjectName(QString::fromUtf8("actionHra"));
        actionO_autorovi = new QAction(MainWindow);
        actionO_autorovi->setObjectName(QString::fromUtf8("actionO_autorovi"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        novaHraBt = new QPushButton(centralWidget);
        novaHraBt->setObjectName(QString::fromUtf8("novaHraBt"));
        novaHraBt->setGeometry(QRect(275, 250, 100, 30));
        hrac1Le = new QLineEdit(centralWidget);
        hrac1Le->setObjectName(QString::fromUtf8("hrac1Le"));
        hrac1Le->setGeometry(QRect(100, 150, 150, 30));
        hrac2Le = new QLineEdit(centralWidget);
        hrac2Le->setObjectName(QString::fromUtf8("hrac2Le"));
        hrac2Le->setGeometry(QRect(400, 150, 150, 30));
        hrac1Lb = new QLabel(centralWidget);
        hrac1Lb->setObjectName(QString::fromUtf8("hrac1Lb"));
        hrac1Lb->setGeometry(QRect(100, 125, 150, 20));
        hrac2Lb = new QLabel(centralWidget);
        hrac2Lb->setObjectName(QString::fromUtf8("hrac2Lb"));
        hrac2Lb->setGeometry(QRect(400, 125, 150, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 26));
        menuHra = new QMenu(menuBar);
        menuHra->setObjectName(QString::fromUtf8("menuHra"));
        menuNastaveni = new QMenu(menuBar);
        menuNastaveni->setObjectName(QString::fromUtf8("menuNastaveni"));
        menuInformace = new QMenu(menuBar);
        menuInformace->setObjectName(QString::fromUtf8("menuInformace"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuHra->menuAction());
        menuBar->addAction(menuNastaveni->menuAction());
        menuBar->addAction(menuInformace->menuAction());
        menuHra->addAction(actionNova_hra);
        menuHra->addSeparator();
        menuHra->addAction(actionKonec);
        menuNastaveni->addAction(actionNastaveni_Hry);
        menuInformace->addAction(actionHra);
        menuInformace->addSeparator();
        menuInformace->addAction(actionO_autorovi);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Achtung! Die Linie", nullptr));
        actionNova_hra->setText(QApplication::translate("MainWindow", "Nov\303\241 hra", nullptr));
        actionKonec->setText(QApplication::translate("MainWindow", "Konec", nullptr));
        actionNastaveni_Hry->setText(QApplication::translate("MainWindow", "Nastaven\303\255 hry", nullptr));
        actionHra->setText(QApplication::translate("MainWindow", "Hra", nullptr));
        actionO_autorovi->setText(QApplication::translate("MainWindow", "O autorovi", nullptr));
        novaHraBt->setText(QApplication::translate("MainWindow", "Hr\303\241t", nullptr));
        hrac1Le->setText(QApplication::translate("MainWindow", "Hr\303\241\304\2151", nullptr));
        hrac2Le->setText(QApplication::translate("MainWindow", "Hr\303\241\304\2152", nullptr));
        hrac1Lb->setText(QApplication::translate("MainWindow", "Zadejte jm\303\251no Hr\303\241\304\215e 1:", nullptr));
        hrac2Lb->setText(QApplication::translate("MainWindow", "Zadejte jm\303\251no Hr\303\241\304\215e 2: ", nullptr));
        menuHra->setTitle(QApplication::translate("MainWindow", "Hra", nullptr));
        menuNastaveni->setTitle(QApplication::translate("MainWindow", "Nastaven\303\255", nullptr));
        menuInformace->setTitle(QApplication::translate("MainWindow", "N\303\241pov\304\233da", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
