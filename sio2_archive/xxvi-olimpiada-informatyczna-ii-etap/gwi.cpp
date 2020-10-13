#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int nax = 5e5;
constexpr ll inf = 1e18;

ll ans[2], suff[nax + 1];
int n, s, tab[2][nax + 1], res[2][nax + 1], use[2][nax + 1];

inline void solve(int s, int f)
{
    ll su = 0;
    ll naj = inf, v = -1;
    for (int i = 0; i < s; ++i)
    {
        if (i == 0 and s != 1) continue;

        su += (i >= 1? tab[f][i] : 0);
        ll val = su + (i + 1 < n? tab[1 - f][i + 1] : 0);
        val += (i + 2 < n? suff[i + 2] : 0);

        if (val < naj) naj = val, v = i;
    }
    
    //cerr << "solve: "; 
    //cerr << naj << ' ' << v << '\n';

    if (v == -1) return;

    ans[f] = naj;
    res[f][1] = s;

    int pt = 1;

    for (int i = v; i >= 1; --i)
        res[f][++pt] = i;

    if (v + 1 >= n)
        return;

    int lo = (v + 2 < n? use[f][v + 2] : 0);
    int hi = (v + 2 < n? use[1 - f][v + 2] : 0);

    int r = v + 1 + lo;
    if (r >= s)
        ++r;

    int ptlo = r - 1;
    int pthi = r + 1;

    res[f][++pt] = r;

    for (int i = 0; i < lo + hi; ++i)
    {
        int p = (tab[1][pt] < tab[0][pt]);
        if (p == f)
        {
            if (ptlo == s) --ptlo;
            res[f][++pt] = ptlo;
            --ptlo;
        }
        else
        {
            if (pthi == s) ++pthi;
            res[f][++pt] = pthi;
            ++pthi;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    for (int i = 1; i <= n - 1; ++i)
        for (int j = 0; j < 2; ++j)
            cin >> tab[j][i];

    for (int i = n - 1; i >= 1; --i)
    {
        suff[i] = (i < n - 1? suff[i + 1] : 0);
        use[0][i] = (i < n - 1? use[0][i + 1] : 0);
        use[1][i] = (i < n - 1? use[1][i + 1] : 0);

        int p = (tab[1][i] < tab[0][i]);
        suff[i] += tab[p][i];
        ++use[p][i];
    }

    //for (int i = n - 1; i >= 1; --i)
        //cerr << suff[i] << ' ' << use[0][i] << ' ' << use[1][i] << '\n';

    ans[0] = ans[1] = inf;

    solve(s, 0);
    solve(n - s + 1, 1);

    //cerr << ans[0] << ' ' << ans[1] << '\n';

    for (int i = 1; i <= n; ++i)
        res[1][i] = n - res[1][i] + 1;

    //for (int j = 0; j < 2; ++j)
    //{
        //for (int i = 1; i <= n; ++i)
            //cerr << res[j][i] << ' ';
        //cerr << '\n';
    //}

    int p = (ans[0] < ans[1]? 0 : 1);

    cout << ans[p] << '\n';

    for (int i = 1; i <= n; ++i)
        cout << res[p][i] << ' ';
    cout << '\n';
}
