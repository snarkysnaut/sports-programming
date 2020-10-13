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

constexpr int maxn = 15e4, maxm = 15e4, logg = 20;

int n, m;
int lc[maxm];
int glb[maxn + 1];
V< int > gr[maxn + 1];
int sk[maxn + 1][logg];
pair< int, int > eds[maxm];
int res = -1, v1 = -1, v2 = -1;
int pre[maxn + 1], erp[maxn + 1];
V< pair< int, int > > tb[maxn + 1];
V< pair< int, int > > bt[maxn + 1];
set< pair< int, int > > S[maxn + 1];

void dfs(int v)
{
    static int t = -1;
    pre[v] = ++t;
    erp[t] = v;
    
    for (int s : gr[v])
        sk[s][0] = v, glb[s] = glb[v] + 1, dfs(s);
}

inline int lca(int a, int b)
{
    if (glb[a] < glb[b])
        swap(b, a);

    for (int i = logg - 1; i >= 0; --i)
        if (glb[sk[a][i]] >= glb[b])
            a = sk[a][i];

    if (a == b)
        return a;

    for (int i = logg - 1; i >= 0; --i)
        if (sk[a][i] != sk[b][i])
            a = sk[a][i], b = sk[b][i];

    return sk[a][0];
}

inline void spr(int a, int b)
{
    if (a == b) return;
    auto p = eds[a];
    auto q = eds[b];

    int w = lca(lc[a], lc[b]);
    w = w == lc[a]? lc[b] : lc[a];

    V< V< int > > ilo(2, V< int >(2));
    tie(ilo[0][0], ilo[0][1]) = p;
    tie(ilo[1][0], ilo[1][1]) = q;

    int rs = 0;

    for (int i = 0; i < 2; ++i)
        for (int k = 0; k < 2; ++k)
        {
            int t = lca(ilo[0][i], ilo[1][k]);
            rs += max(0, glb[t] - glb[w]);
        }

    if (rs > res)
        res = rs, v1 = a + 1, v2 = b + 1;
}

void merge(int a, int b)
{
    bool fl = false;
    if (S[a].size() < S[b].size())
        swap(a, b), fl = true;

    for (auto q : S[b])
    {
        auto it = S[a].insert(q).first;

        if (it != S[a].begin())
            spr((*prev(it)).nd, (*it).nd);
            
        if ((next(it)) != S[a].end())
            spr((*it).nd, (*next(it)).nd);
    }

    if (fl)
        swap(S[a], S[b]);
}

void dfs2(int v)
{
    for (int s : gr[v]) 
    {
        dfs2(s);
        merge(v, s);
    }

    for (auto& p : tb[v])
    {
        auto it = S[v].insert(p).first;

        if (it != S[v].begin())
            spr((*it).nd, (*prev(it)).nd);

        if (next(it) != S[v].end()) 
            spr((*it).nd, (*next(it)).nd);
    }

    for (auto& p : bt[v])
    {
        auto it = S[v].find(p);

        it = S[v].erase(it);

        if (S[v].empty() or it == S[v].begin())
            continue;

        --it;

        if (it != S[v].begin())
            spr((*it).nd, (*prev(it)).nd);

        if (next(it) != S[v].end()) 
            spr((*it).nd, (*next(it)).nd);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 2; i <= n; ++i)
    {
        int v; cin >> v;
        gr[v].push_back(i);
    }

    for (int i = 0; i < m; ++i)
        cin >> eds[i].st >> eds[i].nd;
        
    dfs(1);

    sk[1][0] = 1;

    for (int i = 1; i < logg; ++i)
        for (int v = 1; v <= n; ++v)
            sk[v][i] = sk[sk[v][i - 1]][i - 1];

    for (int i = 0; i < m; ++i)
    {
        tb[eds[i].st].push_back({pre[eds[i].nd], i});
        tb[eds[i].nd].push_back({pre[eds[i].st], i});

        lc[i] = lca(eds[i].st, eds[i].nd);

        bt[lc[i]].push_back({pre[eds[i].st], i});
        bt[lc[i]].push_back({pre[eds[i].nd], i});
    }

    dfs2(1);

    prt(res);
    prt(v1, v2);
}