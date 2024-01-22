/********************************************************************************
** Form generated from reading UI file 'oautorovi.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OAUTOROVI_H
#define UI_OAUTOROVI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_oAutorovi
{
public:
    QTextEdit *oAutoroviTe;

    void setupUi(QDialog *oAutorovi)
    {
        if (oAutorovi->objectName().isEmpty())
            oAutorovi->setObjectName(QString::fromUtf8("oAutorovi"));
        oAutorovi->resize(450, 100);
        oAutorovi->setMinimumSize(QSize(450, 100));
        oAutorovi->setMaximumSize(QSize(450, 100));
        oAutoroviTe = new QTextEdit(oAutorovi);
        oAutoroviTe->setObjectName(QString::fromUtf8("oAutoroviTe"));
        oAutoroviTe->setGeometry(QRect(0, 0, 450, 100));

        retranslateUi(oAutorovi);

        QMetaObject::connectSlotsByName(oAutorovi);
    } // setupUi

    void retranslateUi(QDialog *oAutorovi)
    {
        oAutorovi->setWindowTitle(QApplication::translate("oAutorovi", "O autorovi", nullptr));
        oAutoroviTe->setMarkdown(QApplication::translate("oAutorovi", "**Dle hry Achtung! Die Kurve napsal M.P., 2019.**\n"
"\n"
"", nullptr));
        oAutoroviTe->setHtml(QApplication::translate("oAutorovi", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:5px; margin-bottom:5px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Dle hry Achtung! Die Kurve napsal M.P., 2019.</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class oAutorovi: public Ui_oAutorovi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OAUTOROVI_H
