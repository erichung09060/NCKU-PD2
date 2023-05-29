#include <bits/stdc++.h>
using namespace std;
#define all(a) begin(a), end(a)
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second
#define mp make_pair

unordered_map<string, set<int>> id_set;
int corpus_cnt = 0;

int main(int argc, char **argv) {
    cin.sync_with_stdio(0), cin.tie(0);

    ifstream corpus(argv[1]);
    ifstream query(argv[2]);
    int k = argv[3][0] - '0';
    string line;

    while (getline(corpus, line)) {
        corpus_cnt++;

        int id = 0, i = 0;
        while (isdigit(line[i])) id = id * 10 + line[i++] - '0';
        vector<string> str;
        string word;
        for (; i < line.size(); i++) {
            if (line[i] == ' ' && word != "") {
                id_set[word].insert(id);
                word = "";
            } else if (isalpha(line[i])) {
                word += tolower(line[i]);
            }
        }
        if (word != "") id_set[word].insert(id);
    }
    while (getline(query, line)) {
        stringstream ss(line);
        string word;
        unordered_map<int, double> ans;
        while (ss >> word) {
            for (auto &i : word) i = tolower(i);
            if (id_set.count(word)) {
                double word_idf = log10((double)corpus_cnt / id_set[word].size());
                for (auto i : id_set[word]) {
                    ans[i] += word_idf;
                }
            }
        }
        vector<pair<double,int>> Ans;
        for (auto i : ans) {
            if (i.S) Ans.pb({-i.S, i.F});
        }
        sort(all(Ans));
        for (int i = Ans.size(); i < k; i++) Ans.pb({-1, -1});
        for (int i = 0; i < k; i++) cout << Ans[i].S << " \n"[i == k-1];
    }
}
