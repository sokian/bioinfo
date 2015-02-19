/**
* Решение за O(2^n)
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

void printSolution(vector<int> points) {
    sort(points.begin(), points.end());
    for (int x : points) {
        cout << x << " ";
    }
    cout << endl;
}

void nextPoint(int newPoint, vector<int> points, multiset<int> dist);

void turnpikeSolver(vector<int> points, multiset<int> dist) {
    if (dist.empty()) {
        printSolution(points);
        exit(0);
    }
    int left = points[0], right = points[1];
    int maxDist = *dist.rbegin();
    int newPoint;

    // попробуем поставить эту точку налево
    newPoint = right - maxDist;
    nextPoint(newPoint, points, dist);

    // попробуем поставить точку направо
    newPoint = left + maxDist;
    nextPoint(newPoint, points, dist);
}

void nextPoint(int newPoint, vector<int> points, multiset<int> dist) {
    for (int pt : points) {
        int d = abs(newPoint - pt);
        auto it = dist.find(d);
        if (it == dist.end()) return;
        dist.erase(it);
    }
    points.push_back(newPoint);
    turnpikeSolver(points, dist);
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Входные данные
    vector<int> dist = inputVector();

    // Только положительные расстояния
    vector<int> distances;
    for (int val : dist) {
        if (val > 0) {
            distances.push_back(val);
        }
    }

    vector<int> initialPoints(1, 0);
    initialPoints.push_back(distances.back());
    multiset<int> distancesDict(distances.begin(), distances.end() - 1);

    // Запустить перебор
    turnpikeSolver(initialPoints, distancesDict);

    // Если дошли до этого не вышли
    cout << "NO SOLUTION" << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};