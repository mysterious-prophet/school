#include <iostream>
#include <vector>
#include<algorithm>
#include<string>
#include<fstream>
#include <stdio.h>

using namespace std;
vector<string> split_string(string);

int **correctMatrix(int x, int y, int size, int **matrix) { //if a plus was made, corrects the matrix so that two pluses do not take up same cell

    for (int i = 0; i <= (size - 1) / 2; i++) {
        matrix[x][y - i] = 0;
        matrix[x][y + i] = 0;
        matrix[x + i][y] = 0;
        matrix[x - i][y] = 0;
    }
    return matrix;
}

bool createPlus(int size, int n, int m, int x, int y, int **matrix) {		//computes wheter it is possible to make plus of certain size at the current location



    for (int i = 1; i <= (size - 1) / 2; i++) {
        if (x + i >= 0 && x - i >= 0 && x + i < n) {
            if (matrix[x + i][y] != 1) return 0;
            if (matrix[x - i][y] != 1) return 0;
        }
        else return 0;
        if (y + i >= 0 && y - i >= 0 && y + i < m) {
            if (matrix[x][y + i] != 1) return 0;
            if (matrix[x][y - i] != 1) return 0;
        }

        else return 0;
    }


    return true;

}

int maxSizePlus(int m, int n, int **matrix, int x, int y) {			//returns size of max plus possible to create at current location
    if (matrix[x][y] != 1) return 0;
    int size= min(m, n);
    if (size % 2 == 0) size -= 1;  //will be called for odd numbers decreasingly
    while (!createPlus(size, n, m, x, y, matrix)) {
        size-=2;
    }
    return size;

}

int** createMatrix(int m, int n, vector<string> grid) { //transforms string vector into a matrix with 0 describing bad cell and 1 descrbing good cell, for easier manipulation
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];

    }
    for (int i = 0; i < n; i++) {
        string temp = grid[i];
        for (int j = 0; j < m; j++) {
            if (temp[j] == 'G') {
                matrix[i][j] = 1;
            }
            else matrix[i][j] = 0;
        }
    }

    return matrix;
}

void displayMatrix(int m, int n, int **matrix) {		//displays the current matrix

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;

    }
    cout << endl << endl;
}

int **createMatrixOfSizes(int m, int n, int **matrix) {		//creates a matrix of numbers that represent biggest plus possible to create with center at current index
    int **newMatrix = new int *[n];
    for (int i = 0; i < n; i++) {
        newMatrix[i] = new int[m];

    }	for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            newMatrix[i][j] = maxSizePlus(m, n, matrix, i,j);

        }
    }
    //displayMatrix(n, m, newMatrix);
    return newMatrix;
}

int makeTwoPluses(int m, int n, int **matrix, int **matrixOfSizes, vector<string> grid) {
    int P1 = 0; int P2 = 0; int max = 0; int tempSize;

    for (int i = 0; i < n; i++) {		//one column
        for (int j = 0; j < m; j++) {		//one line

            for (int k = i; k < n; k++) {		//goes over columns
                for (int l = 0; l < m; l++) { //goes over lines

                    for (int s = matrixOfSizes[i][j]; s > 0; s -= 2) {						//goes over the possible sizes of first plus

                        if (matrix[k][l] != 0) {		//IF good cell
                            tempSize = matrixOfSizes[k][l];		//saves current biggest size
                            //createPlus(s, n, m, i, j, matrix);		//
                            matrix = correctMatrix(i, j, s, matrix);	//creates the first plus and transforms our matrix
                            while (!createPlus(tempSize, n, m, k, l, matrix)) {	//while both pluses are not created
                                 tempSize-= 2;	//tries to make secoond plus smaller
                                // if (tempSize < 1) break;		//if not possible to create second plus --->not needed as it never happens thanks to while condidion
                            //no need to rewrite the matrix again with the seconds plus, because it is surely possible to create, otherwise createPlus returns zero
                            }
                            P1 = s;
                            P2 = tempSize;
                        if((2 * P1 - 1)*(2 * P2 - 1)>max)	{		//saves the bigest product
                        //	displayMatrix(n, m, matrix);
                            max = (2 * P1 - 1)*(2 * P2 - 1);
                            }
                        matrix = createMatrix(m, n, grid);	//takes back changes
                        }

                    }

                }
            }
        }
    }
    return max;

}

int twoPluses(int m, int n, vector<string> grid) {
    int **matrix = createMatrix(m, n, grid);		//makes a matri for easier manipulation
    int **newMatrix=createMatrixOfSizes(m, n, matrix);		//makes a matrix of numbers of the biggest plus possible to create at certain cell
    displayMatrix(n, m, newMatrix);
    return makeTwoPluses(m, n, matrix, newMatrix, grid);		//finds the biggest product

}

int main()
{
    cout << "Zadejte pocet radku a pocet sloupcu mrizky, nasledne vlozte samotnou mrizku."<<endl;
    cout << "Pismeno 'B' oznacuje spatnou bunku, pismeno 'G' dobrou bunku. " << endl;
    cout<<"Vzorovy  vstup : " << endl;
    cout << "6 6" << endl;
    cout << "BGBBGB" << endl;
    cout << "GGGGGG" << endl;
    cout << "BGBBGB" << endl;
    cout << "GGGGGG" << endl;
    cout << "BGBBGB" << endl;
    cout << "BGBBGB" << endl << endl;
    cout << "Zadejte sve zadani:" << endl;

    ofstream fout("output.txt", std::ofstream::out);

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

    int result = twoPluses(m,n,grid);

    fout << result << "\n";

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
