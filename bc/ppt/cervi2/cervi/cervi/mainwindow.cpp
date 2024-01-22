#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //nastav ui a obrazek, ktery slouzi jako pozadi hry
    ui->setupUi(this);
    image = QImage(this->width(), this->height(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    timerPohyb = new QTimer(); //vytvor timery
    timerBonusyCet = new QTimer();
    //c1.timerBonusyDoba = new QTimer;
    //c2.timerBonusyDoba = new QTimer;

    ui->hrac1Lb->move(this->width()/5, this->height()/5);
    ui->hrac2Lb->move(3*this->width()/5, this->height()/5);
    ui->hrac1Le->move(this->width()/5, this->height()/4);
    ui->hrac2Le->move(3*this->width()/5, this->height()/4);
    ui->novaHraBt->move(43*this->width()/100,this->height()/3);

    vitezneBody = 10; //nastav defaultni hodnoty pro hru
    rychlost = 35;
    barvaC1 = Qt::red;
    barvaC2 = Qt::green;
    mezery = true;
    mezeryCet = 30;
    bonusy = true;
    bonusyCet = 8;
    defTloustka = 7;
    defDobaTrvaniBon = 8;
    srazkaC1 = false;
    srazkaC2 = false;

    bonus = new QLabel(this);
    bonus->setVisible(false);

    body.resize(3);
    hrac1Body = new QLabel(this);
    hrac2Body = new QLabel(this);
    ui->statusBar->addWidget(hrac1Body);
    ui->statusBar->addWidget(hrac2Body);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hra(int pocet)
{
    int rozmerX = this->width() - 200; //na pocatku kola vygeneruj nahodne pozici cervu, ale ne prilis blizko okraji plochy
    int rozmerY = this->height() - 200;
    int xc1 = 100 + QRandomGenerator::global()->generate() % rozmerX;
    int xc2 = 100 + QRandomGenerator::global()->generate() % rozmerX;
    int yc1 = 100 + QRandomGenerator::global()->generate() % rozmerY;
    int yc2 = 100 + QRandomGenerator::global()->generate() % rozmerY;

    c1 = Cerv(xc1,yc1, barvaC1, defTloustka); //vytvor cervy
    c2 = Cerv(xc2,yc2, barvaC2, defTloustka);

    //pokud jsou ve hre bonusu zacni odpocitavat spawn prvniho bonusu
    if(bonusy){
        timerBonusyCet = new QTimer();
        timerBonusyCet->connect(timerBonusyCet, SIGNAL(timeout()),this, SLOT(timerB()));
        timerBonusyCet->start(bonusyCet*1000);

    }

    //zacni odpocitavat pohyb cervu
    timerPohyb = new QTimer();
    timerPohyb->connect(timerPohyb, SIGNAL(timeout()),this,SLOT(timerP()));
    timerPohyb->start(100-rychlost);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{   //ovladani cervu a pauza a restart mezernikem
    switch (event->key()) {
        case Qt::Key_Up: //nahoru muzu pokud momentalne nejdu dolu, nemuzu se vracet presne po sve stope
            if(c1.getSmer() != 2)
                c1.setSmer(0);
            break;
        case Qt::Key_Right:
            if (c1.getSmer() != 3)
                c1.setSmer(1);
            break;
        case Qt::Key_Down:
            if (c1.getSmer() != 0)
                c1.setSmer(2);
            break;
        case Qt::Key_Left:
            if(c1.getSmer() !=1)
                c1.setSmer(3);
            break;
        case Qt::Key_W:
            if(c2.getSmer() != 2)
                c2.setSmer(0);
            break;
        case Qt::Key_D:
            if(c2.getSmer() != 3)
                c2.setSmer(1);
            break;
        case Qt::Key_S:
            if(c2.getSmer() != 0)
                c2.setSmer(2);
            break;
        case  Qt::Key_A:
            if(c2.getSmer() != 1)
                c2.setSmer(3);
            break;
        case Qt::Key_Space:
            if(konecKola == true && konecHry!=true){ //pokud je konec kola, zacni nove kolo
                restart();
            }
            else if(konecKola == true && konecHry == true){//pokud je konec hry, prejdi na uvodni obrazovku
                MainWindow::on_actionNova_hra_triggered();
            }
            else if(timerPohyb->isActive()){ //pokud se cervi pohybuji tak udelej pauzu
                timerPohyb->stop();
                if(bonusy)
                    timerBonusyCet->stop();
            }
            else if (!timerPohyb->isActive()){ //pokud je pauza zacni hrat
                timerPohyb->start(100-rychlost);
                if(bonusy)
                    timerBonusyCet->start(1000*bonusyCet);
            }
            break;
    }
}

void MainWindow::restart()
{
    image.fill(Qt::white); //smaz platno a priprav na nove kolo
    timerBDC1();
    timerBDC2();
    if(bonusy) // zastav odpocitavani spawnovani bonusu
        timerBonusyCet->stop();
    konecKola = false; //konec kola hry neni
    srazkaC1 = false;
    srazkaC2 = false;
    rychlost = 35;
    c1.setNasRych(1); //pokud se nektery cerv pohyboval rychleji tak nastav nasobice na 1
    c2.setNasRych(1);
    hra(0); //zacni nove kolo
}

void MainWindow::timerP()
{
    static int pocet = 0; //pohybuj cervy
    pohyb(pocet); //pocet je promenna pouzivana k vypocitavani mezer
    pocet +=1;
}

void MainWindow::timerB()
{
        cisloBonusu = 1+ genBonus(); //vygeneruj bonus 1 + 0..6
        int rozmerX = this->width() - 100; //vygeneruj nahodne umisteni ve hre
        int rozmerY = this->height() - 100;
        int xB = 50 + QRandomGenerator::global()->generate() % rozmerX;
        int yB = 50 + QRandomGenerator::global()->generate() % rozmerY;

        QPixmap ikona; //ikona bonusu

        switch (cisloBonusu) { //nahraj ikony
        case 1: //ja 0.5x rychlost
            ikona.load(":bonIkony/01.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("1");
            //bonus->show();
            bonus->setVisible(true);
            break;
        case 2: // ja 0.5 cara
            ikona.load(":bonIkony/02.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("2");
            bonus->show();
            bonus->setVisible(true);
            break;
        case 3: //ja nekreslim caru
            ikona.load(":bonIkony/03.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("3");
            bonus->show();
            bonus->setVisible(true);
            break;
        case 4: // ja muzu zleda doprava a zeshora dolu atd. pres okraj
            ikona.load(":bonIkony/04.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("4");
            bonus->show();
            bonus->setVisible(true);
            break;
        case 5: // souper 2x rychlost
            ikona.load(":bonIkony/05.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("5");
            bonus->show();
            bonus->setVisible(true);
            break;
        case 6: //souper 2x tloustka
            ikona.load(":bonIkony/06.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("6");
            bonus->show();
            bonus->setVisible(true);
            break;
        case 7: // obema smazana cara
            ikona.load(":bonIkony/07.png");
            bonus->setPixmap(ikona);
            bonus->setGeometry(xB, yB, 32, 32);
            bonus->setStatusTip("7");
            //bonus->setProperty("cislo",7);
            bonus->show();
            bonus->setVisible(true);
            break;

        }
}

void MainWindow::timerBDC1()
{ //zrusi bonusy aktivovane cervem1
  if(c1.getTloustka() < defTloustka){
      c1.setTloustka(defTloustka);
      c1.setNasRych(1);
  }
  if(c2.getTloustka() > defTloustka){
      QPainter painter(&image);
      QPen penC2Oprava;
      penC2Oprava.setColor(Qt::white);
      penC2Oprava.setWidth(defTloustka*2);
      painter.setPen(penC2Oprava);
      painter.drawPoint(c2.getPozice());

      update();
      c2.setTloustka(defTloustka);
      timerPohyb->setInterval(100-rychlost);
      c1.setNasRych(1);
  }
  if(c2.getNasRych() > 1 && timerPohyb->interval() == 100-rychlost)
      c2.setNasRych(1);
  if(!c1.getKresli())
      c1.setKresli(true);
  if(c1.getPruchozi())
      c1.setPruchozi(false);
  if(timerPohyb->interval() > (100-rychlost))
      timerPohyb->setInterval(100-rychlost);
}

void MainWindow::timerBDC2()
{ //zrusi bonusy aktivovane cervem2
    if(c2.getTloustka() < defTloustka){
        c2.setTloustka(defTloustka);
        c2.setNasRych(1);
    }
    if(c1.getTloustka() > defTloustka){
        QPainter painter(&image);
        QPen penC1Oprava;
        penC1Oprava.setColor(Qt::white);
        penC1Oprava.setWidth(defTloustka*2);
        painter.setPen(penC1Oprava);
        painter.drawPoint(c1.getPozice());
        update();
        c1.setTloustka(defTloustka);
        timerPohyb->setInterval(100-rychlost);
        c2.setNasRych(1);
    }
    if(c1.getNasRych() > 1 && timerPohyb->interval() == 100-rychlost)
        c1.setNasRych(1);
    if(!c2.getKresli())
        c2.setKresli(true);
    if(c2.getPruchozi())
        c2.setPruchozi(false);
    if(timerPohyb->interval() > (100-rychlost))
        timerPohyb->setInterval(100-rychlost);
}

int MainWindow::genBonus()
{ //vygeneruje bonus 0..6
    return QRandomGenerator::global()->generate() % pocetBonusu;
}

void MainWindow::pohyb(int poc)
{ //pohybuje cervy
    QPainter painter(&image);
    QPen penC1; //vygeneruj platno a pera, ktera budou kreslit cervy
    QPen penC2;

    penC1.setWidth(c1.getTloustka()); //nastav tloustku prvniho cerva
    penC1.setStyle(Qt::SolidLine);
    //penC1.setCapStyle(Qt::RoundCap);
    //penC1.setJoinStyle(Qt::RoundJoin);

    switch(c1.getSmer()){
        case 0:
        if(c1.getKresli()){ //pokud cerv zanechava viditelnou caru
            if(mezery){ //a pokud jsou ve hre mezery
                if(poc % mezeryCet <= 2 || poc % mezeryCet > mezeryCet-2){ //tak kazdou urcitou dobu vykresli mezeru, tzn bilou caru
                    penC1.setColor(Qt::white);
                }else { //jinak kresli barevne
                    penC1.setColor(c1.getBarva());
                }
            }else { //pokud nejsou mezery kresli stale barevne
                penC1.setColor(c1.getBarva());
            }
            painter.setPen(penC1); //platnu nastav pripravene pero
            if(c1.getNasRych()>=1){ //tolikrat kolik je nasobic vykresli cerva, cerv se muze pohybovat rychlosti x1 a x2
                for(int i = 1; i<=c1.getNasRych(); i++){
                    painter.drawPoint(c1.getPozice()); //nakresli bod s barvou cerva
                    c1.setY(c1.getPozice().y()-c1.getTloustka()); //posun se dal
                    if(image.pixelColor(c1.getPozice().x(), c1.getPozice().y()-c1.getTloustka()/2) != Qt::white){//je li v tomto miste uz jiny cerv nebo okraj tak nastav srazku
                        srazkaC1 = true;
                        break;
                    }
                }
                break;
            }
            break;
        }else{ //pokud cerv nezanechava stopu kvuli bonusu, kresli bile
            penC1.setColor(Qt::white);
            painter.setPen(penC1);
            painter.drawPoint(c1.getPozice());
            c1.setY(c1.getPozice().y()-c1.getTloustka());
            break;
        }
        case 1: //obdobne pro vsechny smery
        if(c1.getKresli()){
            if(mezery){
                if(poc % mezeryCet <= 2 || poc %  mezeryCet > mezeryCet-2){
                    penC1.setColor(Qt::white);
                }else {
                    penC1.setColor(c1.getBarva());
                }
            }else {
                penC1.setColor(c1.getBarva());
            }
            painter.setPen(penC1);
            if(c1.getNasRych()>=1){
                for(int i = 1; i<=c1.getNasRych(); i++){
                    painter.drawPoint(c1.getPozice());
                    c1.setX(c1.getPozice().x()+c1.getTloustka());
                    if(image.pixelColor(c1.getPozice().x()+c1.getTloustka()/2,c1.getPozice().y()) != Qt::white){
                        srazkaC1 = true;
                        break;
                    }
                }
                break;
            }
            break;
        }else{
            penC1.setColor(Qt::white);
            painter.setPen(penC1);
            painter.drawPoint(c1.getPozice());
            c1.setX(c1.getPozice().x()+c1.getTloustka());
            break;
        }
        case 3:
        if(c1.getKresli()){
            if(mezery){
                if(poc % mezeryCet <= 2 || poc % mezeryCet > mezeryCet-2){
                    penC1.setColor(Qt::white);
                }else {
                    penC1.setColor(c1.getBarva());
                }
            }else {
                penC1.setColor(c1.getBarva());
            }
            painter.setPen(penC1);
            if(c1.getNasRych()>=1){
                for(int i = 1; i<=c1.getNasRych(); i++){
                    painter.drawPoint(c1.getPozice());
                    c1.setX(c1.getPozice().x()-c1.getTloustka());
                    if(image.pixelColor(c1.getPozice().x()-c1.getTloustka()/2,c1.getPozice().y()) != Qt::white){
                        srazkaC1 = true;
                        break;
                    }
                }
                break;
            }
            break;
        }else{
            penC1.setColor(Qt::white);
            painter.setPen(penC1);
            painter.drawPoint(c1.getPozice());
            c1.setX(c1.getPozice().x()-c1.getTloustka());
            break;
        }
        case 2:
        if(c1.getKresli()){
            if(mezery){
                if(poc % mezeryCet <= 2 || poc % mezeryCet > mezeryCet-2){
                    penC1.setColor(Qt::white);
                }else {
                    penC1.setColor(c1.getBarva());
                }
            }else {
                penC1.setColor(c1.getBarva());
            }
            painter.setPen(penC1);
            if(c1.getNasRych()>=1){
                for(int i = 1; i<=c1.getNasRych(); i++){
                    painter.drawPoint(c1.getPozice());
                    c1.setY(c1.getPozice().y()+c1.getTloustka());
                    if(image.pixelColor(c1.getPozice().x(), c1.getPozice().y()+c1.getTloustka()/2) != Qt::white){
                        srazkaC1 = true;
                        break;
                    }
                }
                break;
            }
        }else{
            penC1.setColor(Qt::white);
            painter.setPen(penC1);
            painter.drawPoint(c1.getPozice());
            c1.setY(c1.getPozice().y()+c1.getTloustka());
        }

    }

   //update();
    penC2.setWidth(c2.getTloustka()); //priprav pero 2
    penC2.setStyle(Qt::SolidLine);

    switch (c2.getSmer()) { //obdobne jako pro cerva1
    case 0:
    if(c2.getKresli()){
        if(mezery){
            if(poc % mezeryCet <=3 ){
                penC2.setColor(Qt::white);
            }else{
                penC2.setColor(c2.getBarva());
            }
        }else {
            penC2.setColor(c2.getBarva());
        }
        painter.setPen(penC2);
         if(c2.getNasRych()>=1){
             for(int i = 1; i<=c2.getNasRych(); i++){
                 painter.drawPoint(c2.getPozice());
                 c2.setY(c2.getPozice().y()-c2.getTloustka());
                 if(image.pixelColor(c2.getPozice().x(), c2.getPozice().y()-c2.getTloustka()/2) != Qt::white){
                     srazkaC2 = true;
                     break;
                 }
             }
             break;
         }
         break;
        }else {
            penC2.setColor(Qt::white);
            painter.setPen(penC2);
            painter.drawPoint(c2.getPozice());
            c2.setY(c2.getPozice().y()-c2.getTloustka());
            break;
        }
    case 1:
    if(c2.getKresli()){
        if(mezery){
            if(poc % mezeryCet <=3 ){
                penC2.setColor(Qt::white);
            }else{
                penC2.setColor(c2.getBarva());
            }
        }else {
            penC2.setColor(c2.getBarva());
        }
        painter.setPen(penC2);
         if(c2.getNasRych()>=1){
             for(int i = 1; i<=c2.getNasRych(); i++){
                 painter.drawPoint(c2.getPozice());
                 c2.setX(c2.getPozice().x()+c2.getTloustka());
                 if(image.pixelColor(c2.getPozice().x()+c2.getTloustka()/2, c2.getPozice().y()) != Qt::white){
                     srazkaC2 = true;
                     break;
                 }
             }
             break;
         }
         break;
    }else{
        penC2.setColor(Qt::white);
        painter.setPen(penC2);
        painter.drawPoint(c2.getPozice());
        c2.setX(c2.getPozice().x()+c2.getTloustka());
        break;
    }
    case 3:
        if(c2.getKresli()){
        if(mezery){
            if(poc % mezeryCet <=3 ){
                penC2.setColor(Qt::white);
            }else{
                penC2.setColor(c2.getBarva());
            }
        }else {
            penC2.setColor(c2.getBarva());
        }
        painter.setPen(penC2);
         if(c2.getNasRych()>=1){
             for(int i = 1; i<=c2.getNasRych(); i++){
                 painter.drawPoint(c2.getPozice());
                 c2.setX(c2.getPozice().x()-c2.getTloustka());
                 if(image.pixelColor(c2.getPozice().x()-c2.getTloustka()/2, c2.getPozice().y()) != Qt::white){
                     srazkaC2 = true;
                     break;
                 }
             }
             break;
         }
         break;
        }else{
            penC2.setColor(Qt::white);
            painter.setPen(penC2);
            painter.drawPoint(c2.getPozice());
            c2.setX(c2.getPozice().x()-c2.getTloustka());
            break;
        }
    case 2:
    if(c2.getKresli()){
        if(mezery){
            if(poc % mezeryCet <=3 ){
                penC2.setColor(Qt::white);
            }else{
                penC2.setColor(c2.getBarva());
            }
        }else {
            penC2.setColor(c2.getBarva());
        }
        painter.setPen(penC2);
         if(c2.getNasRych()>=1){
             for(int i = 1; i<=c2.getNasRych(); i++){
                 painter.drawPoint(c2.getPozice());
                 c2.setY(c2.getPozice().y()+c2.getTloustka());
                 if(image.pixelColor(c2.getPozice().x(), c2.getPozice().y()+c2.getTloustka()/2) != Qt::white){
                     srazkaC2 = true;
                     break;
                 }
             }
             break;
         }
        // break;
    }else{
        penC2.setColor(Qt::white);
        painter.setPen(penC2);
        painter.drawPoint(c2.getPozice());
        c2.setY(c2.getPozice().y()+c2.getTloustka());
        break;
    }

    }

    //update();

    //pokud jsi na okraji nebo primo u tebe jiny cerv
    //if(c1.getPozice().x() <= 0 || c1.getPozice().x() > this->width() || c1.getPozice().y() <= 0 || c1.getPozice().y() > this->height() || image.pixelColor(c1.getPozice()) != Qt::white){
      //  srazka = true;
    //}

    if (srazkaC1 || (c1.getPozice().x() <= 0 || c1.getPozice().x() > this->width() || c1.getPozice().y() <= 30 || c1.getPozice().y() > this->height()) || image.pixelColor(c1.getPozice()) != Qt::white){
        if(!c1.getPruchozi()){ //pokud cerv nemuze projit pres cary nebo pres okraj
            timerPohyb->stop();
            if(timerBonusyCet->isActive())
                timerBonusyCet->stop();
            body[2] += 1;
            QString body2 =QString::number(body[2]);
            hrac2Body->setText(hrac2Jmeno + ": " + body2);
            konecKola = true;
            srazkaC1 = false;
            if (body[2] == vitezneBody){
                konecHry = true;
                ui->statusBar->showMessage("Vítězí " + hrac2Jmeno,2000);
        }
        }else{ //pokud muze a je na okraji tak ho vrat na opacny okraj
            if(c1.getPozice().x() < 1){
                c1.setX(this->width()-1);
                c1.setSmer(3);
            }
            if(c1.getPozice().x() > this->width()-1){
                c1.setX(1);
                c1.setSmer(1);
            }
            if(c1.getPozice().y() < 30){
                c1.setY(this->height()-1);
                c1.setSmer(0);
            }
            if(c1.getPozice().y() > this->height()-1){
                c1.setY(30);
                c1.setSmer(2);
            }
            srazkaC1 = false;

        }
    }

    //if(c2.getPozice().x() <= 0 || c2.getPozice().x() > this->width() || c2.getPozice().y() <= 0 || c2.getPozice().y() > this->height() || image.pixelColor(c2.getPozice()) != Qt::white){
      //  srazka = true;
    //}

   if(srazkaC2 || c2.getPozice().x() <= 0 || c2.getPozice().x() > this->width() || c2.getPozice().y() <= 30 || c2.getPozice().y() > this->height() || image.pixelColor(c2.getPozice()) != Qt::white){
       if(!c2.getPruchozi()){
               timerPohyb->stop();
               if(timerBonusyCet->isActive())
                   timerBonusyCet->stop();
               body[1] += 1;
               QString body1 = QString::number(body[1]);
               hrac1Body->setText(hrac1Jmeno + ": " + body1);
               konecKola = true;
               srazkaC2 = false;
               if(body[1] == vitezneBody){
                    konecHry = true;
                    ui->statusBar->showMessage("Vítězí " + hrac1Jmeno,2000);
               }
    }else{
           srazkaC2 = false;
               if(c2.getPozice().x() < 1){
                   c2.setX(this->width()-1);
                   c2.setSmer(3);
               }
               if(c2.getPozice().x() > this->width()-1){
                   c2.setX(1);
                   c2.setSmer(1);
               }
               if(c2.getPozice().y() < 30){
                   c2.setY(this->height()-1);
                   c2.setSmer(0);
               }
               if(c2.getPozice().y() > this->height()-1){
                   c2.setY(30);
                   c2.setSmer(2);
               }

       }
    }

    //nastaveni bonusu cerva 1, pokud narazi cerv na bonus
   if((c1.getPozice().x() >= bonus->x()) && (c1.getPozice().x() <= (bonus->x()+bonus->width())) && (c1.getPozice().y() >= bonus->y()) && (c1.getPozice().y() <= bonus->y() + bonus->height())){
       c1.timerBonusyDoba = new QTimer; //aktivuj jednorazovy timer s odpocetem trvani bonusu
       c1.timerBonusyDoba->setSingleShot(true);
       connect(c1.timerBonusyDoba, SIGNAL(timeout()), this, SLOT(timerBDC1()));
       c1.timerBonusyDoba->start(1000*defDobaTrvaniBon);

       if(bonus->statusTip() == "1"){ //0.5 rychlost
           timerPohyb->setInterval(2*(100-rychlost)); //nastav obema 0.5 pohyb
           if(c2.getNasRych() == 1){ //a souperi nastav dvojnasobny nasobic rychlosti tzn normalni pohyb
               c2.setNasRych(2);
           }
           else if(c2.getNasRych() < 1){
               c2.setNasRych(1);
           }
           bonus->move(-50,-50); //dej bonus pryc aby ho neslo sebrat
           bonus->clear();
       }
       else if(bonus->statusTip() == "2"){//0.5 cara
           if(c1.getTloustka() >= 0.5*defTloustka){
               c1.setTloustka(c1.getTloustka()*0.5);
               c1.setNasRych(2); //musim se pohybovat 2x rychleji protoze mam polovicni tloustku
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "3"){//nekreslim caru
           if(c1.getKresli())
               c1.setKresli(false);
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "4"){//muzu pres okraj
           if(!c1.getPruchozi())
               c1.setPruchozi(true);
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "5"){//2x rychlost
           if(c2.getNasRych() == 1){
               c2.setNasRych(2);
           }
           else if(c2.getNasRych() < 1){
               c2.setNasRych(1);
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "6"){//2x cara
           if(c2.getTloustka() < 2*defTloustka){
               c2.setTloustka(c2.getTloustka()*2);
               timerPohyb->setInterval(2*(100-rychlost)); //nastav obema polovicni rychlost a sam sebe zrychli aby se oba pohybovali stejne
               c1.setNasRych(2);
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "7"){//smaz caru obema
           image.fill(Qt::white);
           bonus->move(-50,-50);
           bonus->clear();          
       }

   }

   if((c2.getPozice().x() >= bonus->x()) && (c2.getPozice().x() <= (bonus->x()+bonus->width())) && (c2.getPozice().y() >= bonus->y()) && (c2.getPozice().y() <=bonus->y() + bonus->height())){
       c2.timerBonusyDoba = new QTimer;
       c2.timerBonusyDoba->setSingleShot(true);
       connect(c2.timerBonusyDoba, SIGNAL(timeout()), this, SLOT(timerBDC2()));
       c2.timerBonusyDoba->start(1000*defDobaTrvaniBon);


        if(bonus->statusTip() == "1"){ //0.5 rychlost
           timerPohyb->setInterval(2*(100-rychlost));
           if(c1.getNasRych() == 1){
               c1.setNasRych(2);
           }
           else if(c1.getNasRych() < 1){
               c1.setNasRych(1);
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "2"){//0.5 cara
           if(c2.getTloustka() >= defTloustka*0.5){
               c2.setTloustka(c2.getTloustka()*0.5);
               c2.setNasRych(2);
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "3"){//nekreslim caru
           if(c2.getKresli())
               c2.setKresli(false);
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "4"){//muzu pres okraj
         if(!c2.getPruchozi())
               c2.setPruchozi(true);
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "5"){//2x rychlost
           if(c1.getNasRych() == 1){
               c1.setNasRych(2);
           }
           else if(c1.getNasRych() < 1){
               c1.setNasRych(1);
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "6"){//2x cara
           if(c1.getTloustka() < 2*defTloustka){
               c1.setTloustka(c1.getTloustka()*2);
               timerPohyb->setInterval(2*(100-rychlost));
               c2.setNasRych(2);
           }
           bonus->move(-50,-50);
           bonus->clear();
       }
       else if(bonus->statusTip() == "7"){//smaz caru obema
           image.fill(Qt::white);
           bonus->move(-50,-50);
           bonus->clear();
       }

   }

    penC1.setWidth(c1.getTloustka());
    penC1.setColor(Qt::yellow); //nakresli zlutou hlavu cerva
    painter.setPen(penC1);
    painter.drawPoint(c1.getPozice());

    penC2.setWidth(c2.getTloustka());
    penC2.setColor(Qt::yellow);
    painter.setPen(penC2);
    painter.drawPoint(c2.getPozice());

    update();
}

void MainWindow::on_actionKonec_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionNova_hra_triggered()
{
    if(timerPohyb->isActive())
        timerPohyb->stop();
    if(timerBonusyCet->isActive())
        timerBonusyCet->stop();
    image.fill(Qt::white);
    update();

    //zobraz uvodni obrazovku
    ui->hrac1Lb->setVisible(true);
    ui->hrac1Lb->setEnabled(true);
    ui->hrac2Lb->setVisible(true);
    ui->hrac2Lb->setEnabled(true);
    ui->hrac1Le->setVisible(true);
    ui->hrac1Le->setEnabled(true);
    ui->hrac2Le->setVisible(true);
    ui->hrac2Le->setEnabled(true);
    ui->novaHraBt->setVisible(true);
    ui->novaHraBt->setEnabled(true);
    hrac1Body->setVisible(false);
    hrac2Body->setVisible(false);

    //nastav body na 0 atd.
    hrac1Body->setText("Hráč1: 0");
    body[1] = 0;
    hrac2Body->setText("Hráč2: 0");
    body[2] = 0;
    konecHry = false;
    konecKola = false;
    srazkaC1 = false;
    srazkaC2 = false;
    timerBDC1();
    timerBDC2();

}

void MainWindow::on_actionNastaveni_Hry_triggered()
{ //zobraz dialog  nastaveni
    if(timerPohyb->isActive())
        timerPohyb->stop();
    Nastaveni nast;
    nast.setModal(true);

        //nacti do dialogu soucasne hodnoty
    nast.setVitezne(vitezneBody);
    nast.setRychlost(rychlost);
    nast.setBarvaC1(barvaC1);
    nast.setBarvaC2(barvaC2);
    nast.setTloustka(defTloustka);
    nast.setMezery(mezery);
    nast.setMezeryCet(mezeryCet);
    nast.setBonusy(bonusy);
    nast.setBonusyCet(bonusyCet);
    nast.setBonusyDoba(defDobaTrvaniBon);
    nast.exec();

    //pokud bylo nastaveni prijato tak nastav hru
    if(nast.prijato){
        defTloustka = nast.tloustkaNast;
        vitezneBody = nast.vitezneNast;
        barvaC1 = nast.barvaC1;
        barvaC2 = nast.barvaC2;
        rychlost = nast.rychlostNast;
        mezery = nast.mezeryNast;
        mezeryCet = nast.mezeryNastCet;
        bonusy = nast.bonusyNast;
        bonusyCet = nast.bonusyNastCet;
        defDobaTrvaniBon = nast.bonusyDoba;
    }
}

void MainWindow::on_novaHraBt_clicked()
{//nastaveni jmen hracu
    hrac1Jmeno = ui->hrac1Le->text();
    hrac2Jmeno = ui->hrac2Le->text();

    hrac1Body->setText(hrac1Jmeno + ": 0");
    hrac2Body->setText(hrac2Jmeno + ": 0");
    //zrus uvodni obrazovku
    ui->hrac1Lb->setVisible(false);
    ui->hrac1Lb->setEnabled(false);
    ui->hrac2Lb->setVisible(false);
    ui->hrac2Lb->setEnabled(false);
    ui->hrac1Le->setVisible(false);
    ui->hrac1Le->setEnabled(false);
    ui->hrac2Le->setVisible(false);
    ui->hrac2Le->setEnabled(false);
    ui->novaHraBt->setVisible(false);
    ui->novaHraBt->setEnabled(false);
    hrac1Body->setVisible(true);
    hrac2Body->setVisible(true);

    MainWindow::hra(0);
}

void MainWindow::on_actionHra_triggered()
{
   napovedaHra napov;
   napov.setModal(true);
   napov.exec();
}

void MainWindow::on_actionO_autorovi_triggered()
{
    oAutorovi autor;
    autor.setModal(true);
    autor.exec();

}
