/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define dbg(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_;if(!c_)cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dprt(...) dbg(prt(__VA_ARGS__))
#define drprt(...) dbg(rprt(__VA_ARGS__))
#define dmp(...) dprt(#__VA_ARGS__, '=',  __VA_ARGS__)
#define rdmp(...) dbg(cerr<<#__VA_ARGS__<<": ";drprt(__VA_ARGS__);)
using namespace std; using ll = long long;
template< typename t > using V = vector< t >;
template< typename t > void prt(const t& a){cout<<a<<'\n';}
template< typename t, typename... v > void prt(const t& a, v&&... b){cout<<a<<' ';prt(b...);}
template< typename t > void rprt(t a, const t& b){while(a!=b)cout<<(*a++)<<' ';cout << '\n';}
/*}}}*/

constexpr int maxn = 1500, maxm = 1e6, maxq = 2e5 + 1e3, logg = 14, inf = 1e9 + 1;

struct Edge
{
    int p, q, w, id;
};

inline bool operator<(const Edge& mn, const Edge& wc)
{
    return mn.w < wc.w;
}

struct Ev
{
    int t, a, b, c;
};

struct Dsu
{
    V< int > tb;
    Dsu(int n):tb(n, -1){}
    int find(int v)
    {
        return tb[v] < 0? v : tb[v] = find(tb[v]);
    }
    bool join(int p, int q)
    {
        p = find(p); q = find(q);

        if (p == q) return false;

        if (tb[p] > tb[q])
            swap(p, q);

        tb[p] += tb[q];

        tb[q] = p;

        return true;
    }
};

int n, m, q;
bool vis[maxm];
int odw[maxn + 1];
int glb[maxn + 1];
Edge tb[maxm];
Ev evs[maxq];
V< pair< int, int > > gr[maxn + 1];
pair< int, int > sk[maxn + 1][logg];

V< int > mst(V< int >& ilo)
{
    Dsu dsu(n + 1);

    for (int i = 1; i <= n; ++i)
        gr[i].clear();

    V< Edge > eds;

    for (int v : ilo)
        eds.push_back(tb[v]);

    sort(all(eds));
    reverse(all(eds));

    V< int > res;

    for (auto& ed : eds)
    {
        if (dsu.join(ed.p, ed.q))
        {
            res.push_back(ed.id);
            gr[ed.p].push_back({ed.q, ed.w});
            gr[ed.q].push_back({ed.p, ed.w});
        }
    }

    return res;
}

void dfs(int v, int oj, int d, int id)
{
    odw[v] = id;

    glb[v] = glb[oj] + 1;
    sk[v][0] = {oj, d};

    for (auto p : gr[v])
        if (p.st != oj)
            dfs(p.st, v, p.nd, id);

}

void build()
{
    for (int i = 1; i <= n; ++i)
        odw[i] = false;

    int t = 1;

    for (int i = 1; i <= n; ++i)
        if (not odw[i])
            dfs(i, i, inf, t), ++t;

    for (int i = 1; i < logg; ++i)
        for (int k = 1; k <= n; ++k)
        {
            sk[k][i].st = sk[sk[k][i - 1].st][i - 1].st;
            sk[k][i].nd = min(sk[k][i - 1].nd, sk[sk[k][i - 1].st][i - 1].nd);
        }
}

int query(int p, int q)
{
    if (glb[p] < glb[q])
        swap(p, q);
    
    int res = inf;

    for (int i = logg - 1; i >= 0; --i)
        if (glb[sk[p][i].st] >= glb[q])
            res = min(res, sk[p][i].nd), p = sk[p][i].st;

    if (p == q)
        return res;

    for (int i = logg - 1; i >= 0; --i)
        if (sk[p][i].st != sk[q][i].st)
        {
            res = min(res, sk[p][i].nd);
            res = min(res, sk[q][i].nd);
            p = sk[p][i].st;
            q = sk[q][i].st;
        }

    res = min(res, sk[p][0].nd);
    res = min(res, sk[q][0].nd);

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    
    for (int i = 0; i < m; ++i)
        cin >> tb[i].p >> tb[i].q >> tb[i].w, tb[i].id = i;

    for (int i = 0; i < q; ++i)
    {
        auto& ev = evs[i];
        cin >> ev.t >> ev.a >> ev.b;

        if (ev.t == 1)
            cin >> ev.c;

        if (ev.t == 2)
            vis[ev.a - 1] = true;
    }

    V< int > tmp;
    for (int i = 0; i < m; ++i)
        if (not vis[i])
            tmp.push_back(i);

    tmp = mst(tmp);

    for (int i = 0; i < m; ++i)
        if (vis[i])
            tmp.push_back(i);

    mst(tmp);

    build();

    for (int i = 0; i < q; ++i)
    {
        dmp(evs[i].t, evs[i].a, evs[i].b, evs[i].c);
        auto q = evs[i];
        if (q.t == 1)
        {
            dmp(q.t);
            if (odw[q.a] != odw[q.b])
            {
                prt("NO"); continue;
            }

            int p = query(q.a, q.b);

            dmp(odw[q.a], odw[q.b], p, q.c);

            if (p >= q.c)
                prt("YES");
            else
                prt("NO");

        }

        if (q.t == 2)
        {
            int v = evs[i].a;
            int c = evs[i].b;
            tb[v - 1].w = c;
            
            mst(tmp); build();

        }
    }

}