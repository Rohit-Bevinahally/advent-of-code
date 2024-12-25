#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
template<typename T> using v = vector<T>;

#define FOR(i,k,n) for(auto i=k; i<n; i++)
#define ROF(i,n,k) for(auto i=n-1; i>=k; i--)
#define rep(i,n) FOR(i,0,n)
#define per(i,n) ROF(i,n,0)
#define sz(x) (int)x.size()
#define pb push_back
#define eb emplace_back
#define f first
#define s second

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }

const int inf = 0x3f3f3f3f;
const char nl = '\n';
const int G = 10; // Gap bound

struct Block {
    int st;
    int len;
    int val;
};

inline ll sum(int st, int len) {
    return 1LL * len * (len - 1 + 2 * st) / 2;
}

ll solve(string& s) {
    int n = sz(s);
    v<Block> used;
    priority_queue<int, vector<int>, greater<int>> free[G]{};
    int idx = 0;

    rep(i,n) {
        int len = s[i] - '0';
        if(i % 2 == 0) {
            used.eb(idx, len, i / 2);
        } else {
            free[len].push(idx);
        }
        idx += len;
    }

    ll ans = 0;
    per(i, sz(used)) {
        auto& b = used[i];
        int mnidx = inf, mnsz = -1;
        FOR(j, b.len, G) {
            if(free[j].empty()) continue;
            if(ckmin(mnidx, free[j].top())) {
                mnsz = j;
            }
        }
        if(mnidx > b.st) {
            ans += sum(b.st, b.len) * b.val;
            continue;
        }
        ans += sum(mnidx, b.len) * b.val;
        free[mnsz].pop();
        if(mnsz > b.len)
            free[mnsz - b.len].push(mnidx + b.len);
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    getline(cin, line);
    cout << solve(line) << nl;
    return 0;
}
