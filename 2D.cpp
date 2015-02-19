/**
* Решение - стандартная задача о рюкзаке
* Асимптотика - O(totalMass)
*/

#include "bits/stdc++.h"

using namespace std;

// Веса удалены равные
int w[] = {57, 71, 87, 97, 99,
           101, 103, 113, 114,
           115, 128, 129, 131,
           137, 147, 156, 163, 186};
int wsize = 18;

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    // Входные данные
    int m;
    cin >> m;

    // Инициализация динамического программирования
    vector<unsigned long long> numberOfAminoAcids(m + 1, 0);
    numberOfAminoAcids[0] = 1;

    for (int mass = 1; mass <= m; ++mass) {
        for (int i = 0; i < wsize; ++i) {
            if (mass - w[i] >= 0) {
                numberOfAminoAcids[mass] += numberOfAminoAcids[mass - w[i]];
            }
        }
    }

    // Вывод результата
    cout << numberOfAminoAcids[m] << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};