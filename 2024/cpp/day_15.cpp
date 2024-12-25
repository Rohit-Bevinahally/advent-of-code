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

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
string dir = "v>^<";

vs transg(vs& g) {
    int n = sz(g), m = sz(g[0]);
    vs ng;
    rep(i,n) {
        ng.pb("");
        rep(j,m) {
            if(g[i][j] == 'O') ng.back() += "[]";
            else if(g[i][j] == '@') ng.back() += "@.";
            else if(g[i][j] == '.') ng.back() += "..";
            else ng.back() += "##";
        }
    }
    return ng;
}
ll solve(vs& g, string& M) {
    g = transg(g);
    int n = sz(g), m = sz(g[0]);
    int sx = 0, sy = 0;
    rep(i,n) rep(j,m) if(g[i][j] == '@') sx = i, sy = j;
    vpi boxes = {{sx, sy}};
    auto valid = [&](int x, int y) {
        if(x < 0 || x >= n || y < 0 || y >= m) return false;
        return g[x][y] != '#';
    };

    auto check = [&](int pos) {
        trv(b, boxes) {
            int nx = b.f + dx[pos], ny = b.s + dy[pos];
            if(b == boxes[0]) {
                if(!valid(nx, ny)) return false;
            } else {
                if(!valid(nx, ny) || !valid(nx, ny+1)) return false;
            }
        }
        return true;
    };

    auto collect = [&](int pos) {
        set<pi> nboxes;
        auto chk = [&](int x, int y) {
            if(valid(x,y) and g[x][y] != '.') {
                if(g[x][y] == '[') {
                    if(nboxes.contains(mp(x, y))) return 0;
                    nboxes.insert(mp(x, y));
                } else {
                    if(nboxes.contains(mp(x, y-1))) return 0;
                    nboxes.insert(mp(x, y-1));
                }
            }
            return 1;
        };

        vpi to_check = boxes;
        while(!to_check.empty()) {
            trv(b, to_check) {
                int nx = b.f + dx[pos], ny = b.s + dy[pos];
                if(b == boxes[0] || dir[pos] != '>') chk(nx, ny);
                if(b != boxes[0] && dir[pos] != '<') {
                    chk(nx, ny+1);
                }
            }
            to_check.clear();
            while(!nboxes.empty()) {
                auto it = nboxes.begin();
                to_check.pb(*it);
                boxes.pb(*it);
                nboxes.erase(it);
            }
        }
    };

    auto shift = [&](int pos) {
        rtrv(b, boxes) {
            if(b == boxes[0]) continue;
            int nx = b.f + dx[pos], ny = b.s + dy[pos];
            g[nx][ny] = '[';
            g[b.f][b.s] = '.';
            g[nx][ny+1] = ']';
            if(dir[pos] != '>') g[b.f][b.s+1] = '.';
            b = {nx, ny};
        }
    };

    int pdir = -1;
    trv(c, M) {
        int pos = dir.find(c);
        if(pos != pdir) {
            boxes.clear();
            boxes.eb(sx, sy);
            pdir = pos;
        }
        collect(pos);
        if(!check(pos)) continue;
        shift(pos);
        g[sx][sy] = '.';
        sx += dx[pos], sy += dy[pos];
        boxes[0] = {sx, sy};
        g[sx][sy] = '@';
    }

    ll ans = 0;
    rep(i,n) rep(j,m) if(g[i][j] == '[') ans += 100 * i + j;
    return ans;
}

int main() {
    freopen("input", "r", stdin);
    string line;
    vs g;
    string m;
    bool done = false;
    while (getline(cin, line)) {
        if(line == "") done = true;
        if(!done) g.pb(line);
        else m += line;
    }
    cout << solve(g, m) << nl;
    return 0;
}

