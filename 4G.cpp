/**
* Решение за O(input * log(input))
* Построим граф де брейна и найдем в нем эйлеров путь
*/

#include "bits/stdc++.h"

using namespace std;

vector<string> readVectorString()  {
    vector<string> ret;
    string s;
    while (cin >> s) {
        ret.push_back(s);
    }
    return ret;
}

vector<string> dict;

void makeDictionary(const vector<string> &vs) {
    for (const string &s : vs) {
        dict.push_back(s.substr(0, s.length() - 1));
        dict.push_back(s.substr(1));
    }
    sort(dict.begin(), dict.end());
    dict.resize(unique(dict.begin(), dict.end()) - dict.begin());
}

int getIdOfString(const string &s) {
    return lower_bound(dict.begin(), dict.end(), s) - dict.begin();
}

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
pair<bool, int> checkForEulerPath(const vector<vector<int> > &graph) {
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
        return make_pair(false, -1);
    }

    int start = 0;
    vector<char> visited(graph.size(), 0);
    for (int i = 0; i < (int)graph.size(); ++i) {
        if (numberOfOddVertices) {
            if (graph[i].size() > (int)degree[i] / 2) {
                start = i;
                dfs(i, graph, visited);
                break;
            }
        } else {
            if (degree[i] > 0) {
                start = i;
                dfs(i, graph, visited);
                break;
            }
        }
    }

    for (int i = 0; i < (int)graph.size(); ++i) {
        if (graph[i].size() > 1 && !visited[i]) {
            return make_pair(false, -1);
        }
    }
    return make_pair(true, start);
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


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //Ввод данных
    int len;
    cin >> len;
    vector<string> vs = readVectorString();
    if (vs.empty()) {
        return 0;
    }

    // Занумеруем k-1-mers
    makeDictionary(vs);

    // Создание графа
    vector<vector<int> > graph(dict.size());
    for (const string &s : vs) {
        graph[getIdOfString(s.substr(0, len - 1))].push_back(getIdOfString(s.substr(1)));
    }


    // Проверка графа на эйлеровость
    auto pbi = checkForEulerPath(graph);
    if (!pbi.first) {
        cout << "NO EULER PATH" << endl;
        return 0;
    }

    // Нахождение эйлерова пути
    int start = pbi.second;
    vector<int> path;
    findEulerPath(start, graph, path);

    // Вывод результата
    // Первую строку
    cout << dict[path.front()];
    // Далее только по одному символу
    for (int i = 1; i < (int)path.size(); ++i) {
        cout << dict[path[i]].back();
    }
    cout << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

