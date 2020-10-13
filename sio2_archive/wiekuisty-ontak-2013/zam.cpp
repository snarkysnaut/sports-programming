#include <bits/stdc++.h>
using namespace std;

constexpr int nax = 300;

int n, m, k, tab[nax + 1][nax + 1], dp[4][nax + 1][nax + 1], pd[2][nax + 1][nax + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> tab[i][j];

    multiset< int > S;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            S.insert(tab[i][j]);
            if (S.size() > k) S.erase(S.begin());
        }

    int su = 0;
    for (int v : S) su += v;

    if (su < 0) return cout << su << '\n', 0;

    for (int i = 1; i <= n; ++i)
    {
        int ilo[nax + 1];
        for (int j = 1; j <= m; ++j) 
            ilo[j] = 0;
        for (int j = i; j <= n; ++j)
        {
            for (int k = 1; k <= m; ++k)
                ilo[k] += tab[j][k];

            int su = 0, naj = 0;
            for (int k = 1; k <= m; ++k)
            {
                su += ilo[k];
                if (su < 0) su = 0;
                naj = max(naj, su);
                dp[0][j][k] = max(dp[0][j][k], su);
                dp[1][i][k] = max(dp[1][i][k], su);
            }

            su = 0;
            for (int k = m; k >= 1; --k)
            {
                su += ilo[k];
                if (su < 0) su = 0;
                dp[2][j][k] = max(dp[2][j][k], su);
                dp[3][i][k] = max(dp[3][i][k], su);
            }

            pd[0][i][j] = naj;
        }
    }

    for (int j = 1; j <= m; ++j)
    {
        int ilo[nax + 1];
        for (int i = 1; i <= n; ++i)
            ilo[i] = 0;
        for (int k = j; k <= m; ++k)
        {
            for (int i = 1; i <= n; ++i)
                ilo[i] += tab[i][k];

            int su = 0, naj = 0;
            for (int i = 1; i <= n; ++i)
            {
                su += ilo[i];
                if (su < 0) su = 0;
                naj = max(naj, su);
            }

            pd[1][j][k] = naj;
        }
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[0][i][j] = max({dp[0][i][j], dp[0][i - 1][j], dp[0][i][j - 1]});

    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= m; ++j)
            dp[1][i][j] = max({dp[1][i][j], dp[1][i + 1][j], dp[1][i][j - 1]});

    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= 1; --j)
            dp[2][i][j] = max({dp[2][i][j], dp[2][i - 1][j], dp[2][i][j + 1]});

    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j)
            dp[3][i][j] = max({dp[3][i][j], dp[3][i + 1][j], dp[3][i][j + 1]});

    for (int i = n; i >= 1; --i)
        for (int j = i + 1; j <= n; ++j)
            pd[0][i][j] = max({pd[0][i][j], pd[0][i + 1][j], pd[0][i][j - 1]});

    for (int j = m; j >= 1; --j)
        for (int k = j + 1; k <= m; ++k)
            pd[1][j][k] = max({pd[1][j][k], pd[1][j + 1][k], pd[1][j][k - 1]});

    if (k == 1)
        return cout << dp[0][n][m] << '\n', 0;
    if (k == 2)
    {
        int res = 0;
        for (int i = 1; i < n; ++i)
            res = max(res, dp[0][i][m] + dp[1][i + 1][m]);
        for (int j = 1; j < m; ++j)
            res = max(res, dp[0][n][j] + dp[2][n][j + 1]);
        return cout << res << '\n', 0;
    }
    if (k == 3)
    {
        int res = 0;
        for (int i = 1; i < n; ++i)
            for (int j = 1; j < m; ++j)
            {
                res = max(res, dp[0][i][m] + dp[1][i + 1][j] + dp[3][i + 1][j + 1]);
                res = max(res, dp[1][i + 1][m] + dp[0][i][j] + dp[2][i][j + 1]);
                res = max(res, dp[0][n][j] + dp[2][i][j + 1] + dp[3][i + 1][j + 1]);
                res = max(res, dp[2][n][j + 1] + dp[0][i][j] + dp[1][i + 1][j]);
            }

        for (int i = 1; i < n - 1; ++i)
            for (int j = i + 1; j < n; ++j)
                res = max(res, pd[0][1][i] + pd[0][i + 1][j] + pd[0][j + 1][n]);

        for (int j = 1; j < m - 1; ++j)
            for (int k = j + 1; k < m; ++k)
                res = max(res, pd[1][1][j] + pd[1][j + 1][k] + pd[1][k + 1][m]);
                
        return cout << res << '\n', 0;
    }
}
