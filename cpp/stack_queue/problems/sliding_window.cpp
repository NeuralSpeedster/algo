#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (auto& x : arr) cin >> x;
    deque<int> dq;
    vector<int> result(n - k + 1, 0);

    for (int i = 0; i < n; i++) {
        //  проверить, не выпал ли из окна минимум: если выпал, то его надо забрать из дека.
        if (!dq.empty() && (i >= k) && dq.front() == arr.at(i-k)) {
            dq.pop_front();
        }

        while (!dq.empty() &&  dq.back() > arr[i]) {
            dq.pop_back();
        }
        dq.push_back(arr[i]);

        if (!dq.empty() && i >= k - 1) {
            result[i - k + 1] = dq.front();
        }
    }
    for (const auto& x : result) {
        cout << x << "\n";
    }
    return 0;
}