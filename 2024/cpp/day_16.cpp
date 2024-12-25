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
template<class T> bool ckmin(T& a, const T& b) { return b <= a ? a = b, 1 : 0; }
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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int minr(int d1, int d2) {
    if(d1 > d2) swap(d1, d2);
    return min(d2 - d1, d1 + 4 - d2);
}

ll solve(vs& g) {
    int n = sz(g), m = sz(g[0]);
    int sx, sy, ex, ey;
    rep(i,n) rep(j,m) {
        if(g[i][j] == 'S') sx = i, sy = j;
        else if(g[i][j] == 'E') ex = i, ey = j;
    }
    auto c = [&](int x, int y, int d) {
        return m * 4 * x + 4 * y + d;
    };
    set<int> goals;
    rep(i,4) goals.insert(c(ex, ey, i));

    vll dist(n * m * 4, INF);
    priority_queue<pll, v<pll>, greater<pll>> pq;
    pq.push({0, c(sx, sy, 0)});
    ll ans = INF;

    while(!pq.empty()) {
        auto [D, u] = pq.top(); pq.pop();
        if(goals.contains(u)) {
            ckmin(ans, D);
            continue;
        }
        int x = u / (m * 4);
        int rx = u % (m * 4);
        int y = rx / 4;
        int d = rx % 4;
        rep(i,4) {
            if(i == d) {
                int nx = x + dx[i], ny = y + dy[i];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#') continue;
                int cur = c(nx, ny, i);
                if(ckmin(dist[cur], D + 1)) {
                    pq.push({D + 1, cur});
                }
            } else {
                int cur = c(x, y, i);
                if(ckmin(dist[cur], D + 1000 * minr(d, i))) {
                    pq.push({dist[cur], cur});
                }
            }
        }
    }
    ll ans2 = 0;
    queue<int> q;
    vi good(n * m);
    auto c2 = [&](int x, int y) {
        return m * x + y;
    };

    good[c2(ex, ey)] = 1;
    trv(g, goals) if(dist[g] == ans) q.push(g);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(u == c(sx, sy, 0)) continue;
        int x = u / (m * 4);
        int rx = u % (m * 4);
        int y = rx / 4;
        int d = rx % 4;

        rep(i,4) {
            if(i == d) {
                int nx = x + dx[i^2], ny = y + dy[i^2];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#') continue;
                int cur = c(nx, ny, i);
                if(dist[cur] + 1 == dist[u]) {
                    good[c2(nx, ny)] = 1;
                    q.push(cur);
                }
            } else {
                int cur = c(x, y, i);
                if(dist[cur] + 1000 * minr(d, i) == dist[u]) {
                    q.push(cur);
                }
            }
        }
    }
    rep(i,n) rep(j,m) if(good[c2(i, j)]) ans2++;
    return ans2;
}

int main() {
    freopen("input", "r", stdin);
    string line;
    vs g;
    while (getline(cin, line)) {
        g.pb(line);
    }
    cout << solve(g) << nl;
    return 0;
}
