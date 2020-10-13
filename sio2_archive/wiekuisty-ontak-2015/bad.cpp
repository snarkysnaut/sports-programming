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

constexpr int nax = 3e3, inf = 1e9;

int n1, n2, m;
int dp[nax + 2][nax + 2];
int pd[nax + 2][nax + 2];
int lim[nax + 1], mil[nax + 1];
int tab[nax + 1], bat[nax + 1], ilo[nax + 1];

inline void lims(int tb[], int li[], int n)
{
    for (int i = 1; i <= n; ++i)
    {
        int v = 1;
        li[i] = inf;
        for (int k = i; k <= n; ++k)
        {
            if (tb[k] == ilo[v])
                ++v;
            if (v == m + 1) 
            {
                li[i] = k;
                break;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n1;

    for (int i = 1; i <= n1; ++i)
        cin >> tab[i];
    
    cin >> n2;

    for (int i = 1; i <= n2; ++i)
        cin >> bat[i];

    cin >> m;

    for (int i = 1; i <= m; ++i)
        cin >> ilo[i];

    lims(tab, lim, n1);
    lims(bat, mil, n2);

debug(
    for (int i = 1; i <= n1; ++i)
        cout << lim[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n2; ++i)
        cout << mil[i] << ' ';
    cout << '\n';
);

    for (int i = 1; i <= n1; ++i)
        for (int k = 1; k <= n2; ++k)
            dp[i][k] = max({tab[i] == bat[k]? dp[i - 1][k - 1] + 1 : 0, 
            dp[i - 1][k], dp[i][k - 1], dp[i - 1][k - 1]});

    for (int i = n1; i >= 1; --i)
        for (int k = n2; k >= 1; --k)
            pd[i][k] = max({tab[i] == bat[k]? pd[i + 1][k + 1] + 1 : 0, 
            pd[i + 1][k], pd[i][k + 1], pd[i + 1][k + 1]});

    int res = -1;

    if (not m)
        return print(dp[n1][n2]), 0;

    for (int i = 1; i <= n1; ++i)
        for (int k = 1; k <= n2; ++k)
        {
            int hi1 = lim[i] + 1;
            int hi2 = mil[k] + 1;

            if (hi1 > n1 + 1) continue;
            if (hi2 > n2 + 1) continue;

            res = max(res, m + dp[i - 1][k - 1] + pd[hi1][hi2]);
        }

    print(res);
}