/**
* Решение за O(length(inputString))
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

    // Заведем мапу комплиментарности
    map<char, char> complement;
    complement['A'] = 'T';
    complement['T'] = 'A';
    complement['C'] = 'G';
    complement['G'] = 'C';

    // Ввод DNA string
    string dna;
    cin >> dna;


    // Составляем строку комплиментарности и делаем реверс
    string reverseComplement = dna;
    for (char &c : reverseComplement) {
        c = complement[c];
    }
    reverse(reverseComplement.begin(), reverseComplement.end());

    // Вывод результата
    cout << reverseComplement << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};