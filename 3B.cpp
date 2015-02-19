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

string currentKmer;
void generateAllKmers(int k, vector<string> &kmers) {
    if (k == 0) {
        kmers.push_back(currentKmer);
        return;
    }
    for (char c : alphabet) {
        currentKmer.push_back(c);
        generateAllKmers(k - 1, kmers);
        currentKmer.pop_back();
    }
}

// Расстояние до одной dna-строки
int distance(const string &pattern, const string &text) {
    int minimalDistance = INT_MAX;
    for (int start = 0; start + pattern.length() <= text.length(); ++start) {
        int currentDistance = 0;
        for (int index = 0; index < pattern.length(); ++index) {
            if (pattern[index] != text[start + index]) {
                ++currentDistance;
            }
        }
        minimalDistance = min(minimalDistance, currentDistance);
    }
    return minimalDistance;
}

// Суммарное растояние до всех dna-строк
int distance(const string &pattern, const vector<string> &dnas) {
    int result = 0;
    for (const string &dna : dnas) {
        result += distance(pattern, dna);
    }
    return result;
}


// Найти медианный kmer (полный перебоп всех kmers)
string findMedianKmer(int k, const vector<string> &dnas) {
    string bestKmer;
    int bestDistance = INT_MAX;

    vector<string> kmers;
    generateAllKmers(k, kmers);

    for (const string &kmer : kmers) {
        int currentDistance = distance(kmer, dnas);
        if (currentDistance < bestDistance) {
            bestDistance = currentDistance;
            bestKmer = kmer;
        }
    }
    return bestKmer;
}


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Ввод данных
    int k;
    cin >> k;
    vector<string> dnas = inputVectorString();


    string median = findMedianKmer(k, dnas);


    // Вывод результата
    cout << median << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};