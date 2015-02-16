/**
* Решение - стандартная задача о рюкзаке
*/

#include "bits/stdc++.h"

using namespace std;

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

// Считать vector<int> из стандартного ввода разделенных запятой
vector<int> readVectorInt() {
    string line;
    cin >> line;
    vector<string> splited = split(line, ',');
    vector<int> ret;
    for (const string &s : splited) {
        ret.push_back(stoi(s));
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

    //Ввод данных
    int money;
    cin >> money;
    vector<int> coins = readVectorInt();

    int minCoin = *min_element(coins.begin(), coins.end());
    int numberOfIterations = money / minCoin + 1;


    vector<char> dp(money + 1, 0);
    dp[0] = 1;
    // Пыьаемся набрать нужную сумму за i монет
    for (int i = 0; i <= numberOfIterations; ++i) {
        if (dp[money]) {
            cout << i << endl;
            return 0;
        }
        // Добавляем еще 1 монету, за i + 1
        vector<char> cur(money + 1, false);
        for (int j = 0; j <= money; ++j) {
            for (int coin : coins) {
                if (j - coin >= 0) {
                    cur[j] |= dp[j - coin];
                }
            }
        }
        dp = cur;
    }
    // Если набрать нужную сумму не удалось
    cout << "impossible" << endl;


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}

