#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::setX1(double x){
    ui->editX1->setText(QString("%1").arg(x));
}

double Preferences::getX1() const{
    return ui->editX1->text().toDouble();
}

void Preferences::setX2(double x){
    ui->editX2->setText(QString("%1").arg(x));
}

double Preferences::getX2() const{
    return ui->editX2->text().toDouble();
}

void Preferences::setY1(double y){
    ui->editY1->setText(QString("%1").arg(y));
}

double Preferences::getY1() const{
    return ui->editY1->text().toDouble();
}


void Preferences::setY2(double y){
    ui->editY2->setText(QString("%1").arg(y));
}

double Preferences::getY2() const{
    return ui->editY2->text().toDouble();
}

void Preferences::setIterations(unsigned int i){
    ui->editIterations->setText(QString("%1").arg(i));
}

unsigned int Preferences::getIterations() const{
    return ui->editIterations->text().toUInt();
}

double Preferences::getCRe() const{
    return ui->editCRe->text().toDouble();
}

void Preferences::setCRe(double d){
    ui->editCRe->setText(QString("%1").arg(d));
}

double Preferences::getCIm() const{
    return ui->editCIm->text().toDouble();
}

void Preferences::setCIm(double d){
    ui->editCIm->setText(QString("%1").arg(d));
}

FractalType Preferences::getType() const{
    return (ui->rbMandelbrot->isChecked() ? MANDELBROT : JULIA);
}

void Preferences::setType(FractalType t){
    QRadioButton *rb = (t == MANDELBROT ? ui->rbMandelbrot : ui->rbJulia);
    rb->setChecked(true);
}

void Preferences::setExponent(unsigned int e){
    ui->sbExponent->setValue(e);
}

unsigned int Preferences::getExponent() const{
    return ui->sbExponent->value();
}

void Preferences::setChBColors(bool value)
{
    ui->ChbColors->setChecked(value);
}

bool Preferences::getChBColors() const{
    return ui->ChbColors->isChecked();
}
