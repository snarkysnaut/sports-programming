/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;if(!(--c_))cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
#define dump(...) debug(print(#__VA_ARGS__, " = ", __VA_ARGS__))
using namespace std; using ll = long long;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, v&&... b){cout<<a<<(sizeof...(b)? " " : "");print(b...);}
template< typename t > using V = vector< t >;
/*}}}*/

constexpr int nax = 5e5, logg = 62;

int n, m;
ll tab[nax];
V< int > ilo;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> tab[i];

    for (int i = 1; i < n; ++i)
        tab[i] xor_eq tab[i - 1];

    ilo.resize(n);
    iota(all(ilo), 0);
    
    ll res = 0;
    for (int i = logg; i >= 0; --i)
    {
        V< int > nilo;

        bool fl = false;

        for (int v : ilo)
            if (not (tab[v] & (1ll << i)))
                nilo.push_back(v), fl |= (v == n - 1);

        if (nilo.size() >= m and fl)
            ilo = move(nilo);
        else res += (1ll << i);
    }
    print(res);
}