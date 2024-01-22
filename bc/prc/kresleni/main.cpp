#include <iostream>

using namespace std;
string **canvas; //globalni promena platno matice stringu

void display( unsigned int w, unsigned int h){ //vypsani aktualniho stavu platna
    for(unsigned int i = 0; i<h; i++){
        for(unsigned int j = 0; j<w; j++){
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

bool possible(unsigned int x1, unsigned int y1,unsigned int x2,unsigned int y2, unsigned int w, unsigned int h){//zjisti, zda je mozne nakreslit na platno dany objekt
    if(x1<=0 || x1>=w || x2 >= w || x2<= 0 || y1<=0 || y1 >= (h-1) || y2 >= (h-1) || y2 <= 0){
        return false;
    }
    return true;
}

void drawC(unsigned int w, unsigned int h){ //vyrobi platno dane velikosti
    canvas = new string*[h]; //dvojrozmerne pole velikosti w h
    for(unsigned int i = 0; i<h; i++){
        canvas[i] = new string[w];
    }

    for(unsigned int i = 0; i<h; i++){//hranice a prazdna vypln platna
        for(unsigned int j = 0; j<w; j++){
            if(i == 0 || i == (h-1)){
                canvas[i][j] = "-";
            }
            else if (j == 0 || j== (w-1)){
                canvas[i][j] = "|";
            }
            else{
                canvas[i][j] = " ";
            }
        }
    }
}

void drawL(unsigned int x1, unsigned int y1,unsigned int x2,unsigned int y2){//vykresli caru
    if(y1 == y2){ //horizontalni cara
        if(x2<=x1){ //pokud kreslime zprava doleva tak prohod
            unsigned int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        for(unsigned int i=x1; i <=x2; i++){ //kresleni zleva doprava
            canvas[y1][i] = "x";
        }
    }
    else if(x1 == x2){ //vertikalni cara
        if(y2<=y1){ //pokud kreslime zdola nahoru tak prohod
            unsigned int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for(unsigned int i = y1; i<=y2; i++){ //kresleni zeshora dolu
            canvas[i][x1] = "x";
        }
    }
    else{ //diagonalni cary nebyly soucasti zadani
        cout << "Diagonalni cary neumim.\n";
    }
}

void drawR(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2){ //kresleni obrazcu je pouze kresleni 4 car
    drawL(x1, y1, x2, y1);
    drawL(x1, y1, x1, y2);
    drawL(x2, y1, x2, y2);
    drawL(x1, y2, x2, y2);
}

void fillB(unsigned int x,unsigned int y, string c, string inC,  unsigned int w, unsigned int h){ //rekurzivne zmen barvu bunek
    if(x<=0 || x >= (w-1) || y <= 0 || y>= (h-1)){ //pokud mimo platno
        return;
    }
    if(canvas[y][x] != inC){ // pokud je barva odlisna od inicialni barvy, napr umoznuje pouzit fill na cary a obrazce
        return;
    }
    if(canvas[y][x] == c){ //pokud uz byla bunka zmenena
        return;
    }

    canvas[y][x] = c; //zmen barvu

    fillB(x+1, y, c, inC, w, h); //rekurzivne men barvy okolnich bunek
    fillB(x, y+1, c, inC, w, h);
    fillB(x-1, y, c, inC, w, h);
    fillB(x, y-1, c, inC, w, h);
}


int main(){
    char prikaz; //C L R B Q
    unsigned int w, h, x1, y1, x2, y2, x, y; //rozmery platna, objektu, bucket fill
    string c; //barva fillu
    bool platno = false; //je umisteno platno?

    do{
        try{
            cout << "zadany prikaz: \n";
            cin >> prikaz;
            if(prikaz == 'C'){
                cin >> w >> h;
                w += 2; //vnitrek platna ma mit velikosti w, h proto obe plus 2
                h +=2;
                drawC(w, h);
                display(w, h);
                platno = true; //bylo umisteno platno
            }
            else if(prikaz == 'L'){
                if(platno){ //mozne pouze pokud existuje platno
                    cin >> x1 >> y1 >> x2 >> y2;
                    if(possible(x1, y1, x2, y2, w, h)){ //vejde-li se objekt na platno
                        drawL(x1, y1, x2, y2);
                        display(w, h);
                    }
                    else{
                        throw "Takova cara se nevejde na platno. \n";
                    }
                }
                else{
                    throw "Neni kam kreslit, nebylo zadano platno.\n";
                }
            }
            else if(prikaz == 'R'){
                if(platno){
                    cin >> x1 >> y1 >> x2 >> y2;
                    if(possible(x1, y1, x2, y2, w, h)){
                        drawR(x1, y1, x2, y2);
                        display(w, h);
                    }
                    else{
                        throw "Takovy obrazec se nevejde na platno. \n";
                    }
                }
                else{
                    throw "Neni kam kreslit, nebylo zadano platno.\n";
                }
            }
            else if(prikaz == 'B'){
                if(platno){
                    cin >> x >> y >> c;
                    if(possible(x, y, 1, 1, w, h)){
                        string inC = canvas[y][x];
                        fillB(x, y, c, inC, w, h);
                        display(w, h);
                    }
                    else{
                        throw "Bod pro pocatek vyplne se nachazi mimo platno.\n";
                    }
                }
                else{
                    throw "Neni kam kreslit, nebylo zadano platno.\n";
                }

            }
        }
        catch(const char *e){
            cerr << "Nastala chyba: " << e << endl;
        }
    }while(prikaz != 'Q');

    return 0;
}
