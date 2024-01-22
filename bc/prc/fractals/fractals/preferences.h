#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include "fractals.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = 0);
    ~Preferences();
    void setX1(double x);
    double getX1() const;
    void setX2(double x);
    double getX2() const;
    void setY1(double y);
    double getY1() const;
    void setY2(double y);
    double getY2() const;
    void setIterations(unsigned int i);
    unsigned int getIterations() const;
    FractalType getType() const;
    void setType(FractalType t);
    double getCRe() const;
    void setCRe(double d);
    double getCIm() const;
    void setCIm(double d);
    unsigned int getExponent() const;
    void setExponent(unsigned int e);
    bool getChBColors() const;
    void setChBColors(bool value);

private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
