/**
* Решение за O(length * k log(k))
*/

#include "bits/stdc++.h"

using namespace std;

vector<string> readVectorString()  {
    vector<string> ret;
    string s;
    while (cin >> s) {
        ret.push_back(s);
    }
    return ret;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //Ввод данных
    vector<string> vs = readVectorString();
    if (vs.empty()) {
        return 0;
    }
    int len = vs[0].length();

    // Создание мап префиксов длины len - 1
    map<string, vector<string> > m;
    for (const string &s : vs) {
        m[s.substr(0, len - 1)].push_back(s);
    }

    // Создание графа
    map<string, vector<string> > graph;
    for (const string &s : vs) {
        if (!m.count(s.substr(1))) {
            continue;
        }
        const vector<string> &edges = m[s.substr(1)];
        for (const string &to : edges) {
            graph[s].push_back(to);
        }
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

