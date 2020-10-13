#include <bits/stdc++.h>
#ifndef dbg
#define dbg(...)
#endif
#define all(x) begin(x), end(x)
#define rsz(...) resize(__VA_ARGS__)
#define psh(...) push_back(__VA_ARGS__)
#define emp(...) emplace_back(__VA_ARGS__)
#define prt(...) print(cout, __VA_ARGS__)
#define dmp(...) print(cerr, #__VA_ARGS__, '=', __VA_ARGS__)
#define dprt(...) dbg(print(cerr,__VA_ARGS__))
#define ddmp(...) dbg(dmp(__VA_ARGS__))
using namespace std;using ll=long long;
template<typename t>using V=vector<t>;
template<typename t>void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... A>void print
(ostream& os, const t& a, A&&... b){os<<a<<' ';print(os, b...);}

constexpr int p = 29;
constexpr int mod = 1e9 + 7;

int n;
string sl;
V< int > pr;
V< int > pt;

inline int hasz (int lo, int hi)
{
    --lo;
    ddmp(lo, hi);
    int odj = (lo == -1? 0 : ((ll)pr[lo] * pt[hi - lo]) % mod);
    int h = pr[hi] - odj;
    return h < 0? h + mod : h;
}

inline bool same (int lo1, int hi1, int lo2, int hi2)
{
    return hasz(lo1, hi1) == hasz(lo2, hi2);
}

inline bool valid (int v)
{
    int lo = 0;
    for (int b = n - v; b >= 1; b >>= 1)
        while (lo + b <= n - v and 
        same(v, v + lo + b - 1, 0, lo + b - 1))
            lo += b;
    
    if (lo == n - v)
        return false;
    return same(v + lo + 1, n - 1, lo + 1, n - v - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> sl;
    pr.rsz(n);
    pt.rsz(n);
    
    pt[0] = 1;
    for (int i = 1; i < n; ++i)
        pt[i] = ((ll)(pt[i - 1]) * p) % mod;
        
    for (int i = 0; i < n; ++i)
        pr[i] = ((ll)(i == 0? 0 : pr[i - 1]) * p + (sl[i] - 'a')) % mod;
    
    for (int i = (n + 1) / 2; i < n; ++i)
        if (valid(i))
            return prt(i), 0;
    
    prt(-1);
}