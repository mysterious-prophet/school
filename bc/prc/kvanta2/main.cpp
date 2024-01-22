#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Doplnte funkciu twoPluses
int twoPluses(vector<string> grid) {
    int ans = 0; //maximalni velikost plusu, vysledek
    unsigned int h = grid.size(); //velikosti matic pri vypoctu
    unsigned int w = grid[0].size();

    int **poss = new int*[h]; //inicializuje matici G a B bunek jako 1 a 0
    int **sizes = new int*[h]; //a zaroven inicializuje matici maximalni velikosti plusu se stredem v danem poli
    for(int unsigned i = 0; i<h; i++){
        poss[i] = new int[w];
        sizes[i] = new int[w];
    }

    for(unsigned int i = 0; i<h; i++){ //naplni matice 1 a 0, sizes vyhodne naplnit take jelikoz na kazdem G poli jde vytvorit alespon plus velikosti 1
        for(unsigned int j = 0; j<w; j++){ // a zaroven tim mame pripravene obe matice
            if(grid[i][j] == 'G'){
                poss[i][j] = 1;
                sizes[i][j] = 1;

            }
            else{
                poss[i][j] = 0;
                sizes[i][j] = 0;
            }
        }
    }

    unsigned int size = min(w, h); //maximalni velikost jednoho ramena plusu
    for(int i = 0; i<h; i++){ //zjisti maximalni velikosti plusu z daneho pole
        for(int j = 0; j<w; j++){
            if(poss[i][j] == 0){ //pokud B pole, pak nelze vytvorit plus a max velikost je 0
                sizes[i][j] = 0;
            }
            else{
                for(int k = 1; k <= (size-1)/2; k++){ //pro dane pole do (pulky velikosti -1) jelikoz nelze vytvorit vetsi rameno plusu
                    if(i+k < h && i-k>= 0 && j+k <  w && j-k >= 0){ //pokud nejsme na okrajich
                        if(poss[i+k][j] == 0 || poss[i-k][j] == 0 || poss[i][j+k] == 0 || poss[i][j-k] == 0){ //a pokud neni na relevantnich okolnich policcich 0
                            break; //break nutny jinak by bylo, pokud by na +xtych policcich byla 0 a na +ytych policcich byla 1, nespravne vypsano cislo>0
                        }
                        else{ //jedine pak zmen velikost plusu
                            sizes[i][j] = 4*k+1;
                        }
                    }
                }
            }
        }
    }


    //hledame dva plusy a proto 4 for cykly i, j, k, l, a dale kazde velikosti techto plusu tedy cykly n, q
    //cyklus m provede transformaci matice po zvoleni prvniho plusu
    //cykly r, s provedou transformaci matice zpet na puvodni stav

    unsigned int temp = 0, tempSizeP1 = 0, tempSizeP2 = 0; //pomocna promena a pomocne docasne velikosti plusu

    for(int i = 0; i<h; i++){ //radky P1
        for(int j = 0; j<w; j++){ //sloupce P1

            if(sizes[i][j]!=0){ //pokud maximalni velikost plusu z tohoto pole neni 0
                tempSizeP1 = sizes[i][j]; //nastav ji jako hodnotu prvniho plusu
                for(int n = tempSizeP1; n>0; n -= 4){//pro kazdou velikost zvoleneho P1
                    for(int m = 0; m <= (n-1)/4; m++){ //zmen matici moznosti, tak aby se plusy neprekryvaly
                            poss[i+m][j] = 0;
                            poss[i-m][j] = 0;
                            poss[i][j+m] = 0;
                            poss[i][j-m] = 0;
                    }

                   // display(poss, w, h);


                    for(int k = 0; k<h; k++){ //radky P2
                        for(int l = 0; l<w; l++){ //sloupce P2
                            if(poss[k][l]!=0 && k != i && l != j){ //pokud neni druhy plus 0
                                tempSizeP2 = sizes[k][l];

                                for(int q = 0; q<=(tempSizeP2-1)/4; q++){ //najdi vsechny mozne velikosti zvoleneho P2 a porovnej obsahy, zacinam od nejmensi mozne velikosti P2
                                    if(k+q<h && k-q>= 0 && l+q<w && l-q>=0){ //pokud nejsme na okrajich
                                        if(poss[k+q][l] == 0 || poss[k-q][l] == 0 || poss[k][l+q] == 0 || poss[k][l-q] == 0){ //plus dane velikosti nelze vytvorit
                                            break; //zrus zkoumani tohoto plusu
                                        }
                                        else{ //pokud lze vytvorit P2
                                            temp = n*((4*q)+1); //spocti obsah teto konkretni kombinace plusu
                                            if(temp>ans){ //pokud je maximalni nastav ho jako odpoved
                                                ans = temp;
                                            }
                                        }
                                    }

                                 }
                            }
                        }
                    }

                    for(int r = 0; r<h; r++){ //zmena matice moznosti zpet na puvodni
                        for(int s = 0; s<w; s++){
                            if(grid[r][s] == 'G'){
                                poss[r][s] =1;

                            }
                            else{
                                poss[r][s] = 0;
                            }
                        }
                    }

                }
            }

        }
    }

    return ans;
}

int main()
{
    ofstream fout("output.txt",std::ofstream::out);

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
