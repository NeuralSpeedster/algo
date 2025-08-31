#include <bits/stdc++.h>

using namespace std;

int evaluate_from_pn(const string &s) {
    return 0;
}

string convert_to_pn(const string &s) {
    stack<int> st;

    return s;
}

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression;
    getline(cin, expression);

    string result_prefix = convert_to_pn(expression);
    return evaluate_from_pn(result_prefix);
}