#include "napovedahra.h"
#include "ui_napovedahra.h"

napovedaHra::napovedaHra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::napovedaHra)
{
    ui->setupUi(this);
    ui->zaklInfoTe->setReadOnly(true);
}

napovedaHra::~napovedaHra()
{
    delete ui;
}
