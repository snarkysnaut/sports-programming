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

constexpr int nax = 1e5;

int sz[2], tb[2][nax + 1], pr[2][nax + 2], msk[2][nax + 1];

int solve()
{
    for (int i = 0; i < 2; ++i)
        cin >> sz[i];

    for (int i = 0; i < 2; ++i)
        for (int k = 1; k <= sz[i]; ++k)
            cin >> tb[i][k], tb[i][k] = (tb[i][k] & 1) xor tb[i][k - 1];

    for (int i = 0; i < 2; ++i)
    {
        for (int k = 0; k <= sz[i]; ++k)
            msk[i][k] = 3;

        for (int j = 0; j < 2; ++j)
        {
            pr[j][0] = -1;
            for (int k = 1; k <= sz[i]; ++k)
            {
                int l = pr[j][k];
                while (l != -1 and ((tb[i][k] xor tb[i][l]) != j))
                    l = pr[0][l];
                pr[j][k + 1] = l + 1;
            }
            
            for (int v = pr[j][sz[i] + 1]; v >= 1; v = pr[0][v])
                msk[i][sz[i] + 1 - v] -= (1 << j);
        }
    }

    for (int i = min(sz[0], sz[1]); i >= 0; --i)
        if (msk[0][i] bitand msk[1][i])
            return i;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q; cin >> q;
    while (q--) print(solve());
}