#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include "cerv.h"
#include <QString>
#include "nastaveni.h"
#include "napovedahra.h"
#include "oautorovi.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void restart();
    int vitezneBody; //body nutne k vitezstvi ve hre
    int rychlost; //rychlost pohybu cervu
    int defTloustka; //tloustka cervu;
    QColor barvaC1; //barvy cervu
    QColor barvaC2;
    bool mezery; //delaji cervy mezery?
    int mezeryCet; //jak casto pokud ano
    bool bonusy; //vyskytuji se na platne bonusy?
    int bonusyCet; //jak casto
    int defDobaTrvaniBon; //na jak dlouho plati dany bonus
    bool srazkaC1; //doslo ke srazce cerva a jineho cerva nebo okraje ve hre?
    bool srazkaC2;

private:
    Ui::MainWindow *ui;
    Cerv c1, c2;
    QImage image; //platno hry
    QTimer *timerPohyb; //casovac pohybu rychlost cervu
    QTimer *timerBonusyCet; //casovac spawnovani bonusu
    QVector<int> body; //body hracu
    QLabel *hrac1Body;
    QLabel *hrac2Body;
    QLabel *bonus; //typ bonusu ikona
    QString hrac1Jmeno; //jmena hracu
    QString hrac2Jmeno;
    bool konecKola = false; //zda doslo k udalosti, ktera by spustila konec kola nebo konec hry
    bool konecHry = false;
    int pocetBonusu = 7; //pocet bonusu ve hre, naprogramovano 7 ruznych bonusu
    int cisloBonusu; //cislo vygenerovaneho bonusu

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void pohyb(int poc);
    int genBonus();
    void hra(int pocet);
    //void restart();

private slots:
    void timerP(); //sloty pro timery, jelikoz timerem nelze zavolat funkci s parametry
    void timerB();
    void timerBDC1();
    void timerBDC2();

    void on_actionKonec_triggered();
    void on_actionNova_hra_triggered();
    void on_actionNastaveni_Hry_triggered();

    void on_novaHraBt_clicked();
    void on_actionHra_triggered();
    void on_actionO_autorovi_triggered();
};

#endif // MAINWINDOW_H
