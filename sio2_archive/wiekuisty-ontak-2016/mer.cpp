#include <bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int nax = 1e5, qax = 5e5;

struct Edge
{
    int p, q, wg;
    Edge() : p(-1), q(-1), wg(-1) {}
    Edge(int p, int q, int wg) : p(p), q(q), wg(wg) {}
};

ll li;
int n, q, cnt[nax + 1], tab[nax + 1], piv;
Edge eds[qax];
vector< pair< int, int > > gr[nax + 1];
map< int, int > rg[nax + 1];

int zlicz(int v)
{
    int bat[nax + 1];

    fill(begin(bat) + 1, begin(bat) + n + 1, 0);

    for (auto& p : gr[v])
        bat[p.first] = p.second;

    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i == v) continue;
        if (i == piv) continue;

        if (tab[v] + bat[i] - tab[i])
            ++res;
    }

    return res;
}

int zlicz(int p, int q)
{
    return (bool)(tab[p] + rg[p][q] - tab[q]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> q;
    
    for (int i = 0; i < q; ++i)
        cin >> eds[i].p >> eds[i].q >> eds[i].wg;

    for (int i = 0; i < q; ++i)
        ++cnt[eds[i].p], ++cnt[eds[i].q];

    piv = min_element(begin(cnt) + 1, begin(cnt) + n + 1) - begin(cnt);
    
    for (int i = 0; i < q; ++i)
    {
        if (eds[i].p == piv or eds[i].q == piv)
        {
            int h = eds[i].p xor eds[i].q xor piv;
            int wg = (eds[i].p != piv? -eds[i].wg : eds[i].wg);
            li -= zlicz(h);
            tab[h] = wg;
            li += zlicz(h);
        }
        else
        {
            li -= zlicz(eds[i].p, eds[i].q);
            gr[eds[i].p].push_back({eds[i].q, eds[i].wg});
            gr[eds[i].q].push_back({eds[i].p, -eds[i].wg});
            rg[eds[i].p][eds[i].q] = eds[i].wg;
            rg[eds[i].q][eds[i].p] = -eds[i].wg;
            li += zlicz(eds[i].p, eds[i].q);
        }

        cout << (li? "YES" : "NO") << '\n';
    }
}