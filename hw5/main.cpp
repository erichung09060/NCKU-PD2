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

    // Read Data
    set<int> all_idx;
    while (fgets(line, sizeof(line), file)) {
        int idx = 0, i = 0, quote = 0;
        while (isdigit(line[i])) idx = idx * 10 + line[i++] - '0';
        all_idx.insert(idx);
        node *p = root;
        for (; line[i] != 10 && line[i] != 13; i++) {
            if (line[i] == ' ' && p != root) {
                p->idx.insert(idx);
                p = root;
            } else if (isalpha(line[i])) {
                int to = tolower(line[i]) - 'a';
                if (p->nxt[to] == NULL) p->nxt[to] = new node;
                p = p->nxt[to];
            }
        }
        p->idx.insert(idx);
    }
    // Query
    while (fgets(line, sizeof(line), file2)) {
        node *p = root;
        set<int> ans = all_idx;
        int n = strlen(line);
        line[n++] = 10;
        for (int i = 0; i < n; i++) {
            bool fail_match = false;
            if (line[i] == ' ' || line[i] == 10 || line[i] == 13) {
                set<int> tmp;
                set_intersection(all(ans), all(p->idx), inserter(tmp, tmp.begin()));
                ans = tmp;
                p = root;
            } else if (isalpha(line[i])) {
                int to = tolower(line[i]) - 'a';
                if (p->nxt[to]) p = p->nxt[to];
                else fail_match = true;
            } else {
                fail_match = true;
            }
            if (fail_match) {
                ans.clear();
                break;
            }
            if (line[i] == 10 || line[i] == 13) break;
        }
        if (ans.empty()) cout << -1 << '\n';
        else for (auto &idx : ans) cout << idx << " \n"[idx == *prev(ans.end())];
    }
}
