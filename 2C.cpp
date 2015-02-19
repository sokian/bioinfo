/**
* Решение за O(размер ответа) * log(размера ответа)
* лог - только из-за сортировки масс
*/

#include "bits/stdc++.h"

using namespace std;

map<char, int> aminoAcidMass;
// NO COMMENTS
void prepareAminoAcidMass() {
    aminoAcidMass['G'] = 57;
    aminoAcidMass['A'] = 71;
    aminoAcidMass['S'] = 87;
    aminoAcidMass['P'] = 97;
    aminoAcidMass['V'] = 99;

    aminoAcidMass['T'] = 101;
    aminoAcidMass['C'] = 103;
    aminoAcidMass['I'] = 113;
    aminoAcidMass['L'] = 113;
    aminoAcidMass['N'] = 114;

    aminoAcidMass['D'] = 115;
    aminoAcidMass['K'] = 128;
    aminoAcidMass['Q'] = 128;
    aminoAcidMass['E'] = 129;
    aminoAcidMass['M'] = 131;

    aminoAcidMass['H'] = 137;
    aminoAcidMass['F'] = 147;
    aminoAcidMass['R'] = 156;
    aminoAcidMass['Y'] = 163;
    aminoAcidMass['W'] = 186;
}

// масса пептида
int getMass(const string &s) {
    int result = 0;
    for (char c : s) {
        result += aminoAcidMass[c];
    }
    return result;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Заполняем веса амино кислот
    prepareAminoAcidMass();


    // Входные данные
    string peptide;
    cin >> peptide;

    // Удвоим строку для удобства
    string cyclicPeptide = peptide + peptide;

    vector<int> cyclospectrum;
    cyclospectrum.push_back(0);
    cyclospectrum.push_back(getMass(peptide));

    // перебираем циклический сдвиг
    for (int i = 0; i < (int)peptide.length(); ++i) {
        int mass = 0;
        // берем подстроку длины J одновременно посчитываем массу данного подпептида
        for (int j = 1; j < (int)peptide.length(); ++j) {
            mass += aminoAcidMass[cyclicPeptide[i + j - 1]];
            cyclospectrum.push_back(mass);
        }
    }

    // сортируем массы
    sort(cyclospectrum.begin(), cyclospectrum.end());

    // выводим резульатат
    for (int mass : cyclospectrum) {
        cout << mass << " ";
    }
    cout << endl;
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};