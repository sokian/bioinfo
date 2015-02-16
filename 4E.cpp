/**
* Решение за O(числа ребер)
* Подробнее поиск эйлерова цикла http://neerc.ifmo.ru/wiki/index.php?title=Алгоритм_построения_Эйлерова_цикла
*/

#include <winsock.h>
#include "bits/stdc++.h"

using namespace std;


// Обход в глубину
void dfs(int v, const vector<vector<int> > &graph, vector<char> &visited) {
    visited[v] = 1;
    for (int to : graph[v]) {
        if (!visited[to]) {
            dfs(to, graph, visited);
        }
    }
}

// Проверка на существование Эйлерова пути
bool checkForEulerPath(const vector<vector<int> > &graph) {
    int numberOfOddVertices = 0;
    vector<int> degree(graph.size(), 0);
    for (size_t i = 0; i < graph.size(); ++i) {
        for (int to : graph[i]) {
            degree[i]++;
            degree[to]++;
        }
    }

    for (size_t i = 0; i < graph.size(); ++i) {
        if (degree[i] % 2 == 1) {
            numberOfOddVertices++;
        }
    }
    if (numberOfOddVertices > 2) {
        return false;
    }

    vector<char> visited(graph.size(), 0);
    for (int i = 0; i < (int)graph.size(); ++i) {
        if (degree[i] > 0) {
            dfs(i, graph, visited);
            break;
        }
    }

    for (int i = 0; i < (int)graph.size(); ++i) {
        if (graph[i].size() > 1 && !visited[i]) {
            return false;
        }
    }
    return true;
}

// Наути эйлеров путь. Стандартный алгоритм, ссылка вверху
void findEulerPath(int start, const vector<vector<int> > &graph, vector<int> &path) {
    stack<int> st;
    st.push(start);
    vector<int> idEdge(graph.size(), 0);

    while (!st.empty()) {
        int v = st.top();
        if (idEdge[v] < (int)graph[v].size()) {
            st.push(graph[v][idEdge[v]++]);
        } else {
            st.pop();
            path.push_back(v);
        }
    }
    reverse(path.begin(), path.end());
}

//break a sentence into words by delim
std::vector<std::string> split(const std::string& s, char delim = ' '){
    typedef std::string::const_iterator iter;
    std::vector<std::string> ret;
    iter i = s.begin();
    while(i!=s.end()){
        i = std::find_if(i, s.end(), [&](char c){return c != delim;}); // find the beginning of a word
        iter j= std::find_if(i, s.end(), [&](char c){return c == delim;}); // find the end of the same word
        if(i != s.end()){
            ret.push_back(std::string(i, j)); //insert the word into vector
            i = j; // repeat 1,2,3 on the rest of the line.
        }
    }
    return ret;
}

// Распарсить вершины из строки
void parseVertices(vector<int> &vec, const string &vertices) {
    vector<string> splited = split(vertices, ',');
    for (const string &s : splited) {
        vec.push_back(stoi(s));
    }
}

// Распарсить граф
void parseGraph(vector<vector<int> > &graph) {
    string line;
    vector<pair<int, vector<int> > > adjacencyList;
    while (cin >> line) {
        int from = stoi(line);
        adjacencyList.push_back(make_pair(from, vector<int>()));
        string toVertices;
        cin >> toVertices >> toVertices;
        parseVertices(adjacencyList.back().second, toVertices);
    }
    graph.assign(adjacencyList.size(), vector<int>());
    for (const pair<int, vector<int> > &pivi : adjacencyList) {
        int from = pivi.first;
        for (int to : pivi.second) {
            graph[from].push_back(to);
        }
    }
}


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int> > graph;
    parseGraph(graph);

    if (!checkForEulerPath(graph)) {
        cout << "NO EULER PATH" << endl;
        return 0;
    }

    vector<int> path;
    findEulerPath(0, graph, path);

    // Вывод результата
    bool needPointer = false;
    for (int v : path) {
        if (needPointer) cout << "->";
        cout << v;
        needPointer = true;
    }

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};