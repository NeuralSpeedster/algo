#include <bits/stdc++.h>

using namespace std;

// Задача A. ПСП.
// S ::= ∅ | (S) | [S] | {S} | S1 S2

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string sequence;
    cin >> sequence;
    stack<char> brackets;

    for (auto c : sequence) {
        if (c == '{' || c == '[' || c == '(') {
            brackets.push(c);
        }
        else if (c == '}' || c == ']' || c == ')') {
            if (!brackets.empty()) {
                char top = brackets.top();
                char correct;
                if (top == '{') {
                    correct = '}';
                }
                else if (top == '(') {
                    correct = ')';
                }
                else if (top == '[') {
                    correct = ']';
                }
                else {
                    cout<<"no";
                    return 0;
                }
                if (c != correct) {
                    cout << "no";
                    return 0;
                }
                brackets.pop();
            }
            else {
                cout << "no";
                return 0;
            }
        }
    }
    if (brackets.empty()) {
        cout << "yes";
    }
    else {
        cout << "no";
    }
    return 0;
}

