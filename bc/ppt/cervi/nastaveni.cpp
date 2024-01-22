#include "nastaveni.h"
#include "ui_nastaveni.h"
#include "mainwindow.h"
#include "cerv.h"


Nastaveni::Nastaveni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nastaveni)
{
    ui->setupUi(this);
    //nastav rozmezi hodnot
    ui->BdSp->setRange(1,100);
    ui->TlSp->setRange(1,10);
    ui->RySp->setRange(1,100);
    ui->MezSp->setRange(10,100);
    ui->BnSp->setRange(5,60);
    ui->DoBonSp->setRange(1,10);

    //ui->MezCb->setChecked(true);
    //ui->BonCb->setChecked(true);
}


Nastaveni::~Nastaveni()
{

    delete ui;
}

void Nastaveni::setVitezne(int body)
{
    ui->BdSp->setValue(body);
}

void Nastaveni::setRychlost(int rych)
{
    ui->RySp->setValue(rych);
}

void Nastaveni::setTloustka(int tl)
{
    ui->TlSp->setValue(tl);
}

void Nastaveni::setMezery(bool mez)
{
    if(mez)
        ui->MezCb->setChecked(true);
    else{
        ui->MezCb->setChecked(false);
    }
}
void Nastaveni::setMezeryCet(int mez)
{
    ui->MezSp->setValue(mez);
}

void Nastaveni::setBonusy(bool bon)

{
    if(bon)
        ui->BonCb->setChecked(true);
    else {
        ui->BonCb->setChecked(false);
    }
}
void Nastaveni::setBonusyCet(int bon)
{
    ui->BnSp->setValue(bon);
}

void Nastaveni::setBonusyDoba(int bonDob)
{
    ui->DoBonSp->setValue(bonDob);
}

void Nastaveni::on_MezCb_stateChanged(int arg1)
{
    if(!ui->MezCb->isChecked()){ //je li zmenen stav mezer
        ui->MezSp->setVisible(false);
    }
    else if(ui->MezCb->isChecked()){
        ui->MezSp->setVisible(true);
        setMezeryCet(30);
    }
}

void Nastaveni::on_BonCb_stateChanged(int arg1)
{
    if(!ui->BonCb->isChecked()){
        ui->BnSp->setVisible(false);
        ui->DoBonSp->setVisible(false);
    }
    else if(ui->BonCb->isChecked()){
        ui->BnSp->setVisible(true);
        setBonusyCet(15);
        ui->DoBonSp->setVisible(true);
        setBonusyDoba(8);
    }
}

void Nastaveni::on_buttonBox_accepted()
{

    vitezneNast = ui->BdSp->value();
    tloustkaNast = ui->TlSp->value();
    rychlostNast = ui->RySp->value();

    if(ui->MezCb->isChecked())
        mezeryNast = true;
    else {
        mezeryNast = false;
    }
    if(ui->BonCb->isChecked())
        bonusyNast = true;
    else {
        bonusyNast = false;
    }

    if(mezeryNast)
        mezeryNastCet = ui->MezSp->value();
    if(bonusyNast)
        bonusyNastCet = ui->BnSp->value();
        bonusyDoba = ui->DoBonSp->value();

    prijato = true;
}

void Nastaveni::on_buttonBox_rejected()
{

    prijato = false;

    Nastaveni::close();
}

void Nastaveni::setBarvaC1(QColor barva)
{
    QPixmap ikBarva(40,40); //nahraj barvu cervu ze hry
    barvaC1 = barva;
    ikBarva.fill(barvaC1);
    QIcon ikona(ikBarva);
    ui->c1BarvaPb->setIcon(ikona);
}

void Nastaveni::setBarvaC2(QColor barva)
{
    QPixmap ikBarva(40,40);
    barvaC2 = barva;
    ikBarva.fill(barvaC2);
    QIcon ikona(ikBarva);
    ui->c2BarvaPb->setIcon(ikona);

}

void Nastaveni::on_c1BarvaPb_clicked()
{
    QColorDialog dialogC1; //nastav barvu cervum
    dialogC1.open();
    dialogC1.setWindowTitle("Barva Hráč1");
    barvaC1 = dialogC1.getColor();
    if(barvaC1 == Qt::white)
        barvaC1 = Qt::gray;
    QPixmap ikBarvaC1(40,40);
    ikBarvaC1.fill(barvaC1);
    QIcon ikonaC1(ikBarvaC1);
    ui->c1BarvaPb->setIcon(ikonaC1);

}

void Nastaveni::on_c2BarvaPb_clicked()
{
    QColorDialog dialogC2;
    dialogC2.setWindowTitle("Barva Hráč2");
    dialogC2.open();
    barvaC2 = dialogC2.getColor();
    if(barvaC2 == Qt::white)
        barvaC2 = Qt::gray;
    QPixmap ikBarvaC2(40,40);
    ikBarvaC2.fill(barvaC2);
    QIcon ikonaC2(ikBarvaC2);
    ui->c2BarvaPb->setIcon(ikonaC2);
}
