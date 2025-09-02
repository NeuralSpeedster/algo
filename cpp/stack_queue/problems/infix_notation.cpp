#include <bits/stdc++.h>

using namespace std;

int evaluate_from_pn(const string &s) {
    return 0;
}

using Element = std::variant<int, char>;

unordered_map<char,  unsigned short> OPERATIONS_PRIOR = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    //{'(', 0},
};

string convert_to_pn(const string &s) {
    stack<Element> st;
    string res;
    res = "1";

    for (unsigned int i = 0; i < s.length(); i++) {
        if (s.at(i) == ' ') {
            continue;
        }
        // 1. Операнд сразу попадает в стек
        // находим операнд
        unsigned int j = 0;
        string operand;
        while (i + j < s.length() &&
            isdigit(s.at(i+j))) {
            operand += s.at(i + j);
            j++;
        }
        if (j > 0) {
            i += j - 1;
            cout<<operand<<" ";
            st.emplace(stoi(operand));
            continue;
            /* цикл остановился либо в конце строки, либо на первом символе,
            не являющимся цифрой, тогда (инклюзивно) s[i, i+j] = operand
            */
        }

        //

    }
    return res;
}

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression = " 12 + 456";
    //getline(cin, expression);

    string result_postfix = convert_to_pn(expression);
    return evaluate_from_pn(result_postfix);
}