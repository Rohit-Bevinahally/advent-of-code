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
template<class T1, class T2>
istream& operator>>(istream &istream, pair<T1, T2> &p) { return (istream >> p.first >> p.second); } 
template<class T1, class T2>
ostream& operator<<(ostream &ostream, const pair<T1, T2> &p) { return (ostream << p.first << " " << p.second); }

template<class T>
istream& operator>>(istream &istream, vector<T>& v) { for(auto& a: v) istream >> a; return istream; }
template<class T>
ostream& operator<<(ostream &ostream, const vector<T>& v) { for(auto& a: v) ostream << a << " "; return ostream; }

template<class T>
void split(string& s, vector<T>& v, string delim) {
    auto parts = s | views::split(delim);
    v = ranges::to<vector<T>>(parts);
}


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

string line;

void solve() {
    v<vi> locks, keys;
    vs v;
    auto populate = [&]() {
        int n = sz(v), m = sz(v[0]);
        if(v[0] == string(m, '#') and v.back() == string(m, '.')) {
            locks.pb({});
            rep(j,m) {
                int cnt = 0;
                for(int i = 1; i < n-1; i++) if(v[i][j] == '#') cnt++;
                locks.back().pb(cnt);
            }
        }
        if(v[0] == string(m, '.') and v.back() == string(m, '#')) {
            keys.pb({});
            rep(j,m) {
                int cnt = 0;
                for(int i = 1; i < n-1; i++) if(v[i][j] == '#') cnt++;
                keys.back().pb(cnt);
            }
        }
    };
    while (getline(cin, line)) {
        if(line == "") {
            populate();
            v.clear();
        } else {
            v.pb(line);
        }
    }
    populate();
    int ans = 0;
    trv(l, locks) trv(k, keys) {
        bool pos = true;
        rep(i, sz(l)) if(l[i] + k[i] > 5) pos = false;
        ans += pos;
    }
    cout << ans << nl;
}

int main() {
    freopen("input", "r", stdin);
    solve();
    return 0;
}
