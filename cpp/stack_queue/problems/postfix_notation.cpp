#include <bits/stdc++.h>

using namespace std;

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression;
    getline(cin, expression);

    stack<int> st;
    for (char c: expression) {
        if (c == ' ') {
            continue;
        }
        // операнды просто пушим в стек

        if (isdigit(static_cast<unsigned char>(c))) {
            st.push(c - '0');
        }
        else {
            if (st.size() >= 2) {
                int second = st.top();
                st.pop();
                int first = st.top();
                st.pop();

                switch (c) {
                    case '+':
                        st.push(first + second);
                        break;
                    case '*':
                        st.push(first * second);
                        break;
                    case '-':
                        st.push(first - second);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (st.size() == 1) {
        cout << st.top();
    }
    return 0;
}