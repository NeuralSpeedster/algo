#include <bits/stdc++.h>

using namespace std;

void printDq(const deque<int>& d) {
    for (const auto& x : d) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (auto& x : arr) cin >> x;
    deque<int> dq;
    vector<int> result(n - k + 1, 0);

    for (int i = 0; i < n; i++) {
        while (!dq.empty() &&  dq.back() > arr[i]) {
            dq.pop_back();
        }
        dq.push_back(arr[i]);

        printDq(dq);

        if (i >= k - 1) {
            result[i - k + 1] = dq.front();
            dq.pop_front();
        }
    }
    cout<<"Final Result: "<<endl;
    for (const auto& x : result) {
        cout << x << "\n";
    }
    return 0;
}