#include <bits/stdc++.h>
// #include <scn/scan.h>
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
const int M = 16777215;
const int N = 2000;

void solve() {
    vll a;
    while (getline(cin, line)) {
        a.pb(stoll(line));
    }
    ll ans = 0;
    int n = sz(a);
    v<vll> p(n, vll(N + 1));
    rep(i,n) {
        p[i][0] = a[i];
        ll A = a[i];
        rep(j, N) {
            A = (A ^ (A << 6)) & M;
            A = (A ^ (A >> 5)) & M;
            A = (A ^ (A << 11)) & M;
            p[i][j+1] = A;
        }
    }
    unordered_map<ll, ll> cnt;
    unordered_set<ll> cur;
    rep(i, n) {
        cur.clear();
        ll dq = 0;
        FOR(j, 1, N + 1) {
            int diff = (p[i][j] % 10 - p[i][j-1] % 10);
            int sign = diff > 0 ? 1 : 2;
            dq = (dq * 100 + sign * 10 + abs(diff)) % 100000000;
            if(j >= 4) {
                if(!cur.contains(dq)) {
                    cur.ins(dq);
                    cnt[dq] += (p[i][j] % 10);
                    ckmax(ans, cnt[dq]);
                }
            }
        }
    }
    cout << ans << nl;
}

int main() {
    freopen("input", "r", stdin);
    solve();
    return 0;
}

