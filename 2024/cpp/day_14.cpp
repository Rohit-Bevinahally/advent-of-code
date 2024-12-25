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

int N = 101, M = 103, S = 100;

ll solve(vpll& po, vpll& ve) {
    int n = sz(po);
    v<vll> ans(M, vll(N));
    rep(i,n) {
        po[i].f = (po[i].f + (S * ve[i].f) % N + N) % N;
        po[i].s = (po[i].s + (S * ve[i].s) % M + M) % M;
        ans[po[i].s][po[i].f]++;
    }
    vll vals(4);
    rep(i,M) {
        rep(j,N) {
            if(i < M/2 and j < N/2) vals[0] += ans[i][j];
            if(i < M/2 and j > N/2) vals[1] += ans[i][j];
            if(i > M/2 and j < N/2) vals[2] += ans[i][j];
            if(i > M/2 and j > N/2) vals[3] += ans[i][j];
        }
    }
    ll fans = 1;
    rep(i,4) fans *= vals[i];
    return fans;
}

ll solve2(vpll& po, vpll& ve) {
    int n = sz(po);
    v<vll> ans(M, vll(N));
    int i = 0;
    while(++i) {
        rep(i,n) {
            po[i].f = ((po[i].f + ve[i].f) % N + N) % N;
            po[i].s = ((po[i].s + ve[i].s) % M + M) % M;
            ans[po[i].s][po[i].f]++;
        }
        bool pos = true;
        rep(i, M) rep(j, N) if(ans[i][j] > 1) pos = false;
        if(pos) {
            cout << i << nl;
            rep(i,M) {
                rep(j, N) {
                    if(ans[i][j]) cout << 'X';
                    else cout << '.';
                }
                cout << nl;
            }
        }
        rep(i,M) rep(j,N) ans[i][j] = 0;
    }
    return -1;
}

int main() {
    freopen("input", "r", stdin);
    string line;
    vpll po, ve;
    while (getline(cin, line)) {
        auto res = scn::scan<int, int, int, int>(line, "p={},{} v={},{}");
        auto [px, py, vx, vy] = res->values();
        po.eb(px, py);
        ve.eb(vx, vy);
    }
    cout << solve(po, ve) << nl;
    return 0;
}
