#include <bits/stdc++.h>
using namespace std;
#define all(a) begin(a), end(a)

vector<array<int, 3>> Data;

int main(int argc, char** argv) {
    cin.sync_with_stdio(0), cin.tie(0), cout.tie(0);
    Data.reserve(1e7);
    FILE* file = fopen(argv[1], "r");

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int index = 0;
        int comma = 0;

        int id = 0, date = 0, Time = 0;
        for (int i = 0; isdigit(line[i]) || isalpha(line[i]) || line[i]==',' || line[i]=='-'; i++) {
            if (line[i] == ',') {
                comma++;
                index = 0;
            } else if (comma == 0) {
                id = id * 10 + line[i] - '0';
            } else if (comma == 2) {
                if (index <= 8)
                    date = date * 10 + line[i] - '0';
                else
                    Time = Time * 10 + line[i] - '0';
            }
            index++;
        }
        Time = (Time / 100) * 60 + Time % 100;
        Data.push_back({id, date, Time});
    }
    stable_sort(all(Data));
    Data.push_back({-1, -1, -1});

    int over = 0;
    int forget = 0;
    int n = Data.size();
    for (int i = 0; i < n; ++i) {
        if (i && Data[i][0] != Data[i - 1][0]) {
            cout << Data[i - 1][0] << ',' << over << ',' << forget << '\n';
            over = forget = 0;
        }
        if ((i == 0 || !(Data[i - 1][0] == Data[i][0] && Data[i - 1][1] == Data[i][1])) &&
            (i == n - 1 || !(Data[i + 1][0] == Data[i][0] && Data[i + 1][1] == Data[i][1]))) forget++;

        if (i && Data[i - 1][0] == Data[i][0] && Data[i - 1][1] == Data[i][1] && Data[i][2] - Data[i - 1][2] > 60 * 8) over++;
    }
}
