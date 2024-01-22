#include <iostream>
#include <fstream>

using namespace std;

class Image {
public:
    virtual void testRoad();
    virtual void loadFromFile();
    string *canvas;
    void draw (unsigned int w, unsigned int h);
    void floodFill(string *canvas, unsigned int x, unsigned int y, char c, char inC, unsigned int w, unsigned int h);
};

//proc se tohle jmenuje testRoad? cesta je Path
//proc to neni soucasti funkce loadFromFile? to by davalo vic smysl

void Image::testRoad(){
    fstream fs;
    fs.open("test.pbm", ios_base::in); //da se to udelat i ifstream protoze tady je to jen input ale ok
    string s;
    if(!fs){
        cerr << "Chyba" << endl;
        return;
    }
    while(fs >> s){  //tohle vypisuje, ale dal bych celou tuhle funkci do loadFromFile
        cout << s << endl; //a vypsal tu bitmapu bez tech prvnich dvou radku
    }
    fs.close();
}


/*kdyz si vypises tu bitmapu po nacteni, coz se dela nahore v testRoad,
 * tak vidis ze tam ocividne je prvni radek a pak druhy radek, ktery udava rozmery toho canvasu
 * a az pak zacne ta skutecna bitmapa
 * takze dava smysl prvni radek ignorovat a druhy si nahrat jako promenne w a h
 * a podle toho pak vytvorit rovnout ten canvas az s temi udaji te skutecne bitmapy
*/
void Image::loadFromFile(){
    {
            string line; //ok
            int Numline = -1;
            ifstream in("test.pbm");
            if (in.is_open())
            {
                while (getline(in, line))
                {
                    Numline++;
                    if (Numline >= 1)
                    {
                        int j = 0;
                        string temp = "";
                        while (line[j] != ' ')
                        {
                            temp = temp + line[j];
                            j++;
                        }
                        canvas[j] = temp; //nejaky divny, pouzivat tady ten stejnej index j
                    }
                }
            }
            in.close();
        }
}

void Image::draw(unsigned int w, unsigned int h){ //proc ne print? ale draw ok
    string *canvas; //kdyz si tu udelas novy canvas tak se ti nic nevypise
    for(unsigned int i = 0; i < h; i++){
        for(unsigned int j = 0; j < w; j++){
            cout << canvas[i][j];
        }
    }
}


void Image::floodFill(string *canvas, unsigned int x, unsigned int y, char c, char inC, unsigned int w, unsigned int h){
   /* for(unsigned int i = 0; i < h; i++){
        for(unsigned int j = 0; j < w; j++){
            canvas[i][j] = bit; //bit neni nic a flood fill od niceho nezacina
        floodFill(i + 1, j, bit);
        floodFill(i - 1, j, bit);
        floodFill(i, j + 1, bit);
        floodFill(i, j - 1, bit);
        }
    }*/

    /*musis mit pocatecni body x, y od kterych zacina ten flood fill, to jsi tu vubec nemela
     * pak musis mit nejaky int nebo char c, ktery udava, na co chces zmenit hodnotu toho pole
     * to je ten tvuj bit, ktery jsi ale nikde neurcovala
     * to inC, co tu mam, je pokud zacnes pouzivat floodFill uz od nejakeho pole,
     * ktere ma odlisnou barvu napr tady ty 1 vs 0
     * to rekurentni volani floodfill bylo spravne

    */
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

    floodFill(canvas, x+1, y, c, inC, w, h); //rekurzivne men barvy okolnich bunek
    floodFill(canvas, x, y+1, c, inC, w, h);
    floodFill(canvas, x-1, y, c, inC, w, h);
    floodFill(canvas, x, y-1, c, inC, w, h);
}

int main()
{
    unsigned int w, h; //kde deklarujes velikost w a h? to je prave zadany v tom souboru
    Image i;
    i.testRoad();
    i.loadFromFile();
    //i.draw(w, h); //tohle zatim nic nedela
    return 0;
}
