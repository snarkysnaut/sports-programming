#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int maxk = 200, maxn = 1e6, mod = 1e9 + 7;

int n, k;
int sil[maxn + 1], odw[maxn + 1];
int dp[maxk * 2 + 1][maxk + 1][maxk + 1];
int sum[maxk * 2 + 1][maxk + 1][maxk + 1];

inline int fpow(int v, int w)
{
    int r = 1;
    while (w)
    {
        if (w & 1) 
            r = ((ll)r * v) % mod;
        v = ((ll)v * v) % mod;
        w >>= 1;
    }
    return r;
}

inline int binom(int g, int d)
{
    d = ((ll)odw[d] * odw[g - d]) % mod;
    return ((ll)sil[g] * d) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    sil[0] = 1;

    for (int i = 1; i <= n; ++i)
        sil[i] = ((ll)sil[i - 1] * i) % mod;

    odw[n] = fpow(sil[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        odw[i] = ((ll)odw[i + 1] * (i + 1)) % mod;

    dp[0][k][0] = 1;
    for (int i = 1; i <= min(n, k * 2); ++i)
        for (int j = 0; j <= k; ++j)
        {
            for (int l = 1; l <= k; ++l)
            {
                if (j < k)
                    dp[i][j][l] = ((ll)dp[i - 1][j + 1][l - 1] * (j + 1)) % mod;

                if (l < k)
                    dp[i][j][l] = (dp[i][j][l] + sum[i - 1][j][l + 1]) % mod;
            }

            for (int l = k; l >= 1; --l)
                sum[i][j][l] = (dp[i][j][l] + (l < k? sum[i][j][l + 1] : 0)) % mod;
        }

    int rs = 0;
    for (int i = 1; i <= min(n, k * 2); ++i)
        for (int j = 0; j <= k; ++j)
            for (int l = 1; l <= k; ++l)
                if (dp[i][j][l])
                    rs = (rs + (ll)dp[i][j][l] * binom(n - i + i - 1, i - 1)) % mod;

    cout << rs << '\n';
}