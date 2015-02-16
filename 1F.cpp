/**
* Решение за O(length(genome) * length(pattern))
* Существуют и более оптимальные методы решения подобных задач, но они гораздо более сложные в написании
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
    string pattern;
    cin >> pattern;
    int patternLength = int(pattern.length());
    string text;
    cin >> text;
    int textLength = int(text.length());
    int numberOfMistakes;
    cin >> numberOfMistakes;


    // Примерные вхождения pattern в text
    vector<int> approximateOccurrences;

    for (int pos = 0; pos + patternLength <= textLength; ++pos) {
        // Подсчитаем число ошибок, если сичтать вхождение pattern начиная с позиции pos
        int mistakes = 0;
        for (int index = 0; index < patternLength; ++index) {
            if (pattern[index] != text[index + pos]) {
                mistakes++;
            }
        }
        // Если число ошибок не превышает допустимого добавляем эту позицию в ответ
        if (mistakes <= numberOfMistakes) {
            approximateOccurrences.push_back(pos);
        }
    }

    // Вывод результата
    for (int pos : approximateOccurrences) {
        cout << pos << " ";
    }
    cout << endl;



#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};