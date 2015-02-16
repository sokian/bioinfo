/**
* Решение за O(length^2 * log(length))
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

    // Ввод
    int k;
    cin >> k;
    string text;
    cin >> text;
    int len = text.length();

    // Все подстроки длины k
    vector<string> substrs;
    for (int i = 0; i + k <= len; ++i) {
        substrs.push_back(text.substr(i, k));
    }
    sort(substrs.begin(), substrs.end());

    // Вывод результата
    for (const string &s : substrs) {
        cout << s << endl;
    }

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

