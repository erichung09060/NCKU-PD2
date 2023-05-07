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
//#define _GLIBCXX_DEQUE_BUF_SIZE 64
//#pragma pack(1)
#include <bits/stdc++.h>
using namespace std;
#define all(a) begin(a), end(a)
#define fastio cin.sync_with_stdio(0),cin.tie(0),cout.tie(0);

array<long, 4> ans[3];  // id days start end
inline void update(array<long, 4> ins) {
    if (ins[1] > ans[0][1]) {
        ans[2] = ans[1];
        ans[1] = ans[0];
        ans[0] = ins;
    } else if (ins[1] > ans[1][1]) {
        ans[2] = ans[1];
        ans[1] = ins;
    } else if (ins[1] > ans[2][1]) {
        ans[2] = ins;
    }
}

int main(int argc, char **argv) { fastio
    FILE *file = fopen(argv[1], "r");
    char line[1024];
    vector<array<long, 2>> Data; //id time
    while (fgets(line, sizeof(line), file)) {
        int index = 0, comma = 0;
        int id = 0, year = 0, mday = 0, mon = 0, i = 0;
        while(true){
            if (line[i] == ',') {
                comma++;
                index = 0;
            } else if (comma == 0) {
                id = id * 10 + line[i] - '0';
            } else if (comma == 2) {
                if (index <= 4)
                    year = year * 10 + line[i] - '0';
                else if (index <= 6)
                    mon = mon * 10 + line[i] - '0';
                else if (index <= 8)
                    mday = mday * 10 + line[i] - '0';
                if(index == 8) break;
            }
            index++, i++;
        }
        tm info{0, 0, 0};
        info.tm_year = year - 1900;
        info.tm_mon = mon - 1;
        info.tm_mday = mday;

        Data.push_back({id, mktime(&info)});
    }

    stable_sort(all(Data));
    Data.resize(unique(all(Data)) - Data.begin());
    Data.push_back({-1, -1});

    array<long, 4> best{0, 0, 0, 0};
    long startT = Data[0][1], endT = 0, Cont_days = 1;
    for (int i = 1; i < Data.size(); ++i) {
        if (Data[i - 1][0] != Data[i][0] || Data[i][1] - Data[i - 1][1] != 60 * 60 * 24) { // update best : different id or not continue
            endT = Data[i - 1][1];
            if (Cont_days >= best[1]) best = {Data[i - 1][0], Cont_days, startT, endT};
            startT = Data[i][1];
            Cont_days = 1;

            if (Data[i - 1][0] != Data[i][0]) {  // different id
                update(best);
                best = {0, 0, 0, 0};
            }
        } else {
            Cont_days++;
        }
    }
    for (int i = 0; i < 3; i++) {
        tm startT = *localtime(&ans[i][2]);
        tm endT = *localtime(&ans[i][3]);

        cout << ans[i][0] << ',' << ans[i][1] << ',';
        cout << startT.tm_year + 1900 << setw(2) << setfill('0') << startT.tm_mon + 1 << setw(2) << setfill('0') << startT.tm_mday << ',';
        cout << endT.tm_year + 1900 << setw(2) << setfill('0') << endT.tm_mon + 1 << setw(2) << setfill('0') << endT.tm_mday << '\n';
    }
}
