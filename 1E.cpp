/**
* Решение за O(length(inputString))
* Поддерживаем количество G и количество C на префиксе и обновляем ответ,
* если значение Skew стало меньше текущего минимума
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


    // Входные данные
    string genome;
    cin >> genome;
    int length = int(genome.length());

    // Количества С и G
    int numberOfG = 0;
    int numberOfC = 0;
    // Для префикса длины 0 minSkew = 0 и есть пока только одна позиция
    vector<int> minSkewPositions;
    int minSkew = 0;
    minSkewPositions.push_back(0);

    // Основной цикл, перебираем длину префикса
    for (int i = 0; i < length; ++i) {
        if (genome[i] == 'G') {
            ++numberOfG;
        }
        if (genome[i] == 'C') {
            ++numberOfC;
        }
        int currentSkew = numberOfG - numberOfC;

        // Обновляем текущий минимум
        if (currentSkew < minSkew) {
            minSkew = currentSkew;
            minSkewPositions.clear();
        }
        // Добавляем новую длину префикса в ответ
        if (currentSkew == minSkew) {
            minSkewPositions.push_back(i + 1);
        }
    }

    // Вывод результата
    for (int pos : minSkewPositions) {
        cout << pos << " ";
    }
    cout << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};