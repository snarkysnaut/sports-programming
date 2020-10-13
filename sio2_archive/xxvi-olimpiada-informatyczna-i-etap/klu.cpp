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

constexpr int nax = 30, maxm = 2e6, inf = 1e9;

int n, m;
int pr[nax * 2];
int os[nax * 2];
int lt[nax * 2];
int tb[maxm];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; ++i)
        cin >> tb[i];

    for (int i = 0; i < nax * 2; ++i)
        pr[i] = inf, os[i] = -1, lt[i] = inf;

    for (int i = 0; i < m; ++i)
        for (int k = 0; k < n; ++k)
        {
            int v = k + (((1 << k) & tb[i])? n : 0);
            pr[v] = min(pr[v], i);
            os[v] = i;
        }

    ll res = 0;

    for (int i = m - 1; i >= 0; --i)
    {
        int lo = i; int hi = m - 2;
        for (int k = 0; k < n; ++k)
        {
            int v = k + (((1 << k) & tb[i])? n : 0);
            lt[v] = i;
        }
        for (int k = 0; k < n * 2; ++k)
            if (pr[k] != inf)
            {
                if (i <= pr[k])
                    hi = min(hi, os[k] - 1);
                lo = max(lo, lt[k]);
            }

        res += max(0, hi - lo + 1);
    }

    print(res);
}