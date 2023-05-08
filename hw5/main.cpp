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
#define pb push_back
#define all(a) begin(a), end(a)

struct node {
    node *nxt[26] = {NULL};
    set<int> idx;
};

int main(int argc, char **argv) {
    node *root = new node;

    FILE *file = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    char line[100005];

    //Read Data
    set<int> all_idx;
    while (fgets(line, sizeof(line), file)) {
        int idx = 0, i = 0, quote = 0;
        while (isdigit(line[i])) idx = idx * 10 + line[i++] - '0';
        all_idx.insert(idx);
        node *p = root;
        for (;; i++) {
            if (line[i] == '\"') {
                quote++;
                if (quote == 2) {
                    p->idx.insert(idx);
                    break;
                }
            } else if (quote == 1 && line[i] == ' ') {
                p->idx.insert(idx);
                p = root;
            } else if (isalpha(line[i])) {
                int to = tolower(line[i]) - 'a';
                if (p->nxt[to] == NULL) p->nxt[to] = new node;
                p = p->nxt[to];
            }
        }
    }

    //Query
    while (fgets(line, sizeof(line), file2)) {
        node *p = root;
        set<int> ans = all_idx;
        int n = strlen(line);
        line[n++]=10;
        for (int i = 0; i < n; i++) {
            bool fail_match = false;
            if (line[i] == ' ' || line[i] == 10 || line[i] == 13) {
                set<int> tmp;
                set_intersection(all(ans), all(p->idx), inserter(tmp, tmp.begin()));
                ans = tmp;
                p = root;
            } else if (isalpha(line[i]) ) {
                int to = tolower(line[i]) - 'a';
                if (p->nxt[to]) p = p->nxt[to];
                else fail_match = true;
            } else {
                fail_match = true;
            }
            if(fail_match){
                ans.clear();
                break;
            }
            if (line[i] == 10 || line[i] == 13) break;
        }
        if (ans.empty()) cout << -1 << '\n';
        else for (auto &idx : ans) cout << idx << " \n"[idx == *prev(ans.end())];
    }
}