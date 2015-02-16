/**
* Решение за O(length(inputString)) + вывод ответа (асимптотически оптимальное решение)
* Используется структура данных - суффиксный автомат (подробнее на http://e-maxx.ru/algo/suffix_automata)
*/

#include "bits/stdc++.h"

using namespace std;

// Структура состояния суффиксного автомата
struct State {
    int len;            // длина суффикса
    int link;           // суффиксная ссылка
    int firstPosition;  // позиция окончания суффикса соответстующего данному состоянию автомата
    bool isClone;       // флаг, получено ли состояние путем клонирования
    map<char, int> next;// переходы храним в map'e можно хранить в массиве размером алфавита
    // так универсальнее (добавляет в асимптотику log(AlphabetSize))

    State(int len, int link) : len(len), link(link), firstPosition(len - 1), isClone(false) {
    }

    // добавить новый переход по символу c
    void addNext(char c, int nextState) {
        next[c] = nextState;
    }

    // проверить есть ли переход по символу c
    bool hasNext(char c) const {
        return (bool)next.count(c);
    }

    // номер состояния соответствующего переходу по символу с
    int getNext(char c) const {
        if (next.count(c)) {
            return next.at(c);
        } else {
            return -1;
        }
    }
};

// Класс построения суффиксного автомата для данной строки
// После построения выполняет подсчет количества вхождений
class SuffixAutomaton {
public:
    // Конструктор от строки
    SuffixAutomaton(const string &s) {
        // Инициализация автомата создание стартового состояния (пустой строки)
        init();
        // Построение (добавление посимвольное строки)
        for (char c : s) {
            addCharacter(c);
        }

        // построение дерева суффиксных ссылок
        makeTree();
    }
    // Количество состояний автомата
    int size() const {
        return int(states.size());
    }

    // Вернуть ссылку на pos-ое состояние автомата
    const State& getState(int pos) const {
        return states[pos];
    }
    // Возвращаем состояние в которое переходит автомат по данной строке, или -1 если такую строку автомат не принимает
    // то есть данная строка не встречается в исходной строке как подстрока
    int getState(const string &s) const {
        int currentState = 0;
        for (char c : s) {
            if (states[currentState].hasNext(c)) {
                currentState = states[currentState].getNext(c);
            } else {
                return -1;
            }
        }
        return currentState;
    }

    // Состояния достижимые из данного состояния по обратным суффиксным ссылкам
    // Только в таких состояния может появиться новое вхождение строки s, переводящей автомат в состояние state
    // Количество таких состояний О(числа вхождений строки s) (их не более чем в 2 раза больше)
    vector<int> statesReachableByLinks(int state) const {
        vector<int> visited;
        depthFirstSearchOnTree(state, visited);
        return visited;
    }

    // Возвращает позиции вхождения строки s в исходную строку
    vector<int> getOccurrences(const string &s) const {
        int state = getState(s);
        vector<int> visitedStates = statesReachableByLinks(state);
        vector<int> positions;
        int length = int(s.length());
        // Если состояние получено не путем клонирование, то это состояние соответствует очередному вхождению строки s
        for (int visitedState : visitedStates) {
            if (!getState(visitedState).isClone) {
                positions.push_back(getState(visitedState).firstPosition - length + 1);
            }
        }
        return positions;
    }
private:
    // Состояния автомата храним в векторе
    vector<State> states;
    // Последнее состояние, соответствующее самому длинному текущему суффиксу
    int lastState = 0;
    // Здесь храним дерево суффикных ссылок (точнее обратных суффиксных ссылок)
    // храним в виде списков смежности
    vector<vector<int> > tree;
    // Временный вектор хранящий посещенные dfs вершины дерева
    vector<int> visited;

    // Инициализация
    void init() {
        states.push_back(State(0, -1));
        lastState = 0;
    }

    // Добавление очередного символа строки
    void addCharacter(char c) {
        // Добавляем новое состояние, соответствующее самому длинному суффиксу, оканчивающемуся на данный символ
        states.push_back(State(states[lastState].len + 1, -1));
        int currentState = (int)states.size() - 1;

        // Далее вычисляется суффиксная ссылка для данного состояния
        // Суффиксная ссылка - состояние автомата, которому соответствует наидлиннейший суффикс строки w,
        // находящийся в другом классе endpos-эквивалентности (с другим количеством вхождения в исходную строку)
        int prevState;
        for (prevState = lastState; prevState != -1 && !states[prevState].hasNext(c); prevState = states[prevState].link) {
            states[prevState].addNext(c, currentState);
        }
        if (prevState == -1) {
            // Если дошли до корня и не встретили перехода по текущему символу
            states[currentState].link = 0;
        } else {
            // Первый переход по текущему символу, найденный при подъеме
            int linkState = states[prevState].getNext(c);
            if (states[prevState].len + 1 == states[linkState].len) {
                // Если переход (prevState, linkState) - "сплошной"
                states[currentState].link = linkState;
            } else {
                // В противном случае необходимо склонировать состояние linkState и сделать переход "сплошным"
                states.push_back(states[linkState]);
                int cloneState = (int)states.size() - 1;
                states[cloneState].len = states[prevState].len + 1;
                // Перенаправляем переходы по текущему символу, ведущие в linkState, в cloneState
                for (; prevState != -1 && states[prevState].getNext(c) == linkState; prevState = states[prevState].link) {
                    states[prevState].addNext(c, cloneState);
                }
                // Выставляем правильные суффиксные ссылки у состояний linkState и currentState
                states[linkState].link = states[currentState].link = cloneState;
                states[cloneState].isClone = true;
            }
        }
        // Выставляем lastState
        lastState = currentState;
    }

    // Построение дерева обратных суффиксных ссылок
    void makeTree() {
        tree.assign(size(), vector<int>());
        for (int i = 1; i < size(); ++i) {
            int parentState = states[i].link;
            tree[parentState].push_back(i);
        }
    }

    // dfs обход дерева
    void depthFirstSearchOnTree(int state, vector<int> &visited) const {
        visited.push_back(state);
        for (int nextState : tree[state]) {
            depthFirstSearchOnTree(nextState, visited);
        }
    }
};


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Считывание исходных данных
    string pattern;
    cin >> pattern;
    string genome;
    cin >> genome;

    // Построение суффиксного автомата и получение позиций вхождения pattern в genome
    SuffixAutomaton sa(genome);
    vector<int> positions = sa.getOccurrences(pattern);

    // Вывод ответа
    // Можно было бы и не сортировать, но позыции вхождений могут следовать в произвольном порядке
    // Единственное место работающее не за линейное время от ответа и входных данных
    sort(positions.begin(), positions.end());
    for (int x : positions) {
        cout << x << " ";
    }
    cout << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};