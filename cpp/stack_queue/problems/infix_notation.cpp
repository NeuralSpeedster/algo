#include <bits/stdc++.h>

using namespace std;


bool IS_VALID_EXPRESSION = true;

bool is_operation(char ch) {
    return ch == '+' || ch == '-' || ch == '*';
}

int evaluate_from_pn(const string &s) {
    return 0;
}


unordered_map<char, unsigned short> OPERATIONS_PRIOR = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
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
               isdigit(s.at(i + j))) {
            operand += s.at(i + j);
            j++;
        }
        if (j > 0) {
            i += j - 1;
            cout << operand << " ";
            res += operand + " ";
            continue;
            /* цикл остановился либо в конце строки, либо на первом символе,
            не являющимся цифрой, тогда (инклюзивно) s[i, i+j] = operand
            */
        }

        // Операция выталкивает из стека все операции с больше либо равным приоритетом и кладётся в стек
        if (is_operation(s.at(i))) {
            while (!st.empty() && OPERATIONS_PRIOR[s.at(i)] <= OPERATIONS_PRIOR[st.top()]) {
                res += st.top();
                res += " ";
                st.pop();
            }
            st.push(s.at(i));
        } else if (s.at(i) == '(') {
            st.push('(');
        } else if (s.at(i) == ')') { // закр скобка выталкивает в ответ все операции до закрывающей скобки и удаляет открывающую
            while (!st.empty() && is_operation(st.top())) {
                res += st.top();
                res += " ";
                st.pop();
            }
            if (!st.empty() && st.top() == '(') {
                st.pop();
            } else { // не соответствуют скобки
                IS_VALID_EXPRESSION = false;
            }
        }
        else { // неизвестные символы
            IS_VALID_EXPRESSION = false;
        }
    }
    while (!st.empty()) {
        res += st.top();
        res += " ";
        st.pop();
    }
    cout << "\nRes: " << res << "\n";
    return res;
}

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression = "1+a+1";
    //getline(cin, expression);

    string result_postfix = convert_to_prn(expression);
    if (IS_VALID_EXPRESSION) {
        cout<<evaluate_from_pn(result_postfix);
    }
    else {
        cout<<"WRONG";
    }
    return 0;
}