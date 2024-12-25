#include <bits/stdc++.h>
#include <scn/scan.h>
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

ll linSolve(pll a, pll b, pll g) {
    ll det = a.f * b.s - a.s * b.f;
    if(det == 0) return 0;
    ll x = (g.f * b.s - g.s * b.f) / det;
    ll y = (a.f * g.s - a.s * g.f) / det;
    if(a.f * x + b.f * y == g.f and a.s * x + b.s * y == g.s) {
        return 3 * x + y;
    }
    return 0;
}

ll solve(pll a, pll b, pll g) {
    int ans = inf;
    rep(i, 101) rep(j, 101) {
        if(a.f * i + b.f * j == g.f and a.s * i + b.s * j == g.s) {
            ans = 3 * i + j;
        }
    }
    return (ans == inf ? 0 : ans);
}

int main() {
    freopen("input", "r", stdin);
    string line;
    ll ans = 0;
    pll a,b,g;
    while (getline(cin, line)) {
        if(line.empty()) {
            ans += linSolve(a, b, g);
            continue;
        }
        auto r1 = scn::scan<string, char, ll, ll>(line, "{} {}: X+{}, Y+{}");
        auto r2 = scn::scan<string, ll, ll>(line, "{} X={}, Y={}");
        if(r1) {
            auto [_, type, x, y] = r1->values();
            cout << type << " " << x << " " << y << endl;
            else b = {x, y};
        } else if(r2) {
            auto [_, x, y] = r2->values();
            g = {x, y};
        }
    }
    ans += linSolve(a, b, g);
    cout << ans << nl;
    return 0;
}
