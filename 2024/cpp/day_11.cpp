#include <bits/stdc++.h>
using namespace std;

// {{{
// Data type definitions
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
template<typename T> using v = vector<T>;
template<typename T, int N> using a = array<T, N>; 

// Macros
#define FOR(i,k,n) for(auto i=k; i<n; i++)
#define ROF(i,n,k) for(auto i=n-1; i>=k; i--)
#define rep(i,n) FOR(i,0,n)
#define per(i,n) ROF(i,n,0)
#define trv(x,a) for(auto& x:a)
#define rtrv(x,a) for(auto& x:a | views::reverse)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz(x) (int)x.size()
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define eb emplace_back
#define ins insert
#define mp make_pair
#define f first
#define s second

// Min-Max :
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
#define armin(v) *min_element(all(v))
#define armax(v) *max_element(all(v))

// I/O :
template<typename T1, typename T2>
istream& operator>>(istream &istream, pair<T1, T2> &p) { return (istream >> p.first >> p.second); } 
template<typename T1, typename T2>
ostream& operator<<(ostream &ostream, const pair<T1, T2> &p) { return (ostream << p.first << " " << p.second); }

stringstream ss;
template<class T> void inp(T& x) { ss >> x; }
template<class H, class... T> void inp(H& h, T&... t) { inp(h); inp(t...); }
template<class T> void inp(vector<T>& v, char sep = ' ') { T x; while (ss >> x) v.pb(x); }

// Apply offset :
template<class T> vector<T> operator+(vector<T> v, T x) { trv(a,v) a += x; return v; }
template<class T> pair<T,T> operator+(pair<T, T> p, T x) { p.f += x, p.s += x; return p; }

// rng :
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
// }}}

// Constants :
const int mod = 1e9 + 7; //998244353;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-9;
const char nl = '\n';

// Debug :
#ifdef LOCAL
#include "../../Library/debug.cpp"
#else
#define debug(...) ""
#endif

ll solve(vll& a) {
    map<pll, ll> dp;
    auto dfs = [&](auto f, ll num, ll steps) -> ll {
        if(steps == 0) return 1;
        if(dp.contains({num, steps})) return dp[{num, steps}];
        ll& ans = dp[{num, steps}];
        if(num == 0) return ans = f(f, 1, steps - 1);
        string s = to_string(num);
        if(sz(s) & 1) {
            return ans = f(f, num * 2024, steps - 1);
        } else {
            int h = sz(s) / 2;
            ll left = stoll(s.substr(0, h));
            ll right = stoll(s.substr(h));
            return ans = f(f, left, steps - 1) + f(f, right, steps - 1);
        }
    };

    ll ans = 0;
    for(auto& x : a) {
        ans += dfs(dfs, x, 75);
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    vll a;
    while (getline(cin, line)) {
        ss << line;
        inp(a);
    }
    cout << solve(a) << '\n';
    return 0;
}
