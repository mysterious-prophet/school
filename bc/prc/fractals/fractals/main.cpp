#include "fractalviewer.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("fractals_cz", ":/translations");
    a.installTranslator(&translator);
    FractalViewer w;
    w.show();

    return a.exec();
}

//doplnit dole v casti fraktal tlacitko color
