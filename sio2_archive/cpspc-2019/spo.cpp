#include <bits/stdc++.h>
#define st first
#define nd second
using namespace std;
using ll = long long;

constexpr int nax = 1e5, maxm = 5e5;
constexpr ll inf = 1e18;

int n, m, tab[2];
ll odl[2][nax + 1];
vector< pair< int, int > > gr[2][nax + 1];

void dijkstra(const int f)
{
    for (int i = 1; i <= n; ++i)
        odl[f][i] = inf;
    odl[f][tab[f]] = 0;
    set< pair< ll, int > > S;
    S.insert({odl[f][tab[f]], tab[f]});
    while (not S.empty())
    {
        ll dl; int v;
        tie(dl, v) = *S.begin(); S.erase(S.begin());
        if (dl > odl[f][v])
            continue;
        for (auto& p : gr[f][v])
            if (odl[f][p.st] > dl + p.nd)
            {
                odl[f][p.st] = dl + p.nd;
                S.insert({odl[f][p.st], p.st});
            }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> tab[0] >> tab[1];

    for (int i = 0; i < m; ++i)
    {
        int p, q, w; cin >> p >> q >> w;
        gr[0][p].push_back({q, w});
        gr[1][q].push_back({p, w});
    }

    for (int i = 0; i < 2; ++i)
        dijkstra(i);

    for (int i = 1; i <= n; ++i)
        for (auto& p : gr[0][i])
            if (odl[0][i] + p.nd + odl[1][p.st] == odl[0][tab[1]] + 1)
                return cout << ("YES") << '\n', 0;
    cout << ("NO") << '\n';
}