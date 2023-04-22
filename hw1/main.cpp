#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    int ma = 0;
    for (int i = 0; i <= n; i++) {
        cout << "(" << i << "," << n - i << ")\n";
        ma = max(ma, i * (n - i));
    }
    cout << ma << '\n';
}
