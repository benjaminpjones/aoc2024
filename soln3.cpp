// g++ soln3.cpp -o soln3.out && ./soln3.out < in3.txt

#include <iostream>
#include <regex>

using namespace std;

bool doMul = true;

long parseAllMul(const string& line) {
    regex mul_regex("do(n't)?\\(\\)|mul\\(([0-9]+),([0-9]+)\\)");

    auto begin = sregex_iterator(line.begin(), line.end(), mul_regex);
    auto end = sregex_iterator();

    long sum = 0;

    for (auto it = begin; it != end; ++it) {
        auto m = *it;
        if (m.str() == "do()") {
            doMul = true;
        } else if (m.str() == "don't()") {
            doMul = false;
        } else if (doMul) {
            sum += stoi(m[2]) * stoi(m[3]);
        }
    }
    return sum;
}

int main() {
    string line;
    long sum = 0;
    while (getline(cin, line)) {
        sum += parseAllMul(line);
    }

    cout << sum << endl;

    return 0;
}
