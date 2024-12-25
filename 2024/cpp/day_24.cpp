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
struct con {
    string a, b;
    int t;
};

void solve() {
    bool gates = false;
    map<string, int> vals;
    map<string, con> radj;

    ll ans = 0;

    while (getline(cin, line)) {
        if(line == "") {
            gates = true;
            continue;
        }
        vs p;
        if(!gates) {
            split(line, p, " ");
            p[0].pop_back();
            vals[p[0]] = stoi(p[1]);
        } else {
            split(line, p, " ");
            int op = p[1] == "AND" ? 0 : p[1] == "OR" ? 1 : 2;
            radj[p[4]] = {p[0], p[2], op};
        }
    }
    auto comb = [&](int a, int b, int t) {
        if(t == 0) return a & b;
        if(t == 1) return a | b;
        if(t == 2) return a ^ b;
    };

    string cur;
    map<string, vs> leaves;
    auto dfs = [&](auto f, string u) -> void {
        auto [a, b, t] = radj[u];
        if(a[0] == 'x' or a[0] == 'y') {
            leaves[cur].pb(a);
        }
        if(b[0] == 'x' or b[0] == 'y') {
            leaves[cur].pb(b);
        }
        if(!vals.contains(a)) f(f, a);
        if(!vals.contains(b)) f(f, b);
        vals[u] = comb(vals[a], vals[b], t);
    };
    rep(i, 45) {
        string num = (i < 10 ? "0" : "") + to_string(i);
        cur = "z" + num;
        dfs(dfs, cur);
    }
    cout << sz(vals) << nl;
    for(auto [k, v]: leaves) {
        cout << k << " : " << v << nl;
    }
    int carry = 0;
    rep(i,45) {
        string num = (i < 10 ? "0" : "") + to_string(i);
        int nx = vals["x" + num];
        int ny = vals["y" + num];
        int nz = vals["z" + num];
        if((nx ^ ny ^ carry) != nz) {
            cout << i << nl;
        }
        carry = (nx & ny) | ((nx ^ ny) & carry);
    }
    if(carry != vals["z45"]) {
        cout << 45 << nl;
    }
}

int main() {
    freopen("input", "r", stdin);
    solve();
    return 0;
}
