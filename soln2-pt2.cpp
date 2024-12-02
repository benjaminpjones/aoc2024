#include <iostream>
#include <vector>
#include <sstream>
#include <optional>
#include <functional>
#include <cassert>

using namespace std;

optional<vector<int>> readRow() {
    string line;
    if (!getline(cin, line)) {
        return nullopt;
    }
    stringstream ss(line);
    vector<int> row;
    int n;
    while (ss >> n) {
        row.push_back(n);
    }
    return row;
}

bool compareAll(const vector<int>& v, function<bool(int, int)> compare) {
    int last = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (!compare(last, v[i])) {
            return false;
        }
        last = v[i];
    }
    return true;
}

bool isDecreasing(const vector<int>& v) {
    return compareAll(v, [](int last, int curr) {
        return last >= curr;
    });
}

bool isIncreasing(const vector<int>& v) {
    return compareAll(v, [](int last, int curr) {
        return last <= curr;
    });
}

bool isSteady(const vector<int>& v) {
    return compareAll(v, [](int last, int curr) {
        int diff = abs(curr - last);
        return diff >= 1 && diff <= 3;
    });
}

bool checkWithDampener(vector<int> v, function<bool(const vector<int>&)> check) {
    if (check(v)) {
        return true;
    }
    for (int i = 0; i <= v.size(); i++) {
        vector<int> vCopy(v);
        vCopy.erase(vCopy.begin() + i);
        if (check(vCopy)) {
            return true;
        }
    }

    return false;
}

int main() {
    int count = 0;
    while (auto rowTry = readRow()) {
        auto row = rowTry.value();
        if (!row.size()) {
            continue;
        }
        auto check = [](const vector<int>& v) {
            return (isDecreasing(v) || isIncreasing(v)) && isSteady(v);
        };
        if (checkWithDampener(row, check)) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
