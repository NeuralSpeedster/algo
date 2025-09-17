#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t n;
    cin >> n;
    vector<string> tabs;
    size_t current = 0;
    for (int i = 0; i < n; i++) {
        string command;
        getline(cin, command);
        if (!command.empty() && command[0] == 'R') {
            auto start = command.find_first_not_of("Run ");
            auto app = command.substr(start);
            tabs.push_back(app);
        } else if (!command.empty() && command[0] == 'A') {
            size_t k = (command.length() - 3) / 4;
            current = (current + k) % n;
        }
        if (!tabs.empty()) {
            cout << tabs[current] << endl;
        }
    }
    return 0;
}
