/**
* Решение - стандартная динамика dp[i,j] - наидлиннейший путь из (0,0) в (i,j)
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

    //Ввод данных
    int n, m;
    cin >> n >> m;

    vector<vector<long long> > down(n, vector<long long>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            cin >> down[i][j];
        }
    }
    // Зачем здесь дефис???
    {string s;cin >> s;}
    vector<vector<long long> > right(n + 1, vector<long long>(m, 0));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> right[i][j];
        }
    }

    // Посчитаем динамику длиннейший путь из (0,0) в (i,j)
    vector<vector<long long> > longestPath(n + 1, vector<long long>(m + 1, LLONG_MIN));
    // инициализация
    longestPath[0][0] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // два возможных перехода
            if (i) {
                longestPath[i][j] = max(longestPath[i][j], longestPath[i - 1][j] + down[i - 1][j]);
            }
            if (j) {
                longestPath[i][j] = max(longestPath[i][j], longestPath[i][j - 1] + right[i][j - 1]);
            }
        }
    }

    // Вывод результата
    cout << longestPath[n][m] << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

