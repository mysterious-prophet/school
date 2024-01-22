#ifndef CERV_H
#define CERV_H
#include <QPoint>
#include <QString>
#include <QVector>
#include <QColor>
#include <QPen>
#include <QTimer>

class Cerv
{
private:
    int smer; // smer pohybu cerva 0:nahoru, 1:doprava, 2:dolu, 3:doleva
    QPoint pos; //pozice cerva na hraci plose vzhledem k pravemu hornimu okraji
    QColor b; //barva cerva
    int tl; //tloustka cerva
    //QVector<qreal> st;
    int nasRych; //nasobic rychlosti cerva

    bool kresli; //ma cerv viditelnou caru?
    bool pruchozi; //muze cerv prochazet pres cary a pres okraje?


public:
    Cerv();
    Cerv(int x, int y);
    QTimer *timerBonusyDoba;
    Cerv(int x, int y, QColor barva, int tloustka);
    QPoint getPozice();
    QColor getBarva();
    void setBarva(QColor bar);
    void setPozice(QPoint pozice);
    void setSmer(int s);
    int getSmer();
    void setX(int x);
    void setY(int y);
    int getTloustka();
    void setTloustka(int t);
    //QVector<qreal> getStyl();
    //void setStyl(QVector<qreal> s);
    int getNasRych();
    void setNasRych(int nR);
    bool getKresli();
    void setKresli(bool kr);
    bool getPruchozi();
    void setPruchozi(bool pr);
};

#endif // CERV_H
