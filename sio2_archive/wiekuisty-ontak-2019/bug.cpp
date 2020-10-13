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

constexpr int tax = 30, nax = 10, maxm = 350, inf = 1e9;

int t, n, m, k, sum[nax + 1][maxm + 1], dp[4][1 << (2 * nax)];
bool lav[4][1 << (2 * nax)];
V< int > val[4];

int fsum(const int x1, const int y1, const int x2, const int y2)
{
    if (x1 < 1 or x1 > n or x2 < 1 or x2 > n or y1 < 1 or y1 > m or y2 < 1 or y2 > m)
    {
        dump(x1, y1, x2, y2, inf);
        return inf;
    }
    else 
    {
        int val = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
        dump(x1, y1, x2, y2, val);
        return val;
    }
}

void update(const int f, const int s, const int v)
{
    if (not lav[f][s])
    {
        lav[f][s] = true;
        val[f].push_back(s);
        dp[f][s] = v;
    }
    else dp[f][s] = max(dp[f][s], v);
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while (t--)
    {
        cin >> m >> n >> k;

        dump(n, m);

        for (int i = 1; i <= k; ++i)
        {
            int x, y; cin >> x >> y;
            ++sum[y][x]; //sus
        }

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + sum[i][j];

        int f = 0;
        val[f].push_back(0);
        lav[f][0] = true;
        for (int j = 1; j <= m; ++j)
            for (int i = 1; i <= n; ++i)
            {
                for (int s : val[f])
                {
                    {
                        bool b = ((s & 3) >> 1);
                        int ns = (s >> 2) + b * (1 << (2 * (n - 1)));
                        int nf = f + 1; if (nf >= 4) nf -= 4;
                        update(nf, ns, dp[f][s]);
                    }

                    if ((fsum(i, j, i + 1, j + 2) == 0) and not (s & ((1 << 4) - 1)))
                    {
                        int ns = (s >> 4);
                        for (int i = 2 * (n - 2); i < 2 * n; ++i)
                            ns += (1 << i);
                        int nf = f + 2; if (nf >= 4) nf -= 4;
                        update(nf, ns, dp[f][s] + 1);
                    }

                    if ((fsum(i, j, i + 2, j + 1) == 0) and not (s & ((1 << 6) - 1)))
                    {
                        int ns = (s >> 6);
                        for (int i = 2 * (n - 3); i < 2 * n; i += 2)
                            ns += (1 << i);
                        int nf = f + 3; if (nf >= 4) nf -= 4;
                        update(nf, ns, dp[f][s] + 1);
                    }
                }

                for (int s : val[f])
                    lav[f][s] = false, dp[f][s] = 0;
                val[f].clear();

                f = f + 1; if (f >= 4) f -= 4;
            }

        int res = 0;
        for (int s : val[f])
        {
            dump(s, dp[f][s]);
            res = max(res, dp[f][s]);
        }

        print(res);
        
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                sum[i][j] = 0;

        for (int i = 0; i < 4; ++i)
        {
            for (int s : val[i])
                dp[i][s] = 0, lav[i][s] = false;
            val[i].clear();
        }
    }
}