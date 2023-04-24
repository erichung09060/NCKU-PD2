#include <bits/stdc++.h>
using namespace std;
#define all(a) begin(a), end(a)
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second

bool cmp(vector<int> a, vector<int> b) {
    if (a[3] == b[3]) {
        if (a[1] == b[1]) {
            if (a[2] == b[2]) {
                return a[0] < b[0];
            } else {
                return a[2] < b[2];
            }
        } else {
            return a[1] < b[1];
        }
    } else {
        return a[3] < b[3];
    }
}

int main(int argc, char** argv) {
    ifstream input(argv[1]);
    vector<vector<int>> a;
    string line;
    while (input >> line) {
        stringstream ss(line);
        string obj;
        vector<int> b;
        while (getline(ss, obj, ',')) {
            int val;
            if (obj == "f") val = 0;
            else if (obj == "m") val = 1;
            else val = stoi(obj);
            b.push_back(val);
        }
        a.push_back(b);
    }
    sort(all(a), cmp);
    int pre = a[0][3];
    cout << pre;
    for (auto i : a) {
        if (i[3] == pre) {
            cout << "," << i[0];
        } else {
            cout << '\n' << i[3] << "," << i[0];
            pre = i[3];
        }
    }
    cout << '\n';
}
