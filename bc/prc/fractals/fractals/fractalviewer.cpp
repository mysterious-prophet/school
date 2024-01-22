#include "fractalviewer.h"
#include <QLabel>
#include <QScrollArea>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QEventLoop>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QtMath>


#include "preferences.h"
#include "fractals.h"

FractalViewer::FractalViewer(QWidget *parent)
    : QMainWindow(parent), w(1680), h(1050),
      x1(-2.0), x2(1.5), y1(-1.5), y2(1.5), cre(-0.123), cim(0.745), type(MANDELBROT), exponent(2), iterations(500)
{
    loadSettings();
    setupForm();
    setupActions();
}

void FractalViewer::setupForm(){
    lblFractal = new QLabel;
    lblFractal->setSizePolicy(QSizePolicy::Ignored,
                              QSizePolicy::Ignored);
    lblFractal->setScaledContents(true);
    scrollArea = new QScrollArea;
    scrollArea->setWidget(lblFractal);
    this->setCentralWidget(scrollArea);
    this->setWindowTitle(tr("Fractal Viewer"));
    this->resize(w, h);
}

void FractalViewer::setupActions(){
    QIcon iconDraw = QIcon::fromTheme("applications-graphics",
                                      QIcon(":/icons/draw.png"));
    actDraw = new QAction(tr("&Draw"));
    actDraw->setToolTip(tr("Draws fractal"));
    actDraw->setStatusTip(tr("Draws fractal"));
    actDraw->setIcon(iconDraw);
    actDraw->setShortcut(QKeySequence(tr("Ctrl+D")));


    QIcon iconAbort = QIcon::fromTheme("process-stop",
                                       QIcon(":/icons/abort.png"));
    actAbort = new QAction(tr("&Abort"));
    actAbort->setToolTip(tr("Aborts drawing", "tool tip"));
    actAbort->setStatusTip(tr("Aborts drawing", "status tip"));
    actAbort->setShortcut(QKeySequence::Cancel);
    actAbort->setIcon(iconAbort);
    actAbort->setEnabled(false);

    QIcon iconQuit = QIcon::fromTheme("application-exit",
                                      QIcon(":/icons/quit.png"));
    actQuit = new QAction(tr("E&xit"));
    actQuit->setShortcut(QKeySequence::Quit);
    actQuit->setToolTip(tr("Exits the fractal viewer"));
    actQuit->setStatusTip(tr("Exits the application"));
    actQuit->setIcon(iconQuit);

    QIcon iconPreferences = QIcon::fromTheme("preferences-system",
                                             QIcon(":/icons/preferences.png"));

    actPreferences = new QAction(tr("&Preferences..."));
    actPreferences->setToolTip(tr("Configures application"));
    actPreferences->setStatusTip(tr("Configures application"));
    actPreferences->setIcon(iconPreferences);
    actPreferences->setShortcut(QKeySequence::Preferences);

    toolBar = addToolBar("toolbar");

    mnuFractal = new QMenu(tr("&Fractal"));
    mnuFractal->addAction(actDraw);
    mnuFractal->addAction(actAbort);
    mnuFractal->addAction(actQuit);
    menuBar()->addMenu(mnuFractal);

    mnuOptions = new QMenu(tr("Options"));
    mnuOptions->addAction(actPreferences);
    menuBar()->addMenu(mnuOptions);

    toolBar->addAction(actDraw);
    toolBar->addAction(actAbort);
    toolBar->addAction(actQuit);
    toolBar->addSeparator();
    toolBar->addAction(actPreferences);

    connect(actQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(actPreferences, SIGNAL(triggered()),
            this, SLOT(configure()));
    connect(actDraw, SIGNAL(triggered()), this, SLOT(draw()));
    connect(actAbort, SIGNAL(triggered()), this, SLOT(abort()));
    this->statusBar()->showMessage(tr("Application started"), 3000);
}

FractalViewer::~FractalViewer()
{
}


void FractalViewer::loadSettings(){
    QSettings settings("FNSPE", "FractalDrawer");
    x1 = settings.value("geometry/x1", -2).toDouble();
    x2 = settings.value("geometry/x2", 1.5).toDouble();
    y1 = settings.value("geometry/y1", -1.5).toDouble();
    y2 = settings.value("geometry/y2", 1.5).toDouble();
    cre = settings.value("fractal/cre", -0.123).toDouble();
    cim = settings.value("fractal/cim", 0.745).toDouble();
    type = static_cast<FractalType>(settings.value("fractal/type", MANDELBROT).toUInt() )== MANDELBROT ?
                MANDELBROT : JULIA;
    exponent = settings.value("fractal/exponent", 2).toUInt();
    iterations = settings.value("geometry/iterations", 500).toUInt();
    colors = settings.value("fractal/colors", true).toBool();
}

void FractalViewer::saveSettings(){
    QSettings settings("FNSPE", "FractalDrawer");
    settings.setValue("geometry/x1", x1);
    settings.setValue("geometry/x2", x2);
    settings.setValue("geometry/y1", y1);
    settings.setValue("geometry/y2", y2);
    settings.setValue("geometry/iterations", iterations);
    settings.setValue("fractal/cre", cre);
    settings.setValue("fractal/cim", cim);
    settings.setValue("fractal/type", type);
    settings.setValue("fractal/exponent", exponent);
    settings.setValue("fractal/colors", colors);
}

void FractalViewer::closeEvent(QCloseEvent *event){
    if(
    QMessageBox::question(this,
                          tr("Really quit?"),
                          tr("Do you really want to quit?"))
     == QMessageBox::Yes){
        saveSettings();
        event->accept();
    } else{
        event->ignore();
    }
}

void FractalViewer::abort(){
    aborted = true;
}

void FractalViewer::draw(){
    QEventLoop loop;
    QImage image(w, h, QImage::Format_RGB888);
    double x, y; //c = x + yi
    double dx, dy;
    aborted = false;
    actAbort->setEnabled(true);
    actDraw->setEnabled(false);

    dx = (x2-x1)/w;
    dy = (y2-y1)/h;
    int color;

    x = x1;
    for(unsigned int i = 0; i < w; i++){
        y = y1;
        for(unsigned int j = 0; j < h; j++){
            if(type == MANDELBROT){
                color = mandelbrot(x, y, iterations, exponent);
            } else{
                color = julia(x, y, cre, cim, iterations);
            }
            if(colors == true){
                image.setPixel(i, j, qRgb(sin(color) * 150, cos(color) * 150, tan(color) * 150));
            } else {
                image.setPixel(i, j, color);
            }
            y = y + dy;
        }
        x = x + dx;
        statusBar()->showMessage(tr("Completed %1%").arg(i*100/w));
        loop.processEvents(QEventLoop::AllEvents);
        if(aborted){
            actAbort->setEnabled(false);
            actDraw->setEnabled(true);
            statusBar()->showMessage(tr("Drawing aborted"), 3000);
            return;
        }
    }
    lblFractal->setPixmap(QPixmap::fromImage(image));
    lblFractal->adjustSize();
    actAbort->setEnabled(false);
    actDraw->setEnabled(true);
    statusBar()->showMessage(tr("Done!"), 2000);

}

void FractalViewer::configure(){
    Preferences config;
    config.setX1(x1);
    config.setX2(x2);
    config.setY1(y1);
    config.setY2(y2);
    config.setCRe(cre);
    config.setCIm(cim);
    config.setType(type);
    config.setExponent(exponent);
    config.setIterations(iterations);
    config.setChBColors(colors);
    if(config.exec() == QDialog::Accepted){
        x1 = config.getX1();
        x2 = config.getX2();
        y1 = config.getY1();
        y2 = config.getY2();
        iterations = config.getIterations();
        cre = config.getCRe();
        cim = config.getCIm();
        type = config.getType();
        exponent = config.getExponent();
        colors = config.getChBColors();
        qDebug("Accepted!");
    }
}
