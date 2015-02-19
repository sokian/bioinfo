/**
* Решение - реализация того что в условии написано
*/

#include "bits/stdc++.h"

using namespace std;

// Веса amino acids
vector<int> weights;

void fillWeightsWithConvolution(const vector<int> &spectrum, int M) {
    multiset<int> conv;
    set<int> convSet;
    for (int v1 : spectrum) {
        for (int v2 : spectrum) {
            if (v2 > v1) {
                conv.insert(v2 - v1);
                convSet.insert(v2 - v1);
            }
        }
    }
    map<int, vector<int>, greater<int> > convolution;
    for (int mass : convSet) {
        // Это условие не занаю почему
        if (mass >= 57 && mass <= 200)
            convolution[conv.count(mass)].push_back(mass);
    }

    for (pair<int, vector<int> > pivi : convolution) {
        cerr << pivi.first << " : ";
        for (int q : pivi.second) {
            cerr << q << " ";
        }
        cerr << endl;
    }
    cerr << endl;

    while (weights.size() < M && !convolution.empty()) {
        for (int val : convolution.begin()->second) {
            weights.push_back(val);
        }
        convolution.erase(convolution.begin());
    }
}

vector<int> inputVector() {
    vector<int> ret;
    int x;
    while (cin >> x) {
        ret.push_back(x);
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

int getMass(const vector<int> &peptide) {
    return accumulate(peptide.begin(), peptide.end(), 0);
}

int getParentMass(const vector<int> &spectrum) {
    return *max_element(spectrum.begin(), spectrum.end());
}

int getScore(const vector<int> &peptide, const vector<int> &spectrum) {
    vector<int> peptideSpectrum = getCycloSpectrum(peptide);
    multiset<int> spec(spectrum.begin(), spectrum.end());

    int score = 0;
    for (int val : peptideSpectrum) {
        auto it = spec.find(val);
        if (it != spec.end()) {
            score++;
            spec.erase(it);
        }
    }
    return score;
}

vector<vector<int> > cut(const vector<vector<int> > &leaderboard, const vector<int> &spectrum, int N) {
    vector<pair<int, vector<int> > > leaderboardWithScore;
    for (const vector<int> &peptide : leaderboard) {
        leaderboardWithScore.push_back(make_pair(getScore(peptide, spectrum), peptide));
    }
    sort(leaderboardWithScore.begin(), leaderboardWithScore.end(), greater<pair<int, vector<int> > >());
    vector<vector<int> > newLeaderboard;
    int index = 0;
    while (index < leaderboardWithScore.size() && (newLeaderboard.size() <= N || leaderboardWithScore[N - 1].first <= leaderboardWithScore[index].first)) {
        newLeaderboard.push_back(leaderboardWithScore[index].second);
        ++index;
    }
    return newLeaderboard;
}

vector<vector<int> > expand(const vector<vector<int> > &peptides) {
    vector<vector<int> > newPeptides;
    for (const vector<int> &peptide : peptides) {
        for (int mass : weights) {
            vector<int> addPeptide = peptide;
            addPeptide.push_back(mass);
            newPeptides.push_back(addPeptide);
        }
    }
    return newPeptides;
}

vector<int> leaderboardCyclopeptideSequencing(const vector<int> &spectrum, int N) {
    vector<vector<int> > leaderboard;
    leaderboard.push_back(vector<int>());
    vector<int> leaderPeptide;
    int leaderScore = getScore(leaderPeptide, spectrum);
    int parentMass = getParentMass(spectrum);

    while (!leaderboard.empty()) {
        leaderboard = expand(leaderboard);
        vector<vector<int> > newLeaderboard;
        for (const vector<int> &peptide : leaderboard) {
            if (getMass(peptide) < parentMass) {
                newLeaderboard.push_back(peptide);
            } else {
                if (getMass(peptide) == parentMass) {
                    int peptideScore = getScore(peptide, spectrum);
                    if (peptideScore > leaderScore) {
                        leaderPeptide = peptide;
                        leaderScore = peptideScore;
                    }
                }
            }
        }
        leaderboard = cut(newLeaderboard, spectrum, N);
    }
    return leaderPeptide;
}

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
    int n;
    cin >> n;
    vector<int> inputSpectrum = inputVector();

    // Заполняем веса
    fillWeightsWithConvolution(inputSpectrum, m);

    for (int val : weights) {
        cerr << val << " ";
    }
    cerr << endl;

    // leader peptide
    vector<int> peptide = leaderboardCyclopeptideSequencing(inputSpectrum, n);

    // Вывод результата
    for (int i = 0; i < peptide.size(); ++i) {
        if (i) cout << "-";
        cout << peptide[i];
    }
    cout << endl;


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};