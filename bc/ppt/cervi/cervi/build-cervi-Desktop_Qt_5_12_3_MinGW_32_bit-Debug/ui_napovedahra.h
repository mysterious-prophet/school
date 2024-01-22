/********************************************************************************
** Form generated from reading UI file 'napovedahra.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAPOVEDAHRA_H
#define UI_NAPOVEDAHRA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_napovedaHra
{
public:
    QTextEdit *zaklInfoTe;

    void setupUi(QDialog *napovedaHra)
    {
        if (napovedaHra->objectName().isEmpty())
            napovedaHra->setObjectName(QString::fromUtf8("napovedaHra"));
        napovedaHra->resize(750, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(napovedaHra->sizePolicy().hasHeightForWidth());
        napovedaHra->setSizePolicy(sizePolicy);
        napovedaHra->setMinimumSize(QSize(750, 500));
        napovedaHra->setMaximumSize(QSize(750, 500));
        zaklInfoTe = new QTextEdit(napovedaHra);
        zaklInfoTe->setObjectName(QString::fromUtf8("zaklInfoTe"));
        zaklInfoTe->setGeometry(QRect(0, 0, 750, 500));

        retranslateUi(napovedaHra);

        QMetaObject::connectSlotsByName(napovedaHra);
    } // setupUi

    void retranslateUi(QDialog *napovedaHra)
    {
        napovedaHra->setWindowTitle(QApplication::translate("napovedaHra", "N\303\241pov\304\233da ke H\305\231e", nullptr));
        zaklInfoTe->setHtml(QApplication::translate("napovedaHra", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Z\303\241kladn\303\255 informace:</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Hra je zalo\305\276ena na h\305\231e Achtung! Die Kurve. Ve h\305\231e spolu soupe\305\231\303\255 dva \304\215ervi o to, kter\303\275 vydr\305\276\303\255 d\303\251le nenarazit do sebe, do okraje \304\215i do druh\303\251ho \304\215erva. </p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; ma"
                        "rgin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Ovl\303\241d\303\241n\303\255:</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Hr\303\241\304\215 1: \305\241ipky</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Hr\303\241\304\215 2: WASD</p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0"
                        "px;\"><span style=\" font-size:10pt; font-weight:600;\">Nastaven\303\255:</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Je mo\305\276n\303\251 nastavit rychlost pohybu, tlou\305\241\305\245ku i barvu obou \304\215erv\305\257. D\303\241le je mo\305\276n\303\251 nastavit, zda a jak \304\215asto \304\215ervi d\304\233laj\303\255 mezery. Je tak\303\251 mo\305\276n\303\251 nastavit v\303\275stkyt bonus\305\257, kter\303\275ch se ve h\305\231e nach\303\241z\303\255 celkem 7, jak \304\215asto se bonusy objevuj\303\255 a jak dlouho trv\303\241 jejich efekt.</p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font"
                        "-weight:600;\">P\305\231ehled bonus\305\257:</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1. \304\214erv, kter\303\275 bonus sebral m\303\241 na danou dobu pouze polovi\304\215n\303\255 tlou\305\241\305\245ku.</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2. \304\214erv, kter\303\275 bonus sebral se po danou dobu pohybuje polovi\304\215n\303\255 rychlost\303\255.</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3. \304\214erv, kter\303\275 bonus sebral po danou dobu nezanech\303\241v\303\241 stopu.</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4. \304\214erv, kter\303\275 bonus sebral po danou dobu m\305\257\305"
                        "\276e k\305\231\303\255\305\276it stopu sebe i oponenta a tak\303\251 se pohybovat skrz okraje hern\303\255ho okna (v takov\303\251m p\305\231\303\255pad\304\233 se objev\303\255 na opa\304\215n\303\251 stran\304\233 hern\303\255 obrazovky).</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">5. Soupe\305\231 se pohybuje dvojn\303\241sobnou rychlost\303\255.</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">6. Soupe\305\231 zanech\303\241v\303\241 dvojn\303\241sobnou tlou\305\241\305\245ku stopy.</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">7. Ob\304\233ma soupe\305\231\305\257m je vymaz\303\241na moment\303\241ln\303\255 stopa za dan\303\251 kolo.</p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:"
                        "0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class napovedaHra: public Ui_napovedaHra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAPOVEDAHRA_H
