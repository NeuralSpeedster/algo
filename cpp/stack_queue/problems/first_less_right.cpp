#include <bits/stdc++.h>

using namespace std;

// вывести индекс первого правого меньшего для каждого элемента
// решение со стеком O(n)

int main() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> res(n, -1);
    stack<pair<int, int>> unknown;

    for (int i = 0; i < n; i++) {
        while (!unknown.empty() && unknown.top().first > a[i]) {
            // заберем из стека всех кто больше текущего элемента
            res[unknown.top().second] = i;
            unknown.pop();
        }
        unknown.emplace(a[i], i);
    }
    for (auto x : res) {
        cout << x<<" ";
    }
    return 0;
}