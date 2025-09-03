#include <bits/stdc++.h>

using namespace std;


bool IS_VALID_EXPRESSION = true;

bool is_operation(char ch) {
    return ch == '+' || ch == '-' || ch == '*';
}

int evaluate_from_prn(const string &s) {
    stack<int> st;
    for (unsigned int i = 0; i < s.length(); i++) {
        unsigned int j = 0;
        string operand;
        while (i + j < s.length() &&
               isdigit(s.at(i + j))) {
            operand += s.at(i + j);
            j++;
        }
        if (j > 0) {
            i += j - 1;
            st.push(stoi(operand));
            continue;
        }
        if (is_operation(s[i])) {
            if (st.size() < 2) {
                IS_VALID_EXPRESSION = false;
                return 0;
            }
            int second = st.top();
            st.pop();
            int first = st.top();
            st.pop();

            switch (s[i]) {
                case '+':
                    st.push(first + second);
                    break;
                case '-':
                    st.push(first - second);
                    break;
                case '*':
                    st.push(first * second);
                    break;
                default:
                    break;
            }
        }
    }
    if (st.size() == 1) {
        return st.top();
    }

    IS_VALID_EXPRESSION = false;
    return 0;
}


string preprocess_expr(const string &s) {

    string result;
    size_t first_non_space = s.find_first_not_of(' ');
    if (first_non_space != string::npos) {
        if (s.at(first_non_space) == '-') {
            result = "0";
        }
        else {
            result = "";
        }
    }

    bool is_prev_operation = false;
    bool is_prev_opening_bracket = (s.at(first_non_space) == '(');

    size_t pos = 0;
    for (const auto &c: s) {
        if (c == ' ') {
            result += c;
            ++pos;
            continue;
        }
        if (is_operation(c)) {
            if (is_prev_operation) {
                IS_VALID_EXPRESSION = false;
                return "";
            }
            is_prev_operation = true;
        }
        else {
            is_prev_operation = false;
        }
        result += c;
        if (c == '(') {
            size_t counter = 1;
            while (pos + counter < s.length() && isspace(s[pos + counter])) {
                counter++;
            }
            if (pos + counter < s.length() && s[pos + counter] != '(') {
                result += '0';
            }

            is_prev_opening_bracket = true;
        }
        else if (c == ')') {
            if (is_prev_opening_bracket) {
                IS_VALID_EXPRESSION = false;
                return "";
            }
        } else {
            is_prev_opening_bracket = false;
        }
        ++pos;
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
        } else if (s.at(i) == ')') {
            // закр скобка выталкивает в ответ все операции до закрывающей скобки и удаляет открывающую
            while (!st.empty() && is_operation(st.top())) {
                res += st.top();
                res += " ";
                st.pop();
            }
            if (!st.empty() && st.top() == '(') {
                st.pop();
            } else {
                // не соответствуют скобки
                IS_VALID_EXPRESSION = false;
                return "";
            }
        } else {
            // неизвестные символы
            IS_VALID_EXPRESSION = false;
            return "";
        }
    }
    while (!st.empty()) {
        char tp = st.top();
        if (is_operation(tp)) {
            res += tp;
            res += " ";
            st.pop();
        }
        else {
            IS_VALID_EXPRESSION = false;
            return "";
        }
    }
    return res;
}

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression;
    expression = "( - ( 2 + 3 ) )";
    //getline(cin, expression);
    string processed_expr = preprocess_expr(expression);
    cout<< processed_expr<<endl;;
    //cout<<processed_expr<<endl;
    string result_postfix = convert_to_prn(processed_expr);
    int result = evaluate_from_prn(result_postfix);

    if (IS_VALID_EXPRESSION) {
        cout << result << endl;
    } else {
        cout << "WRONG";
    }
    return 0;
}

