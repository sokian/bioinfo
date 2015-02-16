/**
* Решение за O(length(rnaString))
*/

#include "bits/stdc++.h"

using namespace std;

map<string, char> geneticCode;

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

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    prepareGeneticCode();

    string rna;
    cin >> rna;

    string ans;
    for (int i = 0; i + 3 <= (int)rna.length(); i += 3) {
        char c = geneticCode[rna.substr(i, 3)];
        if (c == -1) break;
        ans += c;
    }

    cout << ans << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};