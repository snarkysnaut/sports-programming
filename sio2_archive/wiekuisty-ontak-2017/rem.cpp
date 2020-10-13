#include <bits/stdc++.h>
#ifndef DBG
#define dbg(...)
#else
#define dbg(...) {cerr << "\033[1;96m"; ostream& cout = cerr; \
(void)(cout); __VA_ARGS__; cerr << "\033[0m";} 
#endif
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) print(cerr, #__VA_ARGS__, '=', __VA_ARGS__)
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
using namespace std; using ll = long long;
template< typename... t > using V = vector< t... >;
template< typename t > void print(ostream& os, const t& a)
{os << a <<  '\n';} template< typename t, typename... v >
void print(ostream& os, const t& a, v&&... b){os << a << ' '; print(os, b...);}

constexpr int maxn = 2e5, logg = 19, rozm = (1 << logg);

int n;
int sk[maxn + 1][logg];
V< int > gr[maxn + 1];
int tree[(1 << logg) << 1];
int glb[maxn + 1], pre[maxn + 1], post[maxn + 1];

void dfs1(int v, int oj)
{
    static int t = -1;

    sk[v][0] = oj;
    glb[v] = glb[oj] + 1;
    pre[v] = ++t;

    for (int s : gr[v])
        if (s != oj)
            dfs1(s, v);

    post[v] = ++t;
}

inline void insert(int v, int co = 1)
{
    v += rozm;
    for (; v >= 1; v >>= 1)
        tree[v] += co;
}

inline int sum(int lo, int hi)
{
    lo += rozm; hi += rozm;
    int res = tree[lo] + (lo != hi) * tree[hi];

    while ((lo >> 1) != (hi >> 1))
    {
        if ((lo & 1) == 0)
            res += tree[lo + 1];
        if ((hi & 1) == 1)
            res += tree[hi - 1];
        lo >>= 1; hi >>= 1;
    }

    return res;
}

inline int lca(int a, int b)
{
    if (glb[b] > glb[a])
        swap(a, b);

    for (int i = logg - 1; i >= 0; --i)
        if (glb[sk[a][i]] >= glb[b])
            a = sk[a][i];

    if (a == b)
        return a;

    for (int i = logg - 1; i >= 0; --i)
        while (sk[a][i] != sk[b][i])
            a = sk[a][i], b = sk[b][i];

    return sk[a][0];
}

inline bool query(int a, int b)
{
    int l = lca(a, b);
    return (not sum(pre[l], pre[a])) and (not sum(pre[l], pre[b]));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        
    cin >> n;

    for (int i = 0; i < n - 1; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].push_back(q);
        gr[q].push_back(p);
    }

    dfs1(1, 1);

    for (int j = 1; j < logg; ++j)
        for (int i = 1; i <= n; ++i)
            sk[i][j] = sk[sk[i][j - 1]][j - 1];

    int q; cin >> q;
    while (q--)
    {
        char c; cin >> c;
        
        if (c == '?')
        {
            int p, q; cin >> p >> q;
            prt(query(p, q)? "TAK" : "NIE");
        }
        if (c == '+')
        {
            int v; cin >> v;
            insert(pre[v]);
            insert(post[v], -1);
        }
        if (c == '-')
        {
            int v; cin >> v;
            insert(pre[v], -1);
            insert(post[v]);
        }
    }
}