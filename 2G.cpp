/**
* Решение за О(n^2 * log(ans)), где n - число элементов в спектре
*/

#include "bits/stdc++.h"

using namespace std;

vector<int> inputVector() {
    vector<int> ret;
    int x;
    while (cin >> x) {
        ret.push_back(x);
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Ввод данных
    vector<int> spectrum = inputVector();

    // element and it's multiplicity
    map<int, int> convolution;
    for (int v1 : spectrum) {
        for (int v2 : spectrum) {
            if (v2 > v1) {
                convolution[v2 - v1]++;
            }
        }
    }
    vector<pair<int, int> > convolutionElements;
    for (const pair<int, int> &pii : convolution) {
        convolutionElements.push_back(make_pair(pii.second, pii.first));
    }
    // Сортируем по multiplicity потом по значению
    sort(convolutionElements.begin(), convolutionElements.end(),
            [](const pair<int, int> &l, const pair<int, int> &r){
                if (l.first != r.first) {
                    return l.first > r.first;
                }
                return l.second < r.second;
            });

    // Вывод результата
    for (const pair<int, int> &pii : convolutionElements) {
        for (int i = 0; i < pii.first; ++i) {
            cout << pii.second << " ";
        }
    }
    cout << endl;


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};