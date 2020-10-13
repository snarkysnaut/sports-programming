#include <bits/stdc++.h>
using namespace std;

template< typename t > using V = vector< t >;

constexpr int tax = 10, nax = 200, kax = 5;

int t;
int tab[kax][nax];
bool vis[nax][nax];
V< pair< int, int > > gr[nax][nax];

void dfs(int i, int j)
{
    vis[i][j] = true;
    for (auto& p : gr[i][j])
        if (not vis[p.first][p.second])
            dfs(p.first, p.second);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while (t--)
    {
        int n, k; cin >> n >> k;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                gr[i][j].clear();

        for (int i = 0; i < k; ++i)
            for (int j = 0; j < n; ++j)
                cin >> tab[i][j];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int l = 0; l < k; ++l)
                {
                    int ni = tab[l][i];
                    int nj = tab[l][j];
                    gr[ni][nj].push_back({i, j});
                }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                vis[i][j] = false;

        dfs(0, 0);
        
        bool fl = true;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (not vis[i][j])
                    fl = false;

        cout << (fl? "TAK" : "NIE") << '\n';
    }
}