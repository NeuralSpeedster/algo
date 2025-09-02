#include <bits/stdc++.h>

using namespace std;


bool IS_VALID_EXPRESSION = true;

bool is_operation(char ch) {
    return ch == '+' || ch == '-' || ch == '*';
}

int evaluate_from_prn(const string &s) {
    return 0;
}


string preprocess_expr(const string &s) {
    string result;
    if (!s.empty() && s[0] == '-') {
        result = "0";
    }
    for (const auto &c : s) {
        result += c;
        if (c == '(') {
            result += '0';
        }
    }
    return result;
}


unordered_map<char, unsigned short> OPERATIONS_PRIOR = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
};

string convert_to_prn(const string &s) {
    stack<char> st;
    string res;
    bool is_prev_operand = false;

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
            if (is_prev_operand) {
                IS_VALID_EXPRESSION = false;
                return "";
            }
            i += j - 1;
            cout << operand << " ";
            res += operand + " ";
            is_prev_operand = true;
            continue;
            /* цикл остановился либо в конце строки, либо на первом символе,
            не являющимся цифрой, тогда (инклюзивно) s[i, i+j] = operand
            */
        }
        is_prev_operand = false;

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
                return "";
            }
        }
        else { // неизвестные символы
            IS_VALID_EXPRESSION = false;
            return "";
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

    string expression = "-6 * (-8)";
    //getline(cin, expression);

    string processed_expr = preprocess_expr(expression);
    cout<<processed_expr<<endl;
    string result_postfix = convert_to_prn(processed_expr);

    if (IS_VALID_EXPRESSION) {
        cout<<evaluate_from_prn(result_postfix);
    }
    else {
        cout<<"WRONG";
    }
    return 0;
}