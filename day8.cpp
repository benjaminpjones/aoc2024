#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <numeric>

using namespace std;
template <typename T>
using grid = vector<vector<T>>;

struct Point {
    int x;
    int y;

    Point operator+(const Point& other) const {
        return { x + other.x, y + other.y };
    }
    Point* operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return this;
    }

    Point operator-(const Point& other) const {
        return { x - other.x, y - other.y };
    }
    Point* operator-=(const Point& other) {
        x -= other.x;
        y -= other.y;
        return this;
    }

    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }

    Point operator*(int i) const {
        return {i * x, i * y};
    }

    Point operator/(int i) const {
        return {x / i, y / i};
    }
};

using freq_map = unordered_map<char, vector<Point>>;

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << p.x << "," << p.y << ")";
    return os;
}

grid<char> readData() {
    string line;
    grid<char> ret;
    while (getline(cin, line)) {
        if (line == "") break;

        ret.emplace_back(line.begin(), line.end());
    }
    return ret;
}

template <typename T>
void printGrid(const grid<T>& g) {
    for (const auto& row : g) {
        for (auto c : row) {
            cout << c;
        }
        cout << endl;
    }
}

freq_map getFreqMap(const grid<char>& g) {
    freq_map ret;
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            if (g[i][j] != '.')
                ret[g[i][j]].emplace_back(i, j);
        }
    }
    return ret;
}

void printFreqMap(const freq_map& f) {
    for (const auto& kv : f) {
        cout << kv.first << ":";
        for (const auto& xy : kv.second) {
            cout << xy << endl; 
        }
        cout << endl;
    }
}

grid<bool> boolGrid(int rows, int columns) {
    grid<bool> ret;

    for (int i = 0; i < rows; i++) {
        ret.emplace_back(columns);
    }

    return ret;
}

Point getAntinode(const Point& a, const Point& b) {
    return b + b - a;
}

int countTrue(grid<bool> g) {
    int cnt = 0;
    for (const auto& row : g) {
        for (bool b : row) {
            cnt += b;
        }
    }
    return cnt;
}

Point reducePoint(const Point& p) {
    int common = gcd(p.x, p.y);
    return p / common;
}

template <typename T>
bool inBounds(int i, const vector<T>& v) {
    return i >= 0 && i < v.size();
}

template <typename T>
bool inBounds(const Point& p, const grid<T>& g) {
    return inBounds(p.x, g) && inBounds(p.y, g[p.x]);
}

int main() {
    auto g = readData();
    auto antinodes = boolGrid(g.size(), g[0].size());

    auto freqs = getFreqMap(g);

    auto mark = [&antinodes](const Point& pos) {
        if (pos.x < 0 || pos.x >= antinodes.size()) return;
        if (pos.y < 0 || pos.y >= antinodes[pos.x].size()) return;

        antinodes[pos.x][pos.y] = true;
    };

    for (const auto& kv : freqs) {
        const auto& dishes = kv.second;
        for (int i = 0; i < dishes.size() - 1; i++) {
            for (int j = i + 1; j < dishes.size(); j++) {
                auto step = reducePoint(dishes[j] - dishes[i]);
                auto node = dishes[j];
                while (inBounds(node, antinodes)) {
                    mark(node);
                    node += step;
                }
                node = dishes[i];
                while (inBounds(node, antinodes)) {
                    mark(node);
                    node -= step;
                }
            }
        }
    }

    cout << "Total: " << countTrue(antinodes) << endl;

    return 0;
}
