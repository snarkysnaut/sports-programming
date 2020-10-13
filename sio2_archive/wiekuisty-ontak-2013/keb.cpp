#include <bits/stdc++.h>
#ifndef DBG
#define dbg(...)
#else
#define dbg(...) {cerr << "\033[1;96m"; __VA_ARGS__; cerr << "\033[0m";} 
#endif
#define bgn(...) begin(__VA_ARGS__)
#define rsz(...) resize(__VA_ARGS__)
#define emp(...) emplace_back(__VA_ARGS__)
#define psh(...) push_back(__VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) print(cerr, #__VA_ARGS__, '=', __VA_ARGS__)
#define all(...) bgn(__VA_ARGS__), end(__VA_ARGS__)
#define siz(...) static_cast< int >((__VA_ARGS__).size())
using namespace std; using ll = long long;
template< typename... t > using V = vector< t... >;
template< typename... t > using outit = ostream_iterator< t... >;
void print(ostream& os){os << '\n';} template< typename t, typename... v >
void print(ostream& os, const t& a, v&&... b){os << a << ' '; print(os, b...);}
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template< typename t >
using ordered_set = tree< t, null_type, less< t >, rb_tree_tag, tree_order_statistics_node_update >;

constexpr int inf = 1e9;

struct Edge
{
    int v, val;
    Edge(int v, int val):
    v(v), val(val){}
};

struct Node : V< Edge >
{
    bool bl = false;
    int sum = 0;
    int odp = 0;
    int zas = 0;
};

int n, t;
V< Node > gr;

void fsum(int v, int oj)
{
    ddmp(v);
    gr[v].sum = 1;
    for (int i = 0; i < (int)gr[v].size(); ++i)
        if (gr[v][i].v != oj)
        {
            int s = gr[v][i].v;
            if (gr[s].bl)
            {
                gr[v][i] = gr[v][gr[v].size() - 1];
                gr[v].pop_back();
                --i;
                continue;
            }

            fsum(s, v);
            gr[v].sum += gr[s].sum;
        }
}

int centroid(int v, int sum)
{
    int oj = v;
    bool fl = true;
    while (fl)
    {
        fl = false;
        for (auto& ed : gr[v])
        {
            int s = ed.v;
            if (s != oj and gr[s].sum * 2 > sum)
            {
                fl = true;
                oj = v; v = s;
                break;
            }
        }
    }
    return v;
}

void dfs2(int v, int oj, int val, ordered_set< pair< int, int > >& S, V< int >& ilo)
{
    gr[v].odp += S.order_of_key({gr[v].zas - val, inf});
    ilo.psh(val);

    for (auto& ed : gr[v])
        if (ed.v != oj)
            dfs2(ed.v, v, val + ed.val, S, ilo);
}

void proceed(int c, bool fl = false)
{
    ddmp(c, fl);
    ordered_set< pair< int, int > > S;
    V< int > ilo;    

    if (fl)
        S.insert({0, ++t});
    
    int v = c;
    for (auto& ed : gr[v])
    {
        dfs2(ed.v, v, ed.val, S, ilo);
        
        for (int v : ilo)
            S.insert({v, ++t});
        ilo.clear();
    }

    if (fl)
        gr[c].odp += S.order_of_key({gr[c].zas, inf});
}

void dfs(int v)
{
    fsum(v, v);
    int c = centroid(v, gr[v].sum);
    proceed(c);
    reverse(all(gr[c]));
    proceed(c, true);
    gr[c].bl = true;

    for (auto& ed : gr[c])
    {
        int s = ed.v;
        dfs(s);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        
    cin >> n;

    gr.rsz(n + 1);

    for (int i = 1; i <= n; ++i)
        cin >> gr[i].zas;

    for (int i = 1; i <= n - 1; ++i)
    {
        int p, q, val; cin >> p >> q >> val;
        gr[p].emp(q, val);
        gr[q].emp(p, val);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i)
        prt(gr[i].odp);
}