/*{{{*/
#include <bits/stdc++.h>
#define st first
#define nd second
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {cerr<<(!c_?"\033[96;1m":"");\
++c_;__VA_ARGS__;--c_;cerr<<(!c_?"\033[0m":"");}
#else
#define debug(...) {}
#endif
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
using namespace std; using ll = long long;
template< typename... t > using V = vector< t... >;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":"");print(b...);}
int argc_; char** argv_;
/*thread_local mt19937 gen;
inline ll arg(int v, ll def = 0)
{return v < argc_? atoll(argv_[v]) : def;}
template< typename t >
t rng(t min, t max) 
{return uniform_int_distribution< t >{min, max}(gen);}*/
#define int ll
/*}}}*/

#define int ll

#ifdef DEF
constexpr int pri[2] = {2, 5}, mod[3] = {2, 5, (int)(10)}, toc[3] = {1, 4, 4};
#else
constexpr int pri[2] = {2, 5}, mod[3] = {512, 1953125, (int)(1e9)}, toc[3] = {256, 1562500, 400000000}; 
#endif

ll r, s; int k;
int res[2], dp[2][mod[1] + 1];

pair< ll, ll > rgcd (int x, int y)
{
    if (y == 0)
        return { 1, 0 };
    ll a, b;
    tie(a, b) = rgcd(y, x % y);
    return { b, a - (x / y) * b };
}

inline int fpow(int v, ll w, int m)
{
    int r = 1;
    while (w)
    {
        if (w & 1)
            r = ((ll)r * v) % m;
        v = ((ll)v * v) % m;
        w >>= 1;
    }
    return r;
}

inline int inv(int v, int i)
{
    return fpow(v, toc[i] - 1, mod[i]);
}

inline ll fun(ll v, int e)
{
    ll res = 0;
    while (v)
    {
        res += v / e;
        v /= e;
    }
    return res;
}

int fsil(ll, int);

inline int sil(ll v, int i)
{
    ll r = fsil(v, i);
    ll q = inv(fpow(pri[1 - i], fun(v, pri[1 - i]), mod[i]), i);
    dump(r, q, i);
    return (r * q) % mod[i];
}

inline int fsil(ll v, int i)
{
    if (v == 0) return 1;
    ll r = fpow(dp[i][mod[i]], v / mod[i], mod[i]);
    ll c = v % mod[i];
    r = (r * dp[i][c]) % mod[i];
    return (r * fsil(v / pri[i], i)) % mod[i];
}

string solve(ll r, ll s, int k)
{
    dump(r, s, k);
    //cout << r << '|' << s << '|' << k << '\n';

    for (int i = 0; i < 2; ++i)
    {
        dp[i][0] = 1;
        for (int j = 1; j <= mod[i]; ++j)
        {
            int v = j;
            if ((v % pri[i]) == 0)
            {
                dp[i][j] = dp[i][j - 1];
                continue;
            }
            dp[i][j] = ((ll)dp[i][j - 1] * v) % mod[i];
        }
    }

    dump(dp[0][mod[0]], dp[1][mod[1]]);

    for (int i = 0; i < 2; ++i)
    {
        int g = sil(r + s, i);
        int d = ((ll)sil(r, i) * sil(s, i)) % mod[i];
        dump(i, g, d, inv(d, i), ((ll)d * inv(d, i)) % mod[i]);
        res[i] = ((ll)g * inv(d, i)) % mod[i];
        dump(i, res[i]);
    }

    debug(
        for (int i = 0; i < 2; ++i)
            cerr << res[i] << ' ';
        cerr << '\n';
    );

    ll d = (fun(r + s, 2) - fun(r, 2) - fun(s, 2));
    ll p = (fun(r + s, 5) - fun(r, 5) - fun(s, 5));

    dump(d, p);

    ll l = min(d, p);
    d -= l; p -= l;

    dump(d, p);

    auto q = rgcd(mod[0], mod[1]);
    ll v = (res[1] * mod[0] * q.st + res[0] * mod[1] * q.nd) % mod[2];
    if (v < 0) v += mod[2];

    dump(v, v % mod[0], v % mod[1]);

    v = ((ll)v * fpow(2, d, mod[2])) % mod[2];
    v = ((ll)v * fpow(5, p, mod[2])) % mod[2];

    dump(v, v % mod[0], v % mod[1]);

    ll a = 1;
    for (int i = 0; i < k; ++i)
        a *= 10;

    v %= a;

    dump(v);

    string f;
    stringstream sout;

    sout << setw(k) << setfill('0') << v << '\n';
    sout >> f;

    return f;
}

string bsolve(const ll r, const ll s, const int k)
{
    ll g = r + s;
    ll d = min(r, s);
    ll c = 1;
    ll dw = 0;
    ll pi = 0;

    for (int i = 0; i < d; ++i)
    {
        ll v = g - i;
        while (v % 2 == 0)  
            v /= 2, ++dw;
        while (v % 5 == 0)
            v /= 5, ++pi;
        c = ((ll)c * v) % mod[2];
    }

    for (int i = 1; i <= d; ++i)
    {
        ll v = i;
        while (v % 2 == 0)  
            v /= 2, --dw;
        while (v % 5 == 0)
            v /= 5, --pi;
        ll inv = fpow(v, toc[2] - 1, mod[2]);
        c = ((ll)c * inv) % mod[2];
    }

    int aa = min(dw, pi);
    dw -= aa; pi -= aa;

    while (dw--)
        c = (c * 2) % mod[2];
    while (pi--)
        c = (c * 5) % mod[2];

    string f;
    stringstream sout;
    int h = 1;
    for (int i = 0; i < k; ++i)
        h *= 10;
    c %= h;
    sout << setw(k) << setfill('0') << c << '\n';
    sout >> f;
    return f;
}

int32_t main(int32_t argc, char** argv)
{
    argc_ = argc; argv_ = argv;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //gen = mt19937(arg(1));

    //cin >> r >> s >> k;
    
    ll r, s, k; cin >> r >> s >> k;
    cout << solve(r, s, k) << '\n';
    return 0;
    int n; cin >> n;

    for (int r = 1; r < n; ++r)
    {
        cerr << r << '\n';
        for (int s = 1; s < n; ++s)
            if (solve(r, s, 1) != bsolve(r, s, 1))
            {
                print(r, s, solve(r, s, 1), bsolve(r, s, 1));
                break;
            }
    }

    cout << solve(r, s, k) << '\n';
    cout << bsolve(r, s, k) << '\n';
}