#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
template<typename T> using v = vector<T>;

#define FOR(i,k,n) for(auto i=k; i<n; i++)
#define rep(i,n) FOR(i,0,n) 
#define sz(x) (int)x.size()
#define pb push_back

const char nl = '\n';

ll p10[18]{};

bool solve(ll a, vll& v) {
    bool pos = false;
    auto dfs = [&](auto self, int i, ll cur) {
        if(cur > a) return;
        if(i == sz(v)) {
            if(cur == a) pos = true;
            return;
        }
        self(self, i+1, cur+v[i]);
        self(self, i+1, cur*v[i]);
        int d = log10(v[i])+1;
        self(self, i+1, cur*p10[d]+v[i]);
    };
    dfs(dfs, 1, v[0]);
    return pos;
}
int main() {
    freopen("input.txt", "r", stdin);
    p10[0] = 1;
    rep(i, 17) p10[i+1] = p10[i]*10;
    string line;
    v<vll> vv;
    vll aa;
    while(getline(cin, line)) {
        stringstream ss(line);
        ll a,x;
        char _;
        vll v;
        ss >> a >> _;
        while(ss >> x) {
            v.pb(x);
        }
        aa.pb(a);
        vv.pb(v);
    }

    ll ans = 0;
    // #pragma omp parallel for reduction(+:ans)
    rep(i, sz(vv)) {
        if(solve(aa[i], vv[i])) ans += aa[i];
    }
    cout << ans << nl;
    return 0;
}
