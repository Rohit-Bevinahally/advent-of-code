#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
template<typename T> using v = vector<T>;

// Macros
#define FOR(i,k,n) for(auto i=k; i<n; i++)
#define ROF(i,n,k) for(auto i=n-1; i>=k; i--)
#define rep(i,n) FOR(i,0,n)
#define per(i,n) ROF(i,n,0)
#define sz(x) (int)x.size()
#define pb push_back

const char nl = '\n';

struct DSU{
    vector<int> e; int comps;
    DSU(int n) { e = vector<int>(n,-1); comps = n; }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]);}
    bool same(int a,int b) { return get(a) == get(b);}
    int csize(int x) { return -e[get(x)];}
    bool join(int x,int y){
        x = get(x),y = get(y);
        if(x == y) return false;
        if(e[x] > e[y]) swap(x,y);
        e[x] += e[y];
        e[y] = x;
        comps--;
        return true;
    }
};

// LURD
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

ll solve(vs& g) {
    int n = sz(g), m = sz(g[0]);
    DSU dsu(n * m);
    auto c = [&](int i, int j) { return m * i + j; };
    auto valid = [&](int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; };

    rep(i,n) rep(j,m) rep(k,4) {
        int ni = i + dx[k], nj = j + dy[k];
        if(valid(ni, nj) && g[i][j] == g[ni][nj]) {
            dsu.join(c(i, j), c(ni, nj));
        }
    }

    vi p(n * m), s(n * m);
    v<vi> ct(n * m, vi(4));

    rep(i,n) rep(j,m) {
        int C = c(i, j);
        int ld = dsu.get(C);
        rep(k,4) {
            int ni = i + dx[k], nj = j + dy[k];
            if(!valid(ni, nj) || g[i][j] != g[ni][nj]) {
                p[ld]++;
                rep(l,2) {
                    if(l == k % 2) continue;
                    int li = i + dx[l], lj = j + dy[l];
                    int node = c(li, lj);
                    if(!valid(li, lj) || g[i][j] != g[li][lj] || !ct[node][k]) {
                        s[ld]++;
                    }
                }
                ct[C][k] = 1;
            }
        }
    }

    ll ans = 0, ans2 = 0;
    rep(i, n * m) {
        if(dsu.get(i) == i) {
            ans += -dsu.e[i] * p[i];
            ans2 += -dsu.e[i] * s[i];
        }
    }
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
