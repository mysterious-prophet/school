#include<iostream>

using namespace std;

class solution {
    int n;
    int numOfSols = 0;
    bool **chessBoard;
public:
    solution(int _n);
    ~solution();
    void display();
private:
    bool possible(int r, int s);
    bool solve(int j);
};


solution::solution(int _n)
    :n(_n)
{ //construct matrix
    if (n <= 0) {
        cout << "Cannot solve for value lower than or equal to 0\n";
        system("pause");
        exit(EXIT_FAILURE);
    }

    chessBoard = new bool*[n];
    for (int i = 0; i < n; i++) {
        chessBoard[i] = new bool[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            chessBoard[i][j] = false;
        }
    }

    cout << "All solutions of " << n <<" Queens problem: \n";
    solve(0);
}

solution::~solution() {//throws an exception? why?
    for (int i = 0; i < n; ++i) {
        delete[] chessBoard[i];
    }
    delete[] chessBoard;
}

void solution::display() { //display elements
    cout << "Solution no: " << numOfSols << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << chessBoard[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



bool solution::possible(int row, int column) {//check whether it is possible to put a queen on the spot
    for (int i = 0; i < column; i++) {
        if (chessBoard[row][i]) {
            return false;
        }
    }
    for (int i = row -1, j = column -1; i >= 0 && j >= 0; i--, j--) {
        if (chessBoard[i][j]) {
            return false;
        }
    }
    for (int i = row + 1, j = column - 1; i <n && j >= 0; i++, j--) {
        if (chessBoard[i][j]) {
            return false;
        }
    }
    return true;

}


bool solution::solve(int j) {
    if (j >= n) { //display all solutions
        numOfSols++;
        display();
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (possible(i, j)) {
            chessBoard[i][j] = true;
            if (solve(j + 1)) {
                return true;
            }
            chessBoard[i][j] = false; //backtracking
        }
    }
    if(j==0 && numOfSols == 0)
        cout << "Solution does not exist! \n";
    return false;
}

int main() {
    int n = 0;
    cout << "Solving the nQueens problem, please insert the size of the chessboard (n): \n";
    cin >> n;
    solution s(n);
    system("pause");
    return 0;
}
