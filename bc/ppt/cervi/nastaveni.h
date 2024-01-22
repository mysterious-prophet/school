#pragma once
#ifndef NASTAVENI_H
#define NASTAVENI_H

#include <QDialog>
#include <QColorDialog>
#include "mainwindow.h"

namespace Ui {
class Nastaveni;
}

class Nastaveni : public QDialog
{
    Q_OBJECT

public:
    explicit Nastaveni(QWidget *parent = nullptr);
    ~Nastaveni();
    void setVitezne(int body); //nastav hru
    void setTloustka(int tl);
    void setRychlost(int rych);
    void setMezery(bool mez);
    void setMezeryCet(int mez);
    void setBonusy(bool bon);
    void setBonusyCet(int bon);
    void setBonusyDoba(int bonDob);
    void setBarvaC1(QColor barva);
    void setBarvaC2(QColor barva);


    int vitezneNast; //co je mozne nastavit
    int tloustkaNast;
    QColor barvaC1;
    QColor barvaC2;
    bool mezeryNast;
    int mezeryNastCet;
    bool bonusyNast;
    int bonusyNastCet;
    int bonusyDoba;
    int rychlostNast;
    bool prijato = false;

private slots:
    void on_MezCb_stateChanged(int arg1); //je li zmenena pritomnost mezer a bonusu ve hre

    void on_BonCb_stateChanged(int arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_c1BarvaPb_clicked();

    void on_c2BarvaPb_clicked();

private:
    Ui::Nastaveni *ui;
};

#endif // NASTAVENI_H
