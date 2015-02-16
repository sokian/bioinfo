/**
* Решение - стандартная динамика dp[i,j] - наидлиннейшая общая подстрока префикса длины i первой строки и префикса длины j второй строки
* Ассимптотика O(n * m)
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
    string a, b;
    cin >> a >> b;

    int n = a.length();
    int m = b.length();

    vector<vector<int> > longestCommonSubsequence(n + 1, vector<int>(m + 1, -1));
    longestCommonSubsequence[0][0] = 0;
    // previousState
    // 1 - пропускаем символ первой строки
    // 2 - пропускаем символ второй строки
    // 3 - берем символ из обеих строк
    vector<vector<char> > previousState(n + 1, vector<char>(m + 1, 0));

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i && j) {
                if (a[i - 1] == b[j - 1]) {
                    if (longestCommonSubsequence[i][j] < longestCommonSubsequence[i - 1][j - 1] + 1) {
                        longestCommonSubsequence[i][j] = longestCommonSubsequence[i - 1][j - 1] + 1;
                        previousState[i][j] = 3;
                    }
                }
            }
            if (i) {
                if (longestCommonSubsequence[i][j] < longestCommonSubsequence[i - 1][j]) {
                    longestCommonSubsequence[i][j] = longestCommonSubsequence[i - 1][j];
                    previousState[i][j] = 1;
                }
            }
            if (j) {
                if (longestCommonSubsequence[i][j] < longestCommonSubsequence[i][j - 1]) {
                    longestCommonSubsequence[i][j] = longestCommonSubsequence[i][j - 1];
                    previousState[i][j] = 2;
                }
            }
        }
    }

    // Востановление ответа
    // Текущее состояние динамики
    pair<int, int> state = make_pair(n, m);
    // Начальное состояние
    pair<int, int> initial = make_pair(0, 0);
    // Результат
    string commonSubsequence;

    while (state != initial) {
        switch (previousState[state.first][state.second]) {
        case 1:
            state.first--;
            break;
        case 2:
            state.second--;
            break;
        case 3:
            commonSubsequence += a[state.first - 1];
            state.first--;
            state.second--;
            break;
        }
    }
    reverse(commonSubsequence.begin(), commonSubsequence.end());

    // Вывод результата
    cout << commonSubsequence << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

