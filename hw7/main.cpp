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
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second
#define mp make_pair

unordered_map<string, unordered_set<int> > id_set;
unordered_map<int,int> total_words;
map<pair<int,string>, int> word_cnt;

int corpus_cnt = 0;

int main(int argc, char **argv) {
    cin.sync_with_stdio(0), cin.tie(0);

    ifstream corpus(argv[1]);
    ifstream query(argv[2]);
    int k = stoi(argv[3]);
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
                total_words[id]++;
                word_cnt[{id,word}]++;
                word = "";
            } else if (isalpha(line[i])) {
                word += tolower(line[i]);
            }
        }
        if (word != "") {
            id_set[word].insert(id);
            total_words[id]++;
            word_cnt[{id,word}]++;
        }
    }
    while (getline(query, line)) {
        stringstream ss(line);
        string word;
        unordered_map<int, double> ans;
        while (ss >> word) {
            for (auto &i : word) i = tolower(i);
            if (id_set.count(word)) {
                double word_idf = log10((double)corpus_cnt / id_set[word].size());
                for (auto id : id_set[word]) {
                    double new_tf=(double)word_cnt[{id,word}]/total_words[id];
                    ans[id] += word_idf*new_tf;
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
