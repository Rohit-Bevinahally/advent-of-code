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
#include "/Users/rohitb/Library/debug.cpp"
#else
#define debug(...) ""
#endif

int solve(vs& g) {
    int n = sz(g), m = sz(g[0]);
    auto valid = [&](pi p) {
        auto [x, y] = p;
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    map<char, vpi> pos;
    rep(i, n) {
        rep(j, m) {
            if (g[i][j] != '.') {
                pos[g[i][j]].eb(i, j);
            }
        }
    }
    map<pi, int> cnt;
    for(auto [c, p] : pos) {
        int P = sz(p);
        rep(i, P) {
            rep(j, P) {
                if(i == j) continue;
                int dx = p[j].f - p[i].f;
                int dy = p[j].s - p[i].s;
                pi p1 { p[i].f - dx, p[i].s - dy };
                pi p2 { p[j].f + dx, p[j].s + dy };
                if(valid(p1)) cnt[p1]++;
                if(valid(p2)) cnt[p2]++;
            }
        }
    }
    return sz(cnt);
}
int solve2(vs& g) {
    int n = sz(g), m = sz(g[0]);
    auto valid = [&](pi p) {
        auto [x, y] = p;
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    map<char, vpi> pos;
    rep(i, n) {
        rep(j, m) {
            if (g[i][j] != '.') {
                pos[g[i][j]].eb(i, j);
            }
        }
    }
    map<pi, int> cnt;
    set<pair<ld, ld>> lines;
    for(auto [c, p] : pos) {
        int P = sz(p);
        rep(i, P) {
            FOR(j, i+1, P) {
                int dx = p[j].f - p[i].f;
                int dy = p[j].s - p[i].s;
                ld slope = (ld)dy / dx;
                ld intercept = p[i].s - slope * p[i].f;
                if(lines.contains({slope, intercept})) continue;
                lines.insert({slope, intercept});

                while(dx % 2 == 0 && dy % 2 == 0) {
                    dx /= 2;
                    dy /= 2;
                }
                pi cur = p[i];
                while(valid(cur)) {
                    cnt[cur]++;
                    cur.f += dx;
                    cur.s += dy;
                }
                cur = p[i];
                while(valid(cur)) {
                    cnt[cur]++;
                    cur.f -= dx;
                    cur.s -= dy;
                }
            }
        }
    }
    return sz(cnt);
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    vs g;
    while (getline(cin, line)) {
        g.pb(line);
    }
    cout << solve2(g) << nl;
    return 0;
}

