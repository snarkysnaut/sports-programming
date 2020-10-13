#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int nax = 1e3, maxm = nax;

int n, m, tab[nax + 1][maxm + 1], ilo[nax + 1][maxm + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)    
            cin >> tab[i][j];

    ll res = 0;

    for (int i = 1; i <= n; ++i)
    {
        stack< int > S;
        for (int j = 1; j <= m; ++j)
        {
            tab[i][j] -= min(tab[i][j], ilo[i - 1][j]);
            ilo[i][j] += ilo[i - 1][j];
            while (not S.empty() and tab[i][j])
            {
                int v = S.top(); S.pop();
                int d = min(tab[i][j], ilo[i][v]);
                tab[i][j] -= d;
                ilo[i][v] -= d;
                ilo[i][j] += d;
                if (ilo[i][v]) S.push(v);
            }
            if (tab[i][j])
                ilo[i][j] += tab[i][j], res += tab[i][j], tab[i][j] = 0;
            S.push(j);
        }
    }

    cout << res << '\n';
}