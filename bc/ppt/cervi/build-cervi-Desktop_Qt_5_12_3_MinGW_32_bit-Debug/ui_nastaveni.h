/********************************************************************************
** Form generated from reading UI file 'nastaveni.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NASTAVENI_H
#define UI_NASTAVENI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Nastaveni
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *Tloustka;
    QLabel *Rychlost;
    QLabel *Barva;
    QLabel *CetMez;
    QLabel *CetBon;
    QSpinBox *TlSp;
    QSpinBox *RySp;
    QCheckBox *MezCb;
    QSpinBox *BnSp;
    QCheckBox *BonCb;
    QSpinBox *MezSp;
    QLabel *Body;
    QSpinBox *BdSp;
    QLabel *DobaTrvaniBon;
    QSpinBox *DoBonSp;
    QPushButton *c1BarvaPb;
    QPushButton *c2BarvaPb;

    void setupUi(QDialog *Nastaveni)
    {
        if (Nastaveni->objectName().isEmpty())
            Nastaveni->setObjectName(QString::fromUtf8("Nastaveni"));
        Nastaveni->resize(431, 367);
        buttonBox = new QDialogButtonBox(Nastaveni);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(70, 320, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Tloustka = new QLabel(Nastaveni);
        Tloustka->setObjectName(QString::fromUtf8("Tloustka"));
        Tloustka->setGeometry(QRect(30, 50, 141, 16));
        Rychlost = new QLabel(Nastaveni);
        Rychlost->setObjectName(QString::fromUtf8("Rychlost"));
        Rychlost->setGeometry(QRect(30, 80, 101, 16));
        Barva = new QLabel(Nastaveni);
        Barva->setObjectName(QString::fromUtf8("Barva"));
        Barva->setGeometry(QRect(30, 120, 121, 16));
        CetMez = new QLabel(Nastaveni);
        CetMez->setObjectName(QString::fromUtf8("CetMez"));
        CetMez->setGeometry(QRect(30, 210, 121, 21));
        CetBon = new QLabel(Nastaveni);
        CetBon->setObjectName(QString::fromUtf8("CetBon"));
        CetBon->setGeometry(QRect(30, 290, 121, 16));
        TlSp = new QSpinBox(Nastaveni);
        TlSp->setObjectName(QString::fromUtf8("TlSp"));
        TlSp->setGeometry(QRect(190, 50, 42, 22));
        RySp = new QSpinBox(Nastaveni);
        RySp->setObjectName(QString::fromUtf8("RySp"));
        RySp->setGeometry(QRect(190, 80, 42, 22));
        MezCb = new QCheckBox(Nastaveni);
        MezCb->setObjectName(QString::fromUtf8("MezCb"));
        MezCb->setGeometry(QRect(30, 180, 81, 20));
        BnSp = new QSpinBox(Nastaveni);
        BnSp->setObjectName(QString::fromUtf8("BnSp"));
        BnSp->setGeometry(QRect(150, 290, 42, 22));
        BonCb = new QCheckBox(Nastaveni);
        BonCb->setObjectName(QString::fromUtf8("BonCb"));
        BonCb->setGeometry(QRect(30, 260, 81, 20));
        MezSp = new QSpinBox(Nastaveni);
        MezSp->setObjectName(QString::fromUtf8("MezSp"));
        MezSp->setGeometry(QRect(190, 210, 42, 22));
        Body = new QLabel(Nastaveni);
        Body->setObjectName(QString::fromUtf8("Body"));
        Body->setGeometry(QRect(30, 20, 131, 16));
        BdSp = new QSpinBox(Nastaveni);
        BdSp->setObjectName(QString::fromUtf8("BdSp"));
        BdSp->setGeometry(QRect(190, 20, 42, 22));
        DobaTrvaniBon = new QLabel(Nastaveni);
        DobaTrvaniBon->setObjectName(QString::fromUtf8("DobaTrvaniBon"));
        DobaTrvaniBon->setGeometry(QRect(200, 290, 151, 16));
        DoBonSp = new QSpinBox(Nastaveni);
        DoBonSp->setObjectName(QString::fromUtf8("DoBonSp"));
        DoBonSp->setGeometry(QRect(350, 290, 42, 22));
        c1BarvaPb = new QPushButton(Nastaveni);
        c1BarvaPb->setObjectName(QString::fromUtf8("c1BarvaPb"));
        c1BarvaPb->setGeometry(QRect(190, 110, 50, 50));
        c1BarvaPb->setIconSize(QSize(40, 40));
        c2BarvaPb = new QPushButton(Nastaveni);
        c2BarvaPb->setObjectName(QString::fromUtf8("c2BarvaPb"));
        c2BarvaPb->setGeometry(QRect(270, 110, 50, 50));
        c2BarvaPb->setIconSize(QSize(40, 40));

        retranslateUi(Nastaveni);
        QObject::connect(buttonBox, SIGNAL(accepted()), Nastaveni, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Nastaveni, SLOT(reject()));

        QMetaObject::connectSlotsByName(Nastaveni);
    } // setupUi

    void retranslateUi(QDialog *Nastaveni)
    {
        Nastaveni->setWindowTitle(QApplication::translate("Nastaveni", "Nastaven\303\255", nullptr));
        Tloustka->setText(QApplication::translate("Nastaveni", "Po\304\215\303\241te\304\215n\303\255 tlou\305\241\305\245ka \304\215erv\305\257: ", nullptr));
        Rychlost->setText(QApplication::translate("Nastaveni", "Rychlost pohybu:", nullptr));
        Barva->setText(QApplication::translate("Nastaveni", "Barva \304\215erv\305\257:", nullptr));
        CetMez->setText(QApplication::translate("Nastaveni", "\304\214etnost mezer: ", nullptr));
        CetBon->setText(QApplication::translate("Nastaveni", "\304\214etnost bonus\305\257 (s):", nullptr));
        MezCb->setText(QApplication::translate("Nastaveni", "Mezery", nullptr));
        BonCb->setText(QApplication::translate("Nastaveni", "Bonusy", nullptr));
        Body->setText(QApplication::translate("Nastaveni", "V\303\255t\304\233zn\303\275 po\304\215et bod\305\257:", nullptr));
        DobaTrvaniBon->setText(QApplication::translate("Nastaveni", "Doba trv\303\241n\303\255 bonus\305\257 (s): ", nullptr));
        c1BarvaPb->setText(QString());
        c2BarvaPb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Nastaveni: public Ui_Nastaveni {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NASTAVENI_H
