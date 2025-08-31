#include <bits/stdc++.h>

using namespace std;


int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int n;
    cin >> n;
    cin.ignore();
    deque<unsigned int> dq;
    for (size_t i = 0; i < n; i++) {
        string operation;
        getline(cin, operation);
        if (operation.empty()) {
            continue;
        }
        if (operation[0] == '+') {
            auto raw_value = operation.substr(1);
            unsigned int value = stoi(raw_value);
            dq.push_back(value);
        } else if (operation[0] == '-') {
            cout << dq.back() << "\n";
            dq.pop_back();
        } else if (operation[0] == '?') {
            auto raw_value = operation.substr(1);
            int k = stoi(raw_value);
            long long sum = 0;
            for (auto it = dq.rbegin(); it != dq.rend() && k > 0; ++it, --k) {
                sum += *it;
            }
            cout << sum << "\n";
        }
    }
    return 0;
}
