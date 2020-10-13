#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define dbg(...) {if(!c_)cerr<<"\033[96;1m";++c_; \
__VA_ARGS__;--c_;if(!c_)cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define st first
#define nd second
#define flg() __LINE__, __PRETTY_FUNCTION__
#define mkp(...) make_pair(__VA_ARGS__)
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) dprt(#__VA_ARGS__, __VA_ARGS__)
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template< typename t > using V = vector< t >;
template< typename t > void print(ostream& os, const t& a){os<<a<<'\n';}
template< typename t, typename... v > void print(ostream& os, const t& a, 
v&&... b){os << a << ' '; print(os, b...);}

constexpr int maxn = 2000, logg = 12;

int n, m;
int glb[maxn + 1], ojc[maxn + 1];
bool vis[maxn + 1];
int dp[maxn + 1][1 << logg];
V< pair< int, int > > gr[maxn + 1];

void dfs(int v, int oj)
{
    vis[v] = true;
    ojc[v] = oj;
    glb[v] = glb[oj] + 1;

    V< pair< int, int > > zwr, syn;

    for (auto& p : gr[v])
    {
        if (p.st == oj)
            continue;
        if (vis[p.st])
        {
            if (glb[p.st] < glb[v])
            {
                zwr.push_back(p);
                if (glb[v] - glb[p.st] + 1 >= logg + 1)
                {
                    prt("BEZSENSOWNE");

                    prt(glb[v] - glb[p.st] + 1);

                    while (glb[v] >= glb[p.st])
                    {
                        cout << v << ' ';
                        
                        if (v == ojc[v]) break;

                        v = ojc[v];
                    }

                    cout << '\n';
                    exit(0);
                }
            }
        }
        else
        {
            syn.push_back(p);
            dfs(p.st, v);
        }
    }

    for (int i = 0; i < (1 << logg); ++i)
    {
        for (auto& p : zwr)
        {
            int q = glb[v] - glb[p.st];
            if ((bool)(i & 1) == (bool)(i & (1 << q)))
                dp[v][i] += p.nd;
        }

        for (auto& p : syn)
        {
            int msk = (i << 1) & ((1 << logg) - 1);
            int w = (bool)(i & 1);
            dp[v][i] += min(dp[p.st][msk] + (not w? p.nd : 0),
            dp[p.st][msk + 1] + (w? p.nd : 0));
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        gr[a].push_back({b, w});
        gr[b].push_back({a, w});
    }

    int res = 0;

    for (int i = 1; i <= n; ++i)
        if (not vis[i])
        {
            dfs(i, i);
            int rs = INT_MAX;
            for (int k = 0; k < (1 << logg); ++k)
                rs = min(rs, dp[i][k]);

            res += rs;
        }

                
dbg(
    for (int i = 1; i <= n; ++i)
        for (int m = 0; m < (1 << logg); ++m)
            dprt(i, m, dp[i][m]);
);
    prt("GRAMY");
    prt(res);

}