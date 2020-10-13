/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;if(!(--c_))cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
#define dump(...) debug(print(#__VA_ARGS__, " = ", __VA_ARGS__))
using namespace std; using ll = long long;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, v&&... b){cout<<a<<(sizeof...(b)? " " : "");print(b...);}
template< typename t > using V = vector< t >;
/*}}}*/

constexpr int nax = 1e6, logg = 21;

int n, m, k;
V< int > gr[nax + 1];
int glb[nax + 1], sk[nax + 1][logg];

void dfs(int v, int oj)
{
    sk[v][0] = oj;
    glb[v] = glb[oj] + 1;
    for (int s : gr[v])
        if (s != oj)
            dfs(s, v);
}

inline int jump(int v, int a)
{
    for (int i = logg - 1; i >= 0; --i)
        if ((1 << i) & a)
            v = sk[v][i];
    return v;
}

int lca(int a, int b)
{
    if (glb[a] < glb[b]) swap(a, b);
    
    for (int i = logg - 1; i >= 0; --i)
        if (glb[sk[a][i]] >= glb[b])
            a = sk[a][i];

    if (a == b) return b;

    for (int i = logg - 1; i >= 0; --i)
        if (sk[a][i] != sk[b][i])
            a = sk[a][i], b = sk[b][i];

    return sk[a][0];
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 0; i < n - 1; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].push_back(q);
        gr[q].push_back(p);
    }
    
    dfs(1, 1);

    for (int i = 1; i < logg; ++i)
        for (int k = 1; k <= n; ++k)
            sk[k][i] = sk[sk[k][i - 1]][i - 1];

    while (k--)
    {
        int w, t; cin >> w >> t;
        int c = lca(m, w);
        if (glb[m] - glb[c] <= t) t -= glb[m] - glb[c];
        else
        {
            m = jump(m, t);
            cout << m << ' ';
            continue;
        }
        if (t >= glb[w] - glb[c])
        {
            m = w;
            cout << m << ' ';
            continue;
        }
        m = jump(w, (glb[w] - glb[c]) - t);
        cout << m << ' ';
    }

    cout << '\n';
}