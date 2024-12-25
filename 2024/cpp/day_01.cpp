#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

void solve() {
    vector<int> left, right;
    ll ans = 0;
    for (int a, b; cin >> a >> b; ) {
        left.push_back(a);
        right.push_back(b);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    assert(left.size() == right.size());

    for(int i = 0; i < left.size(); i++) {
        ans += abs(left[i] - right[i]);
    }

    cout << ans << '\n';
}

void solve2() {
    map<int, int> left, right;
    ll ans = 0;
    for (int a, b; cin >> a >> b; ) {
        left[a]++;
        right[b]++;
    }

    for (auto [key, value] : left) {
        if(right.contains(key)) {
            ans += 1LL * key * value * right[key];
        }
    }

    cout << ans << '\n';
}

int main() {
    freopen("../input/part_1.txt", "r", stdin);
    solve2();
    return 0;
}
