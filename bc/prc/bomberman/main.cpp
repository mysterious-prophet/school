#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

void fill(vector<string> &grid){ //pomocna fce naplni bludiste bombami a vytvori tak filledGrid
    for (string & i: grid)
    {
        for (char & j: i)
        {
            j = 'O';
        }
    }
}

void detonate(vector<string> &grid, vector<string> &previousGrid)//pomocna fce detonuje bomby a vytvari tak secondaryGrid
{
    unsigned int rows = grid.size();
    unsigned int cols = grid[0].size();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if (previousGrid[i][j] == 'O'){ //pokud v predchozim stavu na teto pozici bomba
                grid[i][j] = '.'; //na teto pozici prazdno po vybuchu

                if (i + 1 < rows){ //a na pozicich i+-1, j+-1 dle zadani take prazdno po vybuchu
                    grid[i + 1][j] = '.';
                }
                if (j + 1 < cols){
                    grid[i][j + 1] = '.';
                }
                if (i - 1 >= 0){
                    grid[i - 1][j] = '.';
                }              
                if (j - 1 >= 0){
                    grid[i][j - 1] = '.';
                }
            }
        }
    }
}

vector<string> bomberMan(int n, vector<string> grid)//bludiste ma pouze 4 stavy:
{
    vector<string> initialGrid = grid; //inicialni stav
    vector<string> secondaryGrid; //inverze k inicialnimu stavu, sekundarni vzorec
    vector<string> filledGrid = grid; //bludiste plne bomb
    vector<string> pseudoInitialGrid = grid; //pseudoinicialni stav, chybel v predchozim algoritmu


    fill(pseudoInitialGrid);

    fill(filledGrid); //vytvoreni plneho stavu bludiste

    detonate(pseudoInitialGrid, initialGrid); //vytvoreni sekundarniho vzorce
    secondaryGrid = pseudoInitialGrid;

    //oprava:
    fill(pseudoInitialGrid); //vytvoreni pseudoinicialniho stavu v n % 4 = 1, toto chybelo v predchozim algoritmu
    detonate(pseudoInitialGrid, secondaryGrid);

    int timeStamp = n % 4; //stridaji se 4 unikatni stavy - inicialni stav, zcela naplneny stav, sekundarni stav, pseudoinicialni stav

    if (n == 1){ //inicialni stav pouze v n = 1
        return initialGrid;
    }
    else if (timeStamp == 3){ //sekundarni stav se opakuje kazde dve sekundy
        return secondaryGrid;
    }
    else if( timeStamp == 2 || timeStamp == 0){ //bludiste je zcela naplneno kazde dve sekundy
        return filledGrid;
    }
    else {
        return pseudoInitialGrid;
    }
}


int main(){
    ofstream fout("output.txt", std::ofstream::out);

    string rcn_temp;
    getline(cin, rcn_temp);

    vector<string> rcn = split_string(rcn_temp);

    int r = stoi(rcn[0]);

    int c = stoi(rcn[1]);

    int n = stoi(rcn[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }


    vector<string> result = bomberMan(n, grid);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
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
