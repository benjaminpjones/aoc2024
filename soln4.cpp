#include <iostream>

using namespace std;
using Grid = vector<vector<char>>;

Grid readInput() {
    string line;
    Grid ret;
    while (getline(cin, line)) {
        if (line == "") continue;
        ret.emplace_back();
        for (auto c : line) {
            ret.back().push_back(c);
        }
    }
    return ret;
}

int countXmas(const vector<char>& v) {
    int sum = 0;
    for (int i = 0; i <= static_cast<int>(v.size()) - 4; i++) {
        if (v[i] == 'X' && v[i+1] == 'M' && v[i+2] == 'A' && v[i+3] == 'S')
            sum++;
        if (v[i] == 'S' && v[i+1] == 'A' && v[i+2] == 'M' && v[i+3] == 'X')
            sum++;
    }
    return sum;
}


int countHorizontals(const Grid& grid) {
    int sum = 0;
    for (auto row : grid) {
        sum += countXmas(row);
    }
    return sum;
}

// This will make verticals horizontals and vice versa
Grid flipDiagonal(const Grid& grid) {
    Grid ret(grid[0].size());
    for (int i = 0; i < grid.size(); ++i) {
        auto row = grid[i]; 
        for (int j = 0; j < row.size(); ++j) {
            ret[j].push_back(row[j]);
        }
    }
    return ret;
}

void printRow(vector<char> v) {
    for (auto c : v) {
        cout << c;
    }
    cout << endl;
}
void printGrid(Grid g) {
    for (auto r : g) {
        printRow(r);
    }
}

Grid skew45(const Grid& grid) {
    Grid ret(grid.size() + grid[0].size() - 1);
    for (int i = 0; i < grid.size(); ++i) {
        auto row = grid[i];
        for (int j = 0; j < row.size(); ++j) {
            ret[i + j].push_back(row[j]);
        }
    }
    return ret;
}

Grid skewNeg45(const Grid& grid) {
    Grid ret(grid.size() + grid[0].size() - 1);
    for (int i = 0; i < grid.size(); ++i) {
        auto row = grid[i];
        for (int j = 0; j < row.size(); ++j) {
            ret[row.size() + i - j - 1].push_back(row[j]);
        }
    }
    return ret;
}

int main() {
    auto data = readInput();

    int sum = 0;

    sum += countHorizontals(data);
    sum += countHorizontals(flipDiagonal(data));
    sum += countHorizontals(skew45(data));
    sum += countHorizontals(skewNeg45(data));

    cout << sum << endl;
}
