#ifndef FRACTALVIEWER_H
#define FRACTALVIEWER_H

#include <QMainWindow>
#include "fractals.h"

class QLabel;
class QScrollArea;
class QMenu;
class QAction;
class QToolBar;

class QCloseEvent;

class FractalViewer : public QMainWindow
{
    Q_OBJECT
    QLabel *lblFractal;
    QScrollArea *scrollArea;
    QMenu *mnuFractal;
    QAction *actDraw;
    QAction *actAbort;
    QAction *actQuit;
    QMenu *mnuOptions;
    QAction *actPreferences;
    QToolBar *toolBar;
    void setupForm();
    void setupActions();
    unsigned int w, h;
    bool aborted;
    double x1, x2, y1, y2;
    double cre, cim; //pro kvadratickou Juliovu mnozinu
    FractalType type;
    unsigned int exponent;
    unsigned int iterations;
    bool colors;
    void saveSettings();
    void loadSettings();
    void closeEvent(QCloseEvent *event);
private slots:
    void configure();
    void draw();
    void abort();
public:
    FractalViewer(QWidget *parent = 0);
    ~FractalViewer();
};

#endif // FRACTALVIEWER_H
