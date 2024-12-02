// g++ soln1-pt2.cpp -o soln1.out && ./soln1.out < in1.txt

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

pair<vector<int>, vector<int>> readInput() {
    pair<vector<int>, vector<int>> ret;
    int i1, i2;
    while (cin >> i1 >> i2) {
        ret.first.push_back(i1);
        ret.second.push_back(i2);
    }
    return ret;
}

int main() {
    auto data = readInput();
    ranges::sort(data.first);
    ranges::sort(data.second);

    unordered_map<int, int> frequencies;
    for (const auto& val : data.second) {
        if (frequencies.contains(val)) {
            frequencies[val]++;
        } else {
            frequencies[val] = 1;
        }
    }

    long similarity = 0;
    for (const auto& val : data.first) {
        auto freq = 0;
        if (frequencies.contains(val)) {
            freq = frequencies[val];
        }

        similarity += val * freq; 
    }

    cout << similarity << endl;

    return 0;
}
