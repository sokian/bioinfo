/**
* Решение - для все возможных k-mers найдем их d(pattern, dnas) и выберем минимальный
*/

#include "bits/stdc++.h"

using namespace std;

vector<string> inputVectorString() {
    vector<string> ret;
    string s;
    while (cin >> s) {
        ret.push_back(s);
    }
    return ret;
}

vector<char> alphabet = {'A', 'C', 'G', 'T'};
map<char, int> alphaToInt;

void prepareAlphabet() {
    for (int i = 0; i < alphabet.size(); ++i) {
        alphaToInt[alphabet[i]] = i;
    }
}

double calculateProbability(const string &kmer, const vector<vector<double> > &profile) {
    double result = 1;
    for (int i = 0; i < kmer.length(); ++i) {
        result *= profile[alphaToInt[kmer[i]]][i];
    }
    return result;
}


string findMostProbableKmer(const string &text, int k, const vector<vector<double> > &profile) {
    string mostProbableKmer = text.substr(0, k);
    double mostProbability = 0;

    for (int index = 0; index + k <= text.length(); ++index) {
        string kmer = text.substr(index, k);
        double probability = calculateProbability(kmer, profile);
        if (mostProbability < probability) {
            mostProbability = probability;
            mostProbableKmer = kmer;
        }
    }
    return mostProbableKmer;
}


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    prepareAlphabet();

    // Ввод данных
    string text;
    cin >> text;
    int k;
    cin >> k;
    vector<vector<double> > profile(4, vector<double>(k, 0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> profile[i][j];
        }
    }

    string mostProbableKmer = findMostProbableKmer(text, k, profile);

    // Вывод результата
    cout << mostProbableKmer << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};