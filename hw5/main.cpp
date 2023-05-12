#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(a) begin(a), end(a)

struct node {
    node *nxt[26] = {NULL};
    unordered_set<int> id;
};

int main(int argc, char **argv) {
    //cin.sync_with_stdio(0),cin.tie(0);
    node *root = new node;

    FILE *file = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    char line[100005];

    // Read Data
    while (fgets(line, sizeof(line), file)) {
        int id = 0, i = 0, quote = 0;
        while (isdigit(line[i])) id = id * 10 + line[i++] - '0';

        node *p = root;
        for (; line[i] != 10 && line[i] != 13; i++) {
            if (line[i] == ' ' && p != root) {
                p->id.insert(id);
                p = root;
            } else if (isalpha(line[i])) {
                int to = tolower(line[i]) - 'a';
                if (p->nxt[to] == NULL) p->nxt[to] = new node;
                p = p->nxt[to];
            }
        }
        p->id.insert(id);
    }
    // Query
    while (fgets(line, sizeof(line), file2)) {
        node *p = root;
        unordered_map<int,int> cnt;
        int n = strlen(line), words = 0;
        line[n++] = 10;
        bool fail = false;
        for (int i = 0; !fail && line[i] != 10 && line[i] != 13; i++) {
            if (line[i] == ' ' && p != root) {
                for(auto i:p->id) cnt[i]++;
                words++;
                p = root;
            } else if (isalpha(line[i])) {
                int to = tolower(line[i]) - 'a';
                if (p->nxt[to]) p = p->nxt[to];
                else fail = true;
            } else {
                fail = true;
            }
        }
        
        if(p != root){
            for(auto i:p->id) cnt[i]++;
            words++;
        }
        
        if(fail){
            cout << -1 << '\n';
        }else{
            vector<int> ans;
            for(auto i:cnt) if(i.second == words) ans.pb(i.first);
            sort(all(ans));

            if (ans.empty()) cout << -1 << '\n';
            else for (auto &i : ans) cout << i << " \n"[i == ans.back()];
        }
    }
}
