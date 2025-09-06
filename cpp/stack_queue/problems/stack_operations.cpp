#include <bits/stdc++.h>

using namespace std;

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int n;
    cin >> n;
    cin.ignore();
    stack<unsigned int> st;
    vector<long long> prefix_sums(n+1); // оставим prefix_sums[0] == 0;

    unsigned int j = 1;
    for (unsigned int i = 0; i < n; i++) {
        string operation;
        getline(cin, operation);
        if (operation.empty()) {
            continue;
        }

        if (operation[0] == '+') {
            auto raw_value = operation.substr(1);
            unsigned int value = stoi(raw_value);
            st.push(value);
            prefix_sums[j] = prefix_sums[j - 1] + value;
            j++;

        } else if (operation[0] == '-' && !st.empty()) {
            auto deleted = st.top();
            prefix_sums[j-1] = 0;
            j--;
            cout << deleted << "\n";
            st.pop();

        } else if (operation[0] == '?') {
            auto raw_value = operation.substr(1);
            int k = stoi(raw_value);
            unsigned int s = st.size();
            if (s < k) {
                throw out_of_range("K is more than stack.size()");
            }
            long long ans = prefix_sums[s] - prefix_sums[s - k];
            cout << ans << "\n";
        }
    }
    return 0;
}
