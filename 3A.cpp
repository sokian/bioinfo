/**
* Решение - найдем все возможные k-mers с d ошибками и для каждого из них найдем количество вхождений.
* Используется структура данных - суффиксный автомат (подробнее на http://e-maxx.ru/algo/suffix_automata)
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
    // Мап переходов
    const map<char, int> & getNextMap() const {
        return next;
    }
};

// Структура состояния суффиксного автомата
class SuffixState : public State {
// Лучше бы эти поля сделать приватными
public:
    int len;            // длина суффикса
    int link;           // суффиксная ссылка
    int firstPosition;  // позиция окончания суффикса соответстующего данному состоянию автомата
    int counter;        // число вхождений строки соответствующей данному состоянию автомата
    bool isClone;       // флаг, получено ли состояние путем клонирования

    SuffixState(int len, int link) : len(len), link(link), firstPosition(len - 1), isClone(false) {
    }
};

// Класс построения суффиксного автомата для данной строки
// После построения выполняет подсчет количества вхождений
class SuffixAutomaton {
public:
    // Пустой конструктор
    SuffixAutomaton() {}

    // Конструктор от строки
    SuffixAutomaton(const string &s) {
        // Инициализация автомата создание стартового состояния (пустой строки)
        init();
        // Построение (добавление посимвольное строки)
        maxLength = (int)s.length();
        for (char c : s) {
            addCharacter(c);
        }
        // Подсчет количества вхождений каждого суффикса строки
        calculateNumberOfOccurrences();
    }
    // Количество состояний автомата
    int size() const {
        return int(states.size());
    }

    // Вернуть ссылку на pos-ое состояние автомата
    const State& getState(int pos) const {
        return states[pos];
    }

    bool contains(const string &pattern, int numberOfMismatches) const {
        return contains(0, 0, pattern, numberOfMismatches);
    }
private:
    // Состояния автомата храним в векторе
    vector<SuffixState> states;
    // Последнее состояние, соответствующее самому длинному текущему суффиксу
    int lastState = 0;
    // Длина максимального суффикса
    int maxLength;

    // Инициализация
    void init() {
        states.push_back(SuffixState(0, -1));
        lastState = 0;
    }

    // Добавление очередного символа строки
    void addCharacter(char c) {
        // Добавляем новое состояние, соответствующее самому длинному суффиксу, оканчивающемуся на данный символ
        states.push_back(SuffixState(states[lastState].len + 1, -1));
        int currentState = (int)states.size() - 1;
        states[currentState].firstPosition = states[currentState].len - 1;
        states[currentState].counter = 1;

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
                // Так как состояние получено путем клонирования его counter нужно обнулить
                states[cloneState].counter = 0;
            }
        }
        // Выставляем lastState
        lastState = currentState;
    }


    // Подсчет числа вхождений
    void calculateNumberOfOccurrences() {
        vector<int> vec[maxLength + 1];
        for (int i = 0; i < size(); ++i) {
            vec[states[i].len].push_back(i);
        }
        // Идем в порядке уменьшения длины суффиксов и прокидываем по суффиксной ссылке количество вхождений
        for (int i = maxLength; i > 0; --i) {
            for (int x : vec[i]) {
                states[states[x].link].counter += states[x].counter;
            }
        }
    }

    bool contains(int state, int position, const string &pattern, int mismatchesLost) const {
        if (mismatchesLost < 0) {
            return false;
        }
        if (position == pattern.length()) {
            return states[state].counter > 0;
        }
        bool ret = false;
        for (const pair<char, int> &to : states[state].getNextMap()) {
            if (to.first == pattern[position]) {
                ret = ret || contains(to.second, position + 1, pattern, mismatchesLost);
            } else {
                ret = ret || contains(to.second, position + 1, pattern, mismatchesLost - 1);
            }
            if (ret) {
                return ret;
            }
        }
        return ret;
    }
};

string currentMutation;
vector<char> alphabet = {'A', 'C', 'G', 'T'};

void fillMutations(int position, const string &s, int mismatches, set<string> &res) {
    if (mismatches < 0) {
        return;
    }
    if (position == s.length()) {
        res.insert(currentMutation);
        return;
    }
    for (char c : alphabet) {
        currentMutation.push_back(c);
        if (c == s[position]) {
            fillMutations(position + 1, s, mismatches, res);
        } else {
            fillMutations(position + 1, s, mismatches - 1, res);
        }
        currentMutation.pop_back();
    }
}

set<string> getMutations(const string &s, int mismatches) {
    set<string> ret;
    fillMutations(0, s, mismatches, ret);
    return ret;
}

set<string> extendDict(const set<string> &dict, int mismatches) {
    set<string> ret;
    for (string s : dict) {
        set<string> mutates = getMutations(s, mismatches);
        ret.insert(mutates.begin(), mutates.end());
    }
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
    int k, d;
    cin >> k >> d;
    vector<string> dnas = inputVectorString();

    // Заполним словарь k-mers
    set<string> dict;
    for (const string &text : dnas) {
        for (int i = 0; i + k <= text.length(); ++i) {
            dict.insert(text.substr(i, k));
        }
    }
    dict = extendDict(dict, d);

    // Построим суффикный автоматы
    vector<SuffixAutomaton> sas;
    for (const string &text : dnas) {
        sas.push_back(SuffixAutomaton(text));
    }

    // Надем самые популярные слова
    vector<string> kdmotifs;

    for (const string &s : dict) {
        bool containsInAllDna = true;
        for (const SuffixAutomaton &sa : sas) {
            containsInAllDna = containsInAllDna && sa.contains(s, d);
            if (!containsInAllDna) {
                break;
            }
        }
        if (containsInAllDna) {
            kdmotifs.push_back(s);
        }
    }


    // Вывод результата
    for (const string &s : kdmotifs) {
        cout << s << " ";
    }
    cout << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};