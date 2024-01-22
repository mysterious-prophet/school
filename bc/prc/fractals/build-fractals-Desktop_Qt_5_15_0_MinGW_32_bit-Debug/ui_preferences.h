/********************************************************************************
** Form generated from reading UI file 'preferences.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_H
#define UI_PREFERENCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabGeometry;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLabel *lblX1;
    QLineEdit *editX1;
    QLabel *lblY1;
    QLineEdit *editY1;
    QLabel *lblX2;
    QLineEdit *editX2;
    QLabel *lblY2;
    QLineEdit *editY2;
    QHBoxLayout *horizontalLayout;
    QLabel *lblIterations;
    QLineEdit *editIterations;
    QSpacerItem *verticalSpacer;
    QWidget *tabFractal;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbMandelbrot;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblExponent;
    QSpinBox *sbExponent;
    QRadioButton *rbJulia;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblCRe;
    QLineEdit *editCRe;
    QLabel *lblCIm;
    QLineEdit *editCIm;
    QCheckBox *ChbColors;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QString::fromUtf8("Preferences"));
        Preferences->resize(356, 241);
        verticalLayout_2 = new QVBoxLayout(Preferences);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(Preferences);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabGeometry = new QWidget();
        tabGeometry->setObjectName(QString::fromUtf8("tabGeometry"));
        verticalLayout_3 = new QVBoxLayout(tabGeometry);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblX1 = new QLabel(tabGeometry);
        lblX1->setObjectName(QString::fromUtf8("lblX1"));

        gridLayout->addWidget(lblX1, 0, 0, 1, 1);

        editX1 = new QLineEdit(tabGeometry);
        editX1->setObjectName(QString::fromUtf8("editX1"));

        gridLayout->addWidget(editX1, 0, 1, 1, 2);

        lblY1 = new QLabel(tabGeometry);
        lblY1->setObjectName(QString::fromUtf8("lblY1"));

        gridLayout->addWidget(lblY1, 0, 3, 1, 1);

        editY1 = new QLineEdit(tabGeometry);
        editY1->setObjectName(QString::fromUtf8("editY1"));

        gridLayout->addWidget(editY1, 0, 4, 1, 1);

        lblX2 = new QLabel(tabGeometry);
        lblX2->setObjectName(QString::fromUtf8("lblX2"));

        gridLayout->addWidget(lblX2, 1, 0, 1, 2);

        editX2 = new QLineEdit(tabGeometry);
        editX2->setObjectName(QString::fromUtf8("editX2"));

        gridLayout->addWidget(editX2, 1, 2, 1, 1);

        lblY2 = new QLabel(tabGeometry);
        lblY2->setObjectName(QString::fromUtf8("lblY2"));

        gridLayout->addWidget(lblY2, 1, 3, 1, 1);

        editY2 = new QLineEdit(tabGeometry);
        editY2->setObjectName(QString::fromUtf8("editY2"));

        gridLayout->addWidget(editY2, 1, 4, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblIterations = new QLabel(tabGeometry);
        lblIterations->setObjectName(QString::fromUtf8("lblIterations"));

        horizontalLayout->addWidget(lblIterations);

        editIterations = new QLineEdit(tabGeometry);
        editIterations->setObjectName(QString::fromUtf8("editIterations"));

        horizontalLayout->addWidget(editIterations);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(tabGeometry, QString());
        tabFractal = new QWidget();
        tabFractal->setObjectName(QString::fromUtf8("tabFractal"));
        verticalLayout = new QVBoxLayout(tabFractal);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbMandelbrot = new QRadioButton(tabFractal);
        rbMandelbrot->setObjectName(QString::fromUtf8("rbMandelbrot"));
        rbMandelbrot->setChecked(true);

        verticalLayout->addWidget(rbMandelbrot);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblExponent = new QLabel(tabFractal);
        lblExponent->setObjectName(QString::fromUtf8("lblExponent"));

        horizontalLayout_3->addWidget(lblExponent);

        sbExponent = new QSpinBox(tabFractal);
        sbExponent->setObjectName(QString::fromUtf8("sbExponent"));
        sbExponent->setMinimum(2);
        sbExponent->setMaximum(10);

        horizontalLayout_3->addWidget(sbExponent);


        verticalLayout->addLayout(horizontalLayout_3);

        rbJulia = new QRadioButton(tabFractal);
        rbJulia->setObjectName(QString::fromUtf8("rbJulia"));

        verticalLayout->addWidget(rbJulia);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblCRe = new QLabel(tabFractal);
        lblCRe->setObjectName(QString::fromUtf8("lblCRe"));

        horizontalLayout_2->addWidget(lblCRe);

        editCRe = new QLineEdit(tabFractal);
        editCRe->setObjectName(QString::fromUtf8("editCRe"));

        horizontalLayout_2->addWidget(editCRe);

        lblCIm = new QLabel(tabFractal);
        lblCIm->setObjectName(QString::fromUtf8("lblCIm"));

        horizontalLayout_2->addWidget(lblCIm);

        editCIm = new QLineEdit(tabFractal);
        editCIm->setObjectName(QString::fromUtf8("editCIm"));

        horizontalLayout_2->addWidget(editCIm);


        verticalLayout->addLayout(horizontalLayout_2);

        ChbColors = new QCheckBox(tabFractal);
        ChbColors->setObjectName(QString::fromUtf8("ChbColors"));

        verticalLayout->addWidget(ChbColors);

        verticalSpacer_2 = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        tabWidget->addTab(tabFractal, QString());

        verticalLayout_2->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(Preferences);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
        lblX1->setBuddy(editX1);
        lblY1->setBuddy(editY1);
        lblX2->setBuddy(editX2);
        lblY2->setBuddy(editY2);
        lblIterations->setBuddy(editIterations);
        lblExponent->setBuddy(sbExponent);
        lblCRe->setBuddy(editCRe);
        lblCIm->setBuddy(editCIm);
#endif // QT_CONFIG(shortcut)

        retranslateUi(Preferences);
        QObject::connect(buttonBox, SIGNAL(accepted()), Preferences, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Preferences, SLOT(reject()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QDialog *Preferences)
    {
        Preferences->setWindowTitle(QCoreApplication::translate("Preferences", "Preferences", nullptr));
        lblX1->setText(QCoreApplication::translate("Preferences", "x1: ", nullptr));
        lblY1->setText(QCoreApplication::translate("Preferences", "y1: ", nullptr));
        lblX2->setText(QCoreApplication::translate("Preferences", "x2:", nullptr));
        lblY2->setText(QCoreApplication::translate("Preferences", "y2: ", nullptr));
        lblIterations->setText(QCoreApplication::translate("Preferences", "&Iterations: ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeometry), QCoreApplication::translate("Preferences", "&Geometry", nullptr));
        rbMandelbrot->setText(QCoreApplication::translate("Preferences", "&Mandelbrot set", nullptr));
        lblExponent->setText(QCoreApplication::translate("Preferences", "Exponent", nullptr));
        rbJulia->setText(QCoreApplication::translate("Preferences", "&Quadratic Julia set", nullptr));
        lblCRe->setText(QCoreApplication::translate("Preferences", "&Real: ", nullptr));
        lblCIm->setText(QCoreApplication::translate("Preferences", "I&mag: ", nullptr));
        ChbColors->setText(QCoreApplication::translate("Preferences", "Use colors", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabFractal), QCoreApplication::translate("Preferences", "&Fractal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_H
