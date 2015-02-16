/**
* Решение - динамика по DAG наидлиннейший путь до стока из вершины v - pathLength[v] и следующая вершина в этом пути nextVertex[v]
* Ассимптотика O(numberOfVerticies + numberOfEdges)
*/

#include "bits/stdc++.h"

using namespace std;

struct Edge {
    int from, to, len;
    Edge(){}
    Edge(int from, int to, int len) : from(from), to(to), len(len) {}
};

// Считывание ребер графа
vector<Edge> readEdges() {
    vector<Edge> ret;
    string line;
    while (cin >> line) {
        int from = stoi(line.substr(0, line.find('-')));
        int to   = stoi(line.substr(line.find('>') + 1, line.find(':') - line.find('>') - 1));
        int len  = stoi(line.substr(line.find(':') + 1));
        ret.push_back(Edge(from, to, len));
    }
    return ret;
}

// Построение графа
vector<vector<Edge> > getGraph(const vector<Edge> &edges) {
    vector<vector<Edge> > graph;
    int maxVertex = -1;
    for (const Edge &e : edges) {
        maxVertex = max(maxVertex, e.from);
        maxVertex = max(maxVertex, e.to);
    }
    graph.resize(maxVertex + 1);
    for (const Edge &e : edges) {
        graph[e.from].push_back(e);
    }
    return graph;
}

// DAG
vector<vector<Edge> > g;
vector<int> pathLength;
vector<int> nextVertex;

// наидлиннейший путь из vertex в sink
int getLongestPath(int vertex) {
    int &res = pathLength[vertex];
    int &nv  = nextVertex[vertex];

    if (res != -1) {
        return res;
    }

    for (const Edge &e : g[vertex]) {
        int len = getLongestPath(e.to);
        if (len == INT_MAX) continue;
        len += e.len;
        if (len > res) {
            res = len;
            nv = e.to;
        }
    }
    if (res == -1) {
        res = INT_MAX;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Ввод данных
    int source, sink;
    cin >> source >> sink;
    vector<Edge> edges = readEdges();
    g = getGraph(edges);
    // -1 - непосчитанное значение динамики
    pathLength.assign(g.size(), -1);
    nextVertex.assign(g.size(), -1);
    pathLength[sink] = 0;

    // Посчитаем ответ и восстановим путь
    int longestPath = getLongestPath(source);
    vector<int> path;
    int currentVertex = source;
    path.push_back(currentVertex);
    while (currentVertex != sink) {
        currentVertex = nextVertex[currentVertex];
        path.push_back(currentVertex);
    }


    // Вывод результата
    cout << longestPath << endl;
    for (int i = 0; i < int(path.size()); ++i) {
        if (i) cout << "->";
        cout << path[i];
    }
    cout << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

