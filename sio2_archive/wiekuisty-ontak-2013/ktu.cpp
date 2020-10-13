/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define dbg(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) dbg(print(#__VA_ARGS__, __VA_ARGS__))
#define dump_range(...) dbg(cerr<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
using namespace std; using ll = long long; 
template< typename t > using V = vector< t >; void print(){cout<<'\n';}
template< typename t, typename... v > void print(const t& a, v&&... b)
{cout << a << ' '; print(b...);}
template< typename t > void print_range(t a, const t& b)
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
/*}}}*/

constexpr int maxn = 5e5;

int n;
int tb[maxn];
int dp[maxn + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> tb[i];

    sort(tb, tb + n);

    fill(dp, dp + n, -1);
    dp[n] = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        for (int v : {tb[i], tb[i] + 1})
        {
            int s = i + v;
            if (s > n) continue;
            if (dp[s] == -1) continue;
            if (not (tb[s - 1] == v or tb[s - 1] + 1 == v)) continue;
            dp[i] = max(dp[i], dp[s] + 1);
        }
    }

    print(dp[0]);

}