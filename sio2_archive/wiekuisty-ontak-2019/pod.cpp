#include <bits/stdc++.h>
using namespace std;

constexpr int nax = 10000;

int n, m, k, p[nax + 1], q[nax + 1], dp[2][nax + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i)
        cin >> p[i];

    for (int i = 1; i <= m; ++i)
        cin >> q[i];
    
    for (int i = 1; i <= n; ++i)
    {
        int r = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (p[i] == q[j])
                dp[i & 1][j] = r + 1;
            if (__builtin_popcount(q[j] xor p[i]) <= k)
                r = max(r, dp[(i - 1) & 1][j]);
        }

        for (int j = 1; j <= m; ++j)
            dp[i & 1][j] = max(dp[i & 1][j], dp[(i - 1) & 1][j]);

        for (int j = 1; j <= m; ++j)
            dp[(i - 1) & 1][j] = 0;
    }

    cout << *max_element(begin(dp[n & 1]) + 1, begin(dp[n & 1]) + 1 + m) << '\n';
}