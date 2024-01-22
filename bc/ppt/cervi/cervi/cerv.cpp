#include "cerv.h"

Cerv::Cerv()
{
    pos = QPoint(0,0);
    b = "Qt::red";
    smer = 0;
}

Cerv::Cerv(int x, int y)
{
    pos = QPoint(x, y);
    b = "Qt::red";
    smer = 0;
}

Cerv::Cerv(int x, int y, QColor barva, int tloustka)
{
    pos = QPoint(x, y);
    b = barva;
    tl = tloustka;
    smer = 0;
    nasRych = 1;
    kresli = true;
    pruchozi = false;
}

QPoint Cerv::getPozice()
{
    return pos;

}

QColor Cerv::getBarva()
{
    return b;

}

void Cerv::setBarva(QColor bar)
{
    b = bar;
}

void Cerv::setPozice(QPoint pozice)
{
    pos = pozice;

}

void Cerv::setSmer(int s)
{
    smer = s;

}

int Cerv::getSmer()
{
    return smer;
}

void Cerv::setX(int x)
{
    pos.setX(x);
}

void Cerv::setY(int y)
{
    pos.setY(y);
}

int Cerv::getTloustka()
{
    return tl;
}

void Cerv::setTloustka(int t)
{
    tl = t;
}


int Cerv::getNasRych(){
    return nasRych;
}

void Cerv::setNasRych(int nR){
    nasRych = nR;
}

bool Cerv::getKresli()
{
    return kresli;
}

void Cerv::setKresli(bool kr)
{
    kresli = kr;
}

bool Cerv::getPruchozi()
{
    return pruchozi;
}

void Cerv::setPruchozi(bool pr)
{
    pruchozi = pr;
}
