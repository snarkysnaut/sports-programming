/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define debug(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) debug(print(#__VA_ARGS__, '=',  __VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
using namespace std; using ll = long long; 
template< typename t > using V = vector< t >; void print(){cout<<'\n';}
template< typename t, typename... v > void print(const t& a, v&&... b)
{cout << a << (sizeof...(b)? " " : ""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
/*}}}*/

constexpr int maxn = 1e6;

int n;
V< ll > ilo;
ll tb[maxn + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> tb[i];

    for (int i = 1; i <= n; ++i)
        tb[i] += tb[i - 1];

    dump_range(tb, tb + n + 1);
    dump(tb[n]);

    if (tb[n] & 1)  
        return print(0), 0;

    for (int lo = 0, hi = 0; hi <= n; ++hi)
    {
        while (tb[hi] - tb[lo] > tb[n] / 2)
            ++lo;

        if (tb[hi] - tb[lo] == tb[n] / 2)
        {
            ilo.push_back(tb[lo]);
            dump(lo, hi);
        }
    }

    ll res = 0;

    ll hlf = tb[n] / 2;
    ll q = hlf / 2;

    dump_range(all(ilo));

    if (ilo.size() <= 1)    
        return print(0), 0;

    for (int i = 0; i < (int)ilo.size() - 1; ++i)
    {
        auto it = upper_bound(all(ilo), ilo[i] + q);

        for (int k = 0; k < 2; ++k)
        {
            if (it != ilo.end())
            {
                ll a = (*it) - ilo[i];
                dump(a);
                res = max(res, (hlf - a) * a);
            }
            if (k < 1)
                --it;
        }
    }

    print(res);
}