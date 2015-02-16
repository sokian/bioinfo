/**
* Решение за O(length * k log(k))
*/

#include "bits/stdc++.h"

using namespace std;

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    // Ввод данных
    int k;
    cin >> k;
    string s;
    cin >> s;
    int len = s.length();
    --k;

    // k-mers of string s
    vector<string> kmers;

    for (int i = 0; i + k <= len; ++i) {
        kmers.push_back(s.substr(i, k));
    }

    // Construction of De Bruijn Graph from a String
    map<string, vector<string> > graph;
    for (int i = 0; i + 1 < int(kmers.size()); ++i) {
        graph[kmers[i]].push_back(kmers[i + 1]);
    }

    // Вывод результата
    for (const pair<string, vector<string> > &kv : graph) {
        cout << kv.first << " -> ";
        for (int i = 0; i < int(kv.second.size()); ++i) {
            if (i) cout << ",";
            cout << kv.second[i];
        }
        cout << endl;
    }


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

