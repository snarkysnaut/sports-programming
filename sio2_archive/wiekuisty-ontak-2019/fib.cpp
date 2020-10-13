#pragma GCC optimize("O3")
/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_ = 0;
#define cout (c_?cerr:cout)
#define debug(...) \
{if(!c_++)cerr<<"\033[96;1m"; \
__VA_ARGS__; \
if(!--c_)cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define assrt(...) debug(\
if (not (__VA_ARGS__)) \
    exit((cerr << __LINE__ << ": " << #__VA_ARGS__ << '\n', 0));\
)
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long; using ld = long double;
template < typename t > using V = vector< t >;
template < typename t, size_t s > using A = array< t, s >;
void print() {cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{ while (a != b) cout << (*a++) << ' '; cout << '\n';}
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__ << ": "; print_range(__VA_ARGS__))
/*}}}*/

constexpr int tax = 100, nax = 2e6;

int t, n, k, tab[nax + 2];

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> tab[i];
        cin >> k;
        
        for (int i = n; i >= 2; --i)
            while (tab[i] % k)
                --tab[i], ++tab[i - 1], ++tab[i - 2];

        tab[1] += tab[0], tab[0] = 0;

        for (int i = n; i >= 1; --i)
            tab[i] /= k;

        bool fl = true;
        while (fl)
        {
            fl = false;
                
            for (int i = 2; i <= n - 1; ++i)
                while (tab[i] and tab[i - 1])
                    ++tab[i + 1], --tab[i], --tab[i - 1], fl = true;

            for (int i = n - 1; i >= 2; --i)
                while (tab[i] and tab[i] % 2 == 0)
                    ++tab[i + 1], ++tab[i - 2], tab[i] -= 2, fl = true;

            tab[1] += tab[0], tab[0] = 0;
            tab[2] += (tab[1] / 2);
            tab[1] %= 2;
        }

        int r = 0;
        for (int i = 1; i <= n; ++i)
            if (tab[i]) r = i;

        tab[0] = 0;
        cout << r << ' ';
        for (int i = 1; i <= r; ++i)
            cout << tab[i] << ' ', tab[i] = 0;
        cout << '\n';
    }
}