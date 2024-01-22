#ifndef OAUTOROVI_H
#define OAUTOROVI_H

#include <QDialog>

namespace Ui {
class oAutorovi;
}

class oAutorovi : public QDialog
{
    Q_OBJECT

public:
    explicit oAutorovi(QWidget *parent = nullptr);
    ~oAutorovi();

private:
    Ui::oAutorovi *ui;
};

#endif // OAUTOROVI_H
