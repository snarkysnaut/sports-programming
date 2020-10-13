#include <bits/stdc++.h>
constexpr int nax = 300, kax = nax, mod = 1e9 + 33;
using namespace std;

int n, k, tab[nax + 2], lo[nax + 2], hi[nax + 2], dp[nax + 2][nax + 2][nax + 2],
pr[nax + 1][nax + 1][nax + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> tab[i];

    tab[0] = tab[n + 1] = -1;
    
    for (int i = 1; i <= n; ++i)
    {
        int k = i - 1;
        while (tab[i] < tab[k])
            k = lo[k];
        lo[i] = k;
    }
        
    for (int i = n; i >= 1; --i)
    {
        int k = i + 1;
        while (tab[i] < tab[k])
            k = hi[k];
        hi[i] = k;
    }

    dp[0][0][0] = 1;

    //for (int i = 1; i <= n; ++i)
        //cout << lo[i] << ' ' << hi[i] << '\n';

    for (int i = 1; i <= n; ++i)
    {

        for (int j = 0; j <= n; ++j)
            for (int l = 0; l <= k; ++l)
            {
                pr[i - 1][j][l] = dp[i - 1][j][l] + (j > 0? pr[i - 1][j - 1][l] : 0);
                if (pr[i - 1][j][l] >= mod) pr[i - 1][j][l] -= mod;
            }

        for (int j = 0; j <= n; ++j)
            for (int l = 0; l <= k; ++l)
            {
                int& d = dp[i][j][l];

                d += dp[i - 1][j][l];
                if (d >= mod) d -= mod;

                if (i == j)
                    d += dp[i - 1][j - 1][l];
                if (d >= mod) d -= mod;

                if (j < hi[i] and j > lo[i] and l > 0)
                {
                    if (i == j)
                        d += (j - 2 >= 0? pr[i - 1][j - 2][l - 1] : 0);
                    else
                        d += pr[i - 1][j - 1][l - 1];

                    d -= (lo[i] > 0? pr[i - 1][lo[i] - 1][l - 1] : 0);

                    if (d >= mod) d -= mod;
                    if (d < 0) d += mod;
                }
            }
    }

    int res = 0;

    for (int i = 0; i <= k; ++i)
    {
        res += dp[n][n][i];
        if (res >= mod) res -= mod;
    }
    
    cout << res << '\n';
}