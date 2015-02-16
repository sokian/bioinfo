/**
* Решение за O(размер ввода)
*/

#include "bits/stdc++.h"

using namespace std;

// Класс состояния некоторого автомата
class State {
private:
    // Переходы по символам
    map<char, int> next;
public:
    State() {}
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

    const map<char, int> & nextMap() const {
        return next;
    }
};

// Класс бор
class Trie {
    class TrieState : public State {
    public:
        // Флаг окончания некоторой строки в данном состоянии
        bool isLast;
        TrieState() {
            isLast = false;
        }
    };

public:
    Trie() {
        init();
    }
    // Добавление строки в бор
    void addString(const string &s) {
        int currentState = 0;
        // Идем по переходам бора и добавляем новые состояния по мере необходимости
        for (char c : s) {
            // Если нет перехода по текущему символу добавляем новое состояние
            if (!states[currentState].hasNext(c)) {
                int newState = int(states.size());
                states.push_back(TrieState());
                states[currentState].addNext(c, newState);
            }
            currentState = states[currentState].getNext(c);
        }
        // Выставляем флаг об окончании некоторой строки в данном состоянии
        states[currentState].isLast = true;
    }
    // Выводим ответ тут
    void printEdges() {
        for (size_t i = 0; i < states.size(); ++i) {
            for (pair<char, int> pci : states[i].nextMap()) {
                cout << i + 1 << "->" << pci.second + 1 << ":" << pci.first << endl;
            }
        }
    }
private:
    vector<TrieState> states;
    void init() {
        states.push_back(TrieState());
    }
};

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    Trie trie;
    string pattern;
    while (cin >> pattern) {
        trie.addString(pattern);
    }
    trie.printEdges();

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};