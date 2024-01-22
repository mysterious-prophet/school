#include "oautorovi.h"
#include "ui_oautorovi.h"

oAutorovi::oAutorovi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oAutorovi)
{
    ui->setupUi(this);
    ui->oAutoroviTe->setReadOnly(true);
}

oAutorovi::~oAutorovi()
{
    delete ui;
}
