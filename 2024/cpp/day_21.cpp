#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
template<typename T> using v = vector<T>;

#define FOR(i,k,n) for(auto i=k; i<n; i++)
#define ROF(i,n,k) for(auto i=n-1; i>=k; i--)
#define rep(i,n) FOR(i,0,n)
#define per(i,n) ROF(i,n,0)
#define trv(x,a) for(auto& x:a)
#define sz(x) (int)x.size()
#define pb push_back
#define mp make_pair

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }

const ll INF = 0x3f3f3f3f3f3f3f3f;
const char nl = '\n';

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
string dir = ">v<^";

vi nkp = { 10, 6, 7, 8, 3, 4, 5, 0, 1, 2, 11 };
vi dkp = { 5, 4, 3, 1, 2 };

int cv(int i, int j) {
    return i * 3 + j;
}
pi vc(int x) {
    return mp(x / 3, x % 3);
}

map<pair<string, int>, ll> dp;

ll calc(string s, int d, int pass = 1) {
    if(d == 0) {
        return sz(s);
    }

    auto state = mp(s, d);
    if(dp.contains(state)) {
        return dp[state];
    }

    int x = 0, y = 2, bad = 0;
    if(!pass) {
        x = 3, bad = 9;
    }
    ll cur = 0;

    trv(c, s) {
        int nx = -1, ny = -1;
        if(pass) {
            int nd = dir.find(c);
            if(nd == -1) nd = 4;
            tie(nx, ny) = vc(dkp[nd]);
        } else {
            tie(nx, ny) = vc(nkp[min(10, c - '0')]);
        }

        string ns1 = "";
        if(nx < x) ns1 += string(x - nx, '^');
        if(nx > x) ns1 += string(nx - x, 'v');

        string ns2 = "";
        if(ny < y) ns2 += string(y - ny, '<');
        if(ny > y) ns2 += string(ny - y, '>');

        ll mn = INF;
        if(cv(nx, y) != bad) {
            ckmin(mn, calc(ns1 + ns2 + 'A', d - 1));
        }
        if(cv(x, ny) != bad) {
            ckmin(mn, calc(ns2 + ns1 + 'A', d - 1));
        }
        cur += mn;
        x = nx, y = ny;
    }
    return dp[state] = cur;
}

int main() {
    freopen("input", "r", stdin);

    string line;
    ll ans = 0;
    while (getline(cin, line)) {
        ll x = stoll(line.substr(0,3));
        ll y = calc(line, 26, 0);
        ans += x * y;
    }
    cout << ans << nl;

    return (0-0);
}
