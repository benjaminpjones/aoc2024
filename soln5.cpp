#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<int, unordered_set<int>> readDependencies() {
    string line;
    getline(cin, line);
    unordered_map<int, unordered_set<int>> ret;
    while (line != "") {
        int split = line.find('|');
        int a = stoi(line.substr(0, split));
        int b = stoi(line.substr(split+1));

        ret[b].insert(a);

        getline(cin, line);
    }
    return ret;
}

vector<int> parseUpdate(string update) {
    vector<int> ret;
    while (true) {
        size_t i = update.find(",");
        if (i == string::npos) {
            ret.push_back(stoi(update));
            return ret;
        }

        ret.push_back(stoi(update.substr(0, i)));
        update = update.substr(i + 1);
    }
}

vector<vector<int>> readUpdates() {
    string line;
    getline(cin, line);
    vector<vector<int>> ret;
    while (line != "") {
        ret.push_back(parseUpdate(line));
        getline(cin, line);
    }
    return ret;
}

bool checkUpdate(vector<int> update, unordered_map<int, unordered_set<int>> deps) {
    for (int i = 0; i < update.size() - 1; ++i) {
        for (int j = i+1; j < update.size(); ++j) {
            if (deps[update[i]].contains(update[j]))
                return false;
        }
    }
    return true;
}

int middle(vector<int> v) {
    return v[v.size() / 2];
}

void sortUpdate(vector<int>& update, unordered_map<int, unordered_set<int>> deps) {
    auto comp = [&deps](int a, int b) {
        return deps[b].contains(a);
    };

    stable_sort(update.begin(), update.end(), comp);
}

void printVec(vector<int> v) {
    for (auto el : v) {
        cout << el << ' ';
    }
    cout << endl;
}

int main() {
    auto deps = readDependencies();

    for (const auto& dep : deps) {
        cout << dep.first << " - ";
        for (auto dd : dep.second) {
            cout << dd << ' ';
        }
        cout << endl;
    }

    auto updates = readUpdates();
    for (const auto& u : updates) {
        printVec(u);
    }

    int sum = 0;
    int sum2 = 0;
    for (auto& u : updates) {
        if (checkUpdate(u, deps))
            sum += middle(u);
        else {
            sortUpdate(u, deps);
            sum2 += middle(u);
        }
    }

    cout << "Sum: " << sum << endl;
    cout << "Sum2: " << sum2 << endl;

    return 0;
}
