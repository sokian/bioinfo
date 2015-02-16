/**
* Решение так как нужно вывести все подсроки из которых можно получить Peptide,
* а не только уникальные то решение за O(length(dna)^2)
* Если бы нужно было бы найти уникальные такие подстроки, то можно было бы написать перебор,
* который поддерживает текущее состояние в суффиксном автомате строки (dna) и работал бы за размер ответа
*/

#include "bits/stdc++.h"

using namespace std;

map<string, char> geneticCode;
map<char, char> complement;

// NO COMMENTS
void prepareGeneticCode() {

    // auto generated code
    geneticCode["UUU"] = 'F';
    geneticCode["UUC"] = 'F';

    geneticCode["UUA"] = 'L';
    geneticCode["UUG"] = 'L';
    geneticCode["CUU"] = 'L';
    geneticCode["CUC"] = 'L';
    geneticCode["CUA"] = 'L';
    geneticCode["CUG"] = 'L';

    geneticCode["AUU"] = 'I';
    geneticCode["AUC"] = 'I';
    geneticCode["AUA"] = 'I';

    geneticCode["AUG"] = 'M';

    geneticCode["GUU"] = 'V';
    geneticCode["GUC"] = 'V';
    geneticCode["GUA"] = 'V';
    geneticCode["GUG"] = 'V';

    geneticCode["UCU"] = 'S';
    geneticCode["UCC"] = 'S';
    geneticCode["UCA"] = 'S';
    geneticCode["UCG"] = 'S';

    geneticCode["CCU"] = 'P';
    geneticCode["CCC"] = 'P';
    geneticCode["CCA"] = 'P';
    geneticCode["CCG"] = 'P';

    geneticCode["ACU"] = 'T';
    geneticCode["ACC"] = 'T';
    geneticCode["ACA"] = 'T';
    geneticCode["ACG"] = 'T';

    geneticCode["GCU"] = 'A';
    geneticCode["GCC"] = 'A';
    geneticCode["GCA"] = 'A';
    geneticCode["GCG"] = 'A';

    geneticCode["UAU"] = 'Y';
    geneticCode["UAC"] = 'Y';

    geneticCode["CAU"] = 'H';
    geneticCode["CAC"] = 'H';

    geneticCode["CAA"] = 'Q';
    geneticCode["CAG"] = 'Q';

    geneticCode["AAU"] = 'N';
    geneticCode["AAC"] = 'N';

    geneticCode["AAA"] = 'K';
    geneticCode["AAG"] = 'K';

    geneticCode["GAU"] = 'D';
    geneticCode["GAC"] = 'D';

    geneticCode["GAA"] = 'E';
    geneticCode["GAG"] = 'E';

    geneticCode["UGU"] = 'C';
    geneticCode["UGC"] = 'C';

    geneticCode["UGG"] = 'W';

    geneticCode["CGU"] = 'R';
    geneticCode["CGC"] = 'R';
    geneticCode["CGA"] = 'R';
    geneticCode["CGG"] = 'R';

    geneticCode["AGU"] = 'S';
    geneticCode["AGC"] = 'S';

    geneticCode["AGA"] = 'R';
    geneticCode["AGG"] = 'R';

    geneticCode["GGU"] = 'G';
    geneticCode["GGC"] = 'G';
    geneticCode["GGA"] = 'G';
    geneticCode["GGG"] = 'G';

    geneticCode["UGA"] = -1;
    geneticCode["UAA"] = -1;
    geneticCode["UAG"] = -1;
}

void prepareComplement() {
    complement['A'] = 'T';
    complement['T'] = 'A';
    complement['C'] = 'G';
    complement['G'] = 'C';
}

void prepare() {
    prepareGeneticCode();
    prepareComplement();
}

// reverse complement dna
string getReverseComplement(string s) {
    for (char &c : s) {
        c = complement[c];
    }
    reverse(s.begin(), s.end());
    return s;
}

// RNA from DNA
string getRna(string dna) {
    for (char &c : dna) {
        if (c == 'T') c = 'U';
    }
    return dna;
}

// Peptide
string getPeptide(const string &s) {
    string result;
    for (size_t i = 0; i + 3 <= s.length(); i += 3) {
        char c = geneticCode[s.substr(i, 3)];
        if (c == -1) break;
        result += c;
    }
    return result;
}

// Проверяет можно ли из данной dna получить пептид
bool checkPeptide(const string &dna, const string &peptide) {
    string rna = getRna(dna);
    string revRna = getRna(getReverseComplement(dna));
    if (getPeptide(rna) == peptide) {
        return true;
    }
    if (getPeptide(revRna) == peptide) {
        return true;
    }
    return false;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Заполняем мапы генетических кодов
    prepare();


    // Входные данные
    string dna;
    cin >> dna;
    string peptide;
    cin >> peptide;

    size_t lengthOfPattern = peptide.length() * 3;
    // Проверяем все подстроки длины lengthOfPattern и выдводим подходящие
    for (size_t i = 0; i + lengthOfPattern <= dna.length(); ++i) {
        string pattern = dna.substr(i, lengthOfPattern);
        if (checkPeptide(pattern, peptide)) {
            cout << pattern << endl;
        }
    }

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};