#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("fma,sse,sse2,sse3,sse4")
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
        int len = strlen(line) - 2;

        int id = 0, date = 0, Time = 0;
        for (int i = 0; i < len; i++) {
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
