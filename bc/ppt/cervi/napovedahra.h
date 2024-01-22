#ifndef NAPOVEDAHRA_H
#define NAPOVEDAHRA_H

#include <QDialog>

namespace Ui {
class napovedaHra;
}

class napovedaHra : public QDialog
{
    Q_OBJECT

public:
    explicit napovedaHra(QWidget *parent = nullptr);
    ~napovedaHra();

private:
    Ui::napovedaHra *ui;
};

#endif // NAPOVEDAHRA_H
