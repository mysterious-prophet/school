#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Doplnte funkciu bomberman
void fillGridWithBombs(vector<string> &grid)
{
    size_t r{ grid.size() };
    size_t c{ grid[0].size() };

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            grid[i][j] = 'O';
}

void detonate(vector<string> &grid, vector<string> &previous_grid)
{
    size_t r{ grid.size() };
    size_t c{ grid[0].size() };

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
        {
            if (previous_grid[i][j] == 'O')
            {
                grid[i][j] = '.';

                if (i + 1 < r)
                    grid[i + 1][j] = '.';

                if (i - 1 >= 0)
                    grid[i - 1][j] = '.';

                if (j + 1 < c)
                    grid[i][j + 1] = '.';

                if (j - 1 >= 0)
                    grid[i][j - 1] = '.';
            }
        }
}

vector<string> bomberMan(int n, vector<string> grid)
{
    vector<string> initial_grid{ grid }, full_of_bombs{ grid }, pattern_a;

    fillGridWithBombs(grid);
    fillGridWithBombs(full_of_bombs);

    detonate(grid, initial_grid);

    pattern_a = grid;

    fillGridWithBombs(grid);
    detonate(grid, pattern_a);

    int k{ n % 4 };

    if (n == 1)
        return initial_grid;

    if (k == 0 || k == 2)
        return full_of_bombs;
    else if (k == 3)
        return pattern_a;

    return grid;
}
/*
vector<string> detonate(int r, int c, vector<string> grid) {

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {

            cout << grid[i][j];
        }
        cout << endl;
    }
    return grid;
}
*/

int main()
{


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
