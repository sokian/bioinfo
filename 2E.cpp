/**
* Решение - brute-force solution
*/

#include "bits/stdc++.h"

using namespace std;

// Веса amino acids
vector<int> weights = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};

vector<int> inputVector() {
    vector<int> ret;
    int x;
    while (cin >> x) {
        ret.push_back(x);
    }
    sort(ret.begin(), ret.end());
    return ret;
}


vector<int> currentPeptide;
vector<vector<int> > answer;
vector<int> inputSpectrum;

vector<int> getLinearSpectrum(const vector<int> &peptide) {
    vector<int> ret;
    ret.push_back(0);
    for (int i = 0; i < peptide.size(); ++i) {
        for (int j = i; j < peptide.size(); ++j) {
            ret.push_back(accumulate(peptide.begin() + i, peptide.begin() + j + 1, 0));
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

vector<int> getCycloSpectrum(const vector<int> &peptide) {
    vector<int> ret;
    ret.push_back(0);
    if (peptide.empty()) {
        return ret;
    }
    ret.push_back(accumulate(peptide.begin(), peptide.end(), 0));

    vector<int> expandedPeptide = peptide;
    for (int val : peptide) {
        expandedPeptide.push_back(val);
    }
    int len = (int)peptide.size();
    for (int i = 0; i < len; ++i) {
        for (int j = 1; j < len; ++j) {
            ret.push_back(accumulate(expandedPeptide.begin() + i, expandedPeptide.begin() + i + j, 0));
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

// Проверка линеного спектра
bool checkLinearSpectrum() {
    vector<int> linearSpectrum = getLinearSpectrum(currentPeptide);
    multiset<int> spectrum(inputSpectrum.begin(), inputSpectrum.end());
    for (int value : linearSpectrum) {
        auto it = spectrum.find(value);
        if (it == spectrum.end()) {
            return false;
        }
        spectrum.erase(it);
    }
    return true;
}

// Проверка Cyclospectrum(Peptide) = inputSpectrum
bool checkCycloSpectrum() {
    return getCycloSpectrum(currentPeptide) == inputSpectrum;
}

// Перебор всех возможным пептидов с отсечением по текущему линейному спектру
void bruteforce() {
    if (!checkLinearSpectrum()) {
        return;
    }
    if (checkCycloSpectrum()) {
        answer.push_back(currentPeptide);
        return;
    }

    for (int weight : weights) {
        currentPeptide.push_back(weight);
        bruteforce();
        currentPeptide.pop_back();
    }
}

// Вывод ответа
void printAnswer() {
    bool needSpace = false;
    for (const vector<int> &vec : answer) {
        if (needSpace) cout << " ";
        bool needHyphen = false;
        for (int val : vec) {
            if (needHyphen) cout << "-";
            cout << val;
            needHyphen = true;
        }
        needSpace = true;
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Входные данные
    inputSpectrum = inputVector();

    // solution
    bruteforce();

    // Вывод результата
    printAnswer();




#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};