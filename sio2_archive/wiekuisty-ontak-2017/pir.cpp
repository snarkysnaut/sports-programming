#include <bits/stdc++.h>
#ifndef dbg
#define dbg(...)
#endif
#define popcount(x) __builtin_popcount(x)
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

constexpr ll MaxRes = 1e18;

int n, m;
V< ll > tb;
V< pair< ll, int > > ilo;

inline void gen ()
{
    for (int i = 1; i < (1 << tb.size()); ++i)
    {
        ll a = 1;
        for (int k = 0; k < tb.size(); ++k)
            if ((1 << k) & i)
            {
                a /= __gcd(tb[k], a); 
                a *= tb[k];
            }
        ilo.psh({a, (popcount(i) & 1)? 1 : -1}); 
    }
}

inline ll foo (ll v)
{
    ll res = 0;
    for (auto& p : ilo)
        res += v / p.first * p.second;
    return res;
}

inline ll licz (ll v)
{
    ll lo = 0;
    for (ll b = MaxRes; b >= 1; b >>= 1)
        while (lo + b <= MaxRes and foo(lo + b) < v)
            lo += b;
    return ++lo;    
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;    

    tb.rsz(n);
    for (ll& i : tb)
        cin >> i;
    
    gen();    
        
    for (int i = 0; i < m; ++i)
    {
        ll v; cin >> v;
        prt(licz(v));
    }
}