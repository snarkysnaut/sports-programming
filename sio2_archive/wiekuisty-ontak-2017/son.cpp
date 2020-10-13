#include <bits/stdc++.h>
#include "csonlib.h"
using namespace std;
using ll = long long;

constexpr ll maxn = 1e12;
constexpr int maxk = 500, maxq = 500;

ll dp[maxq + 1][maxk + 1];

int main()
{
    ll n; int q, k;
    n = dajDlugosc();
    q = dajLimitCzasowy();
    k = dajLiczbeSond();
    
    for (int i = 0; i <= k; ++i)
        dp[0][i] = 1;

    for (int i = 0; i <= q; ++i)
        dp[i][0] = 1;

    for (int i = 1; i <= q; ++i)
        for (int j = 1; j <= k; ++j)
            dp[i][j] = min(maxn, dp[i - 1][j - 1] + dp[i - 1][j]);

    ll lo = 1, hi = n;

    while (lo < hi)
    {
        ll v = dp[q - 1][k - 1] + lo - 1;

        bool fl = false;

        if (v > hi)
            fl = true;
        else
            fl = sprawdz(v);

        if (fl)
            hi = v, --k;
        else
            lo = v + 1;

        --q;
    }
    
    odpowiedz(lo);
}