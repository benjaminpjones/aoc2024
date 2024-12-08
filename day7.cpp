#include <iostream>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

pair<long long, vector<int>> parseLine(string s) {
    vector<int> rhs;

    // Split the string around the colon
    size_t colonPos = s.find(':');
    // Parse the number before the colon
    long long lhs = stoll(s.substr(0, colonPos));

    // Parse the numbers after the colon
    istringstream rhsStream(s.substr(colonPos + 1));
    int num;
    while (rhsStream >> num) {
        rhs.push_back(num);
    }

    return make_pair(lhs, rhs);
}

void printVec(vector<int> v) {
    for (int val : v) cout << val << ' ';
    cout << endl;
}

bool isValid(long long lhs, const vector<int>& rhs, long long currVal, int currIndex) {
    if (currIndex == rhs.size()) {
        return currVal == lhs;
    }

    return isValid(lhs, rhs, currVal * static_cast<long long>(rhs[currIndex]), currIndex + 1)
        || isValid(lhs, rhs, currVal + static_cast<long long>(rhs[currIndex]), currIndex + 1)
        || isValid(lhs, rhs, stoll(to_string(currVal) + to_string(rhs[currIndex])), currIndex + 1);
}

int main() {
    string line;
    long long sum = 0;
    while (getline(cin, line)) {
        if (line == "") break;
        auto data = parseLine(line);
        auto lhs = data.first;
        auto& rhs = data.second;

        if (isValid(lhs, rhs, rhs[0], 1)) {
            sum += lhs;
        }
    }
    cout << "Sum: " << sum << endl;
    return 0;
}
