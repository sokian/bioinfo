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
    int counter;        // число вхождений строки соответствующей данному состоянию автомата
    map<char, int> next;// переходы храним в map'e можно хранить в массиве размером алфавита
                        // так универсальнее (добавляет в асимптотику log(AlphabetSize))

    State(int len, int link) : len(len), link(link) {
        counter = 0;
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
private:
    // Состояния автомата храним в векторе
    vector<State> states;
    // Последнее состояние, соответствующее самому длинному текущему суффиксу
    int lastState = 0;
    // Длина максимального суффикса
    int maxLength;

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
};



int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string data;
    cin >> data;
    int length;
    cin >> length;


    // Построение суффиксного автомата
    SuffixAutomaton sa(data);

    // Находим состояния с максимальным количеством вхождений в исходную строку длины не меньше length
    vector<int> maxStates;
    int maxOccurrence = -1;
    for (int i = 0; i < sa.size(); ++i) {
        State st = sa.getState(i);
        if (st.len < length) {
            continue;
        }
        if (st.counter > maxOccurrence) {
            maxOccurrence = st.counter;
            maxStates.clear();
        }
        if (st.counter == maxOccurrence) {
            maxStates.push_back(i);
        }
    }

    // Вывод ответа
    bool whitespace = false;
    for (int state : maxStates) {
        int firstPosition = sa.getState(state).firstPosition;
        if (whitespace) cout << " ";
        cout << data.substr(firstPosition - length + 1, length);
        whitespace = true;
    }
    cout << endl;

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};