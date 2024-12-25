#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pi;
template<typename T> using v = vector<T>;

#define FOR(i,k,n) for(auto i=k; i<n; i++)
#define rep(i,n) FOR(i,0,n) 
#define sz(x) (int)x.size()
#define pb push_back

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }

const int inf = 0x3f3f3f3f;
const vector<char> dirs = { '^', '>','v','<' };
const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { -1, 0, 1, 0 };

struct FunctionalGraph {
    int n, comps = 0;
    vector<int> nxt, comp_id, cyc_idx, dist, root;
    vector<vector<int>> cycles, up;
    const int L = 20;

    FunctionalGraph(vector<int> a) : nxt(a) {
        n = (int)nxt.size();
        comp_id.assign(n,-1);
        up.resize(L, vector<int>(n));
        cyc_idx = root = dist = comp_id;
        init();
    }
    void init() {
        for(int i = 0; i < n; i++) if(~nxt[i]) up[0][i] = nxt[i];
        for(int i = 1; i < L; i++) {
            for(int j = 0; j < n; j++) {
                if(~nxt[i]) up[i][j] = up[i-1][up[i-1][j]];
            }
        }
        for(int i = 0; i < n; i++) if(comp_id[i] == -1) {
            if(nxt[i] == -1) continue;
            vector<int> nodes;
            int cur = i;
            while(comp_id[cur] == -1) {
                nodes.push_back(cur);
                comp_id[cur] = -2;
                cur = nxt[cur];
            }
            bool inCycle = false;
            int cid = comp_id[cur];
            if(cid < 0) cid = comps++;

            int id = 0;
            vector<int> cyc_nodes;
            for(auto x : nodes) {
                comp_id[x] = cid;
                inCycle |= (x == cur);
                if(inCycle) {
                    cyc_idx[x] = id++;
                    cyc_nodes.push_back(x);
                }
            }
            if(inCycle) cycles.push_back(cyc_nodes);
        }

        for(int i = 0; i < n; i++) if(dist[i] == -1 and ~nxt[i]) get_dist(i);
    }

    int get_root(int u) {
        if(~root[u]) return root[u];
        if(~cyc_idx[u]) return root[u] = u;
        return root[u] = get_root(nxt[u]);
    }

    int get_dist(int u) {
        if(~dist[u]) return dist[u];
        if(u == get_root(u)) return dist[u] = 0;
        return dist[u] = 1 + get_dist(nxt[u]);
    }

    int cycle_dist(int u, int v) {
        if(comp_id[u] != comp_id[v]) return -1;
        int cyc_len = (int)cycles[comp_id[u]].size();
        return (cyc_idx[v] - cyc_idx[u] + cyc_len) % cyc_len; 
    }

    int jump(int u, int k) {
        for(int i = L - 1; i >= 0; i--) if(k >> i & 1) u = up[i][u];
        return u;
    }

    int node_dist(int u, int v) {
        if(comp_id[u] != comp_id[v] or dist[v] > dist[u]) return inf;
        int diff = dist[u] - dist[v];
        u = jump(u, diff);
        if(dist[v]) {
            return (u != v) ? inf : diff;
        } else {
            return diff + cycle_dist(u, v);
        }
    }
};

set<pair<int,int>> path;
int sx = -1, sy = -1, didx = -1;

int solve(vs& g) {
    int n = sz(g), m = sz(g[0]);
    rep(i,n) rep(j,m) {
        rep(k,4) {
            if(g[i][j] == dirs[k]) {
                sx = i, sy = j;
                didx = k;
                break;
            }
        }
        if(~didx) break;
    }

    auto valid = [&](int x, int y) {
        return x >= 0 and x < n and y >= 0 and y < m;
    };

    auto dfs = [&](auto self, int i, int j, int d) {
        path.insert({i,j});
        int nx = i + dx[d], ny = j + dy[d];
        if(!valid(nx,ny)) return;

        if(g[nx][ny] == '#') {
            int nd = (d + 1) % 4;
            self(self, i, j, nd);
        } else {
            self(self, nx, ny, d);
        }
    };

    dfs(dfs, sx, sy, didx);
    int ans = sz(path);
    path.erase({sx,sy});
    return ans;
}

int solve2(vs& g) {
    int n = sz(g), m = sz(g[0]);

    auto c = [&](int x, int y, int d) {
        return m * x * 4 + 4 * y + d;
    };

    auto valid = [&](int x, int y) {
        return x >= 0 and x < n and y >= 0 and y < m;
    };

    vi nxt(n * m * 4 + 1, -1);
    const int outside = n * m * 4;
    rep(i,n) rep(j,m) {
        if(g[i][j] == '#') continue;
        rep(k,4) {
            int nx = i + dx[k], ny = j + dy[k];
            int cur = c(i,j,k);
            if(!valid(nx,ny)) {
                nxt[cur] = outside;
            } else if(g[nx][ny] == '#') {
                int nd = (k + 1) % 4;
                nxt[cur] = c(i,j,nd);
            } else {
                nxt[cur] = c(nx,ny,k);
            }
        }
    }

    FunctionalGraph fg(nxt);

    int ans = 0;
    for(auto& [x,y] : path) {
        // Place obstacle at (x,y)
        vi changes, rots;
        rep(d,4) {
            int cx = x + dx[d], cy = y + dy[d];
            if(!valid(cx,cy) or g[cx][cy] == '#') continue;
            // Changed edge has direction oposite to displacement
            int cd = d ^ 2;
            changes.pb(c(cx, cy, cd));
            rots.pb(c(cx, cy, (cd + 1) % 4));
        }
        int cands = sz(changes);
        vi vis(cands);
        int cur = c(sx, sy, didx);
        rep(i, cands + 1) {
            int mnd = inf, mni = -1;
            rep(j,cands) {
                if(ckmin(mnd, fg.node_dist(cur, changes[j]))) {
                    mni = j;
                }
            }
            if(~mni) {
                if(vis[mni]) {
                    ans++;
                    break;
                }
                vis[mni] = 1;
                cur = rots[mni];
            } else {
                if(fg.node_dist(cur, outside) == inf) {
                    ans++;
                    break;
                }
                break;
            }
        }
    }
    return ans;
}

int main() {
    freopen("test.txt", "r", stdin);
    string line;
    vs g;
    while(getline(cin, line)) {
        g.pb(line);
    }
    cout << solve(g) << '\n';
    cout << solve2(g) << '\n';
    return 0;
}
