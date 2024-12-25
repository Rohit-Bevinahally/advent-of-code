#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<int>& v) {
    int n = v.size();

    auto good = [&](int d, int s) {
        if(d == 0 or abs(d) > 3) return false;
        if(d * s < 0) return false;
        return true;
    };

    auto rem = [&](int i, int s) {
        if(i > 0 and i < n-1) {
            return good(v[i+1] - v[i-1], s);
        }
        return true;
    };

    for(int s = 1, j = 0; j < 2; j++, s = -s) {
        bool pos = true;
        bool first_fail = true;
        for(int i = 1; i < n; i++) {
            int d = v[i] - v[i-1];
            if(!good(d, s)) {
                if(!first_fail) {
                    pos = false;
                    break;
                }
                first_fail = false;
                if(rem(i, s)) {
                    v[i] = v[i-1];
                    continue;
                } else if(!rem(i-1, s)) {
                    pos = false;
                    break;
                }
            }
        }
        if(pos) return true;
    }
    return false;
}

int main() {
    freopen("../input/part_1.txt", "r", stdin);
    string line;
    int ans = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        vector<int> v;
        int x;
        while (ss >> x) {
            v.push_back(x);
        }
        ans += isSafe(v);
    }
    cout << ans << '\n';
}
