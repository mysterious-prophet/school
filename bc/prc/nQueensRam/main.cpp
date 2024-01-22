#include<iostream>

using namespace std;

class damy {
    int n;
    int pocetReseni = 0;
    bool **sachovnice;
public:
    damy(int _n);
    ~damy();
    bool umisteniDamy(int col);
    bool kontrola();
private:
    void vypis();
    bool jeMozny(int row, int col);
};

damy::damy(int _n) //konstruktor
    :n(_n)
{   if(n <= 0){
        cout << "Doslo k chybe, reseni neexistuje" << endl;
    }
    sachovnice = new bool*[n];
    for(int i = 0; i < n; i++){
        sachovnice[i] = new bool[n];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            sachovnice[i][j] = false; //nastaveni vsech elementu na nulu
        }
    }
    kontrola();
}

damy::~damy(){ //destruktor
    for(int i = 0; i < n; ++i){
        delete[] sachovnice[i];
   }
    delete[] sachovnice;
}

void damy::vypis(){
  cout << "Reseni cislo: " << pocetReseni << endl;
  for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++){
         cout << sachovnice[i][j] << " "; //vypis vsech elementu
      }
      cout << endl;
   }
   cout << endl;
}

bool damy::jeMozny(int row, int col){
   for (int i = 0; i < col; i++){ //zkontroluj jestli dama je v levem sloupce
      if (sachovnice[row][i]){
         return false;
      }
   }
   for (int i = row, j = col; i >= 0 && j >= 0; i--, j--){ //zkontroluj jestli dama je v leve horni diagonale
      if (sachovnice[i][j]){
         return false;
      }
   }
   for (int i = row, j = col; j >= 0 && i < n; i++, j--){ //zkontroluj jestli dama je v leve dolni diagonale
      if (sachovnice[i][j]){
         return false;
      }
   }
   return true; //v jinem pripade dama muze byt umistnena
}

bool damy::umisteniDamy(int col){
    if (col == n){ //kdyz damy jsou umisteny a mame reseni
        pocetReseni++;
        vypis();
        return true;
    }
    bool res = false;
    for (int i = 0; i < n; i++){ //zkontroluj, jestli existje moznost umisteni damy
        if (jeMozny(i, col)){
            sachovnice[i][col] = true; //kdyz je to mozny, umisti damu na misto (i, col)
            res = umisteniDamy(col + 1) || res; //kdyz umisteni damy nedava reseni
            sachovnice[i][col] = false;
        }
    }
    return res; //kdyz neexistuje zadny zpusob umisteni
}

bool damy::kontrola(){
   if (umisteniDamy(0) == false ) { //zacneme od 0 sloupce
      cout << "Reseni neexistuje" << endl;
      return false;
   }
   return true;
}

int main() {
   int n = 0;
   cout << "Zadejte velikost sachovnice: ";
   cin >> n;
   damy d(n); //deklarace objektu damy
   return 0;
}
