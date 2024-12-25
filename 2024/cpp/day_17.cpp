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

template<class T>
void split(const string& s, char delim, vector<T>& v) {
    string cur;
    T x;
    stringstream ss;
    for(auto& c : s) {
        if(c == delim) {
            ss << cur;
            ss >> x;
            v.push_back(x);
            ss.clear();
            cur.clear();
        } else {
            cur += c;
        }
    }
    ss << cur;
    ss >> x;
    v.push_back(x);
}

void solve2(vi p);

ll solve(vs& lines) {
    vll r;
    rep(i,3) {
        auto [_,x] = scn::scan<char, ll>(lines[i], "Register {}: {}")->values();
        r.pb(x);
    }
    auto [p] = scn::scan<string>(lines[3], "Program: {}")->values();
    vi prog;
    split(p, ',', prog);

    solve2(prog);

    auto c = [&](int val) -> ll {
        if(val == 7) return -1;
        if(val < 4) return val;
        return r[val-4];
    };

    auto do_op = [&](int ip, int op, int val) {
        bool jmp = false;
        ll x = c(val), cur = 1;
        rep(i,x) {
            cur *= 2;
            if(cur > r[0]) break;
        }
        switch(op) {
            case 0:
                r[0] /= cur;
                break;
            case 1:
                r[1] ^= val;
                break;
            case 2:
                r[1] = c(val) % 8;
                break;
            case 3:
                if(r[0]) {
                    jmp = true;
                    ip = val;
                }
                break;
            case 4:
                r[1] ^= r[2];
                break;
            case 5:
                cout << (c(val) % 8) << ',';
                break;
            case 6:
                r[1] = r[0] / cur;
                break;
            case 7:
                r[2] = r[0] / cur;
                break;
            default:
                break;
        }
        if(!jmp) ip += 2;
        return ip;
    };

    int ip = 0;
    while(ip < sz(prog)) {
        int op = prog[ip];
        int val = prog[ip+1];
        ip = do_op(ip, op, val);
    }
    return 0;
}

void solve2(vi p) {
    ll ans = 0;
    auto do_seq = [&](ll a, int tgt) {
        ll b = (a & 0x7) ^ 5;
        ll c = a / (1LL << b);
        b ^= 6;
        b ^= c;
        return (b & 0x7) == tgt;
    };

    auto check = [&](auto self, int i, ll j) -> ll {
        if(i < 0) return j;
        rep(k, 8) {
            ll a = (j << 3) + k;
            if(do_seq(a, p[i])) {
                if(auto ans = self(self, i-1, a)) {
                    return ans;
                }
            }
        }
        return 0;
    };

    cout << check(check, sz(p)-1, 0) << nl;
}

int main() {
    freopen("input", "r", stdin);
    string line;
    vs lines;
    while (getline(cin, line)) {
        if(sz(line)) lines.pb(line);
    }

    cout << solve(lines) << nl;
    return 0;
}
