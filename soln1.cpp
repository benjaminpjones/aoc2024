// g++ soln1.cpp -o soln1.out && ./soln1.out < in1.txt

#include <iostream>
#include <vector>
#include <algorithm>

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

    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += abs(data.first[i] - data.second[i]); 
    }

    cout << sum << endl;

    return 0;
}
