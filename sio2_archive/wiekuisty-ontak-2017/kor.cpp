#include <bits/stdc++.h>
#ifdef DBG
#define dbg(...) {cerr<<"\033[96;1m";ostream& cout=cerr;__VA_ARGS__; \
(void)(cout);cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define st first
#define nd second
#define flg() __LINE__, __PRETTY_FUNCTION__
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(prt(__VA_ARGS__))
#define dmp(...) print(cout, #__VA_ARGS__, __VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
using namespace std; using ll = long long;
template<typename... t> using V = vector<t...>;
template<typename t>void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... v>void print(ostream& os, const t& a,
v&&... b){os<<a<<' ';print(os,b...);}

constexpr int maxn = 2e5, logg = 19, rz = (1 << logg);

int n, t;
int pre[2][maxn + 1], pos[2][maxn + 1];
V< int > gr[2][maxn + 1];
V< int > tree[rz << 1];

void dfs(int v, int f)
{
    pre[f][v] = ++t;
    for (int s : gr[f][v])
        dfs(s, f);
    pos[f][v] = ++t;
}

inline void insert(int lo, int hi, int c)
{
    lo += rz; hi += rz;

    tree[lo].push_back(c);

    if (lo != hi)
        tree[hi].push_back(c);

    while ((lo >> 1) != (hi >> 1))
    {
        if ((lo & 1) == 0)
            tree[lo + 1].push_back(c);
        if ((hi & 1) == 1)
            tree[hi - 1].push_back(c);

        lo >>= 1; hi >>= 1;
    }
}

inline int query(int v, int tl, int th)
{
    int r = 0;
    for (v += rz; v >= 1; v >>= 1)
    {
        r += upper_bound(all(tree[v]), th) - begin(tree[v]);
        r -= lower_bound(all(tree[v]), tl) - begin(tree[v]);
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < 2; ++i)
        for (int k = 2; k <= n; ++k)
        {
            int v; cin >> v;
            gr[i][v].push_back(k);
        }

    for (int i = 0; i < 2; ++i)
        t = -1, dfs(1, i);

    for (int i = 1; i <= n; ++i)
        insert(0, pre[0][i],  pre[1][i]);

    for (int i = 0; i < (rz << 1); ++i)
        if (not tree[i].empty())
            sort(all(tree[i]));

    for (int i = 1; i <= n; ++i)
        cout << (query(pre[0][i], pre[1][i] + 1, pos[1][i]) - 
                 query(pos[0][i], pre[1][i] + 1, pos[1][i])) << ' ';
    cout << '\n';
}