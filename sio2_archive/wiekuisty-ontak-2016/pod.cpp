#include <bits/stdc++.h>

constexpr int nax = 5e5, alf = 26, inf = 1e9;

using namespace std;
using Dp = array< array< int, 2 >, nax + 1 >;
using Aia = array< int, alf >;
using Pts = array< Aia, nax + 1 >;

int solve(const int n, const int k, const string& p, const string& q)
{
    Dp dp;
    Pts pts;
    Aia cur;

    for (int i = 0; i < alf; ++i)
        cur[i] = n + 1;

    for (int i = n; i >= 0; --i)
    {
        pts[i] = cur;
        if (i > 0)
            cur[p[i - 1] - 'a'] = i;
    }

    for (int i = 0; i <= k; ++i)    
        for (int j = 0; j < 2; ++j)
            dp[i][j] = -inf;

    dp[0][0] = 0;

    for (int i = 0; i < k; ++i)
        for (int j = 0; j < 2; ++j)
        {
            if (dp[i][j] == -inf) continue;
            int v = q[i] - 'a';

            if (dp[i][j] <= n)
                dp[i + 1][j] = max(dp[i + 1][j], pts[dp[i][j]][v]);

            if (j == 0)
                dp[i + 1][1] = max(dp[i + 1][1], dp[i][j]);
        }

    return dp[k][1] == -inf? -1 : dp[k][1];
}




int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string p, q;
    cin >> n >> k >> p >> q;
    cout << solve(n, k, p, q) << '\n';
}