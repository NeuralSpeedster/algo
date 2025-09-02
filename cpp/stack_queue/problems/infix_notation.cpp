#include <bits/stdc++.h>

using namespace std;

int evaluate_from_pn(const string &s) {
    return 0;
}

unordered_map<char,  unsigned short> OPERATIONS_PRIOR = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    //{'(', 0},
};

string convert_to_prn(const string &s) {
    stack<char> st;
    string res;

    for (unsigned int i = 0; i < s.length(); i++) {
        if (s.at(i) == ' ') {
            continue;
        }
        // 1. Операнд сразу попадает в ответ
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
            res.append(operand + " ");
            continue;
            /* цикл остановился либо в конце строки, либо на первом символе,
            не являющимся цифрой, тогда (инклюзивно) s[i, i+j] = operand
            */
        }

        //

    }
    cout<<"\nRes: "<<res<<"\n";
    return res;
}

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression = " 12 + 456";
    //getline(cin, expression);

    string result_postfix = convert_to_prn(expression);
    return evaluate_from_pn(result_postfix);
}