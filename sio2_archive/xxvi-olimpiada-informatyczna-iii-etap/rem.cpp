/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_++)cerr<<"\033[96;1m";\
__VA_ARGS__; if (!(--c_))cerr<<"\033[0m";}
#define assrt(...) debug( \
if (not (__VA_ARGS__)) \
    exit((cerr<<__LINE__<<": "<<#__VA_ARGS__ << '\n', 1)))
#else
#define debug(...) {}
#endif
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define st first
#define nd second
using namespace std; using ll = long long;
template< typename t > using V = vector< t >;
template< typename t, size_t s > using A = array< t, s >;
void print() {cout << '\n';}
template< typename t, typename... v > 
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)? " " : "") ; print(b...);}
template< typename t > void print_range(t a, const t& b) 
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
#define dump(...) debug(print(__LINE__,':',#__VA_ARGS__,'=',__VA_ARGS__))
#define dump_range(...) debug(cerr<<__LINE__<<": "<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
/*}}}*/

using Graph = vector< vector< int > >;

constexpr int tax = 10, nax = 15e4, kax = nax;

struct Str
{
    pair< int, int > p;
    int ind;
};

inline bool operator<(const Str& mn, const Str& wc)
{
    return (mn.p == wc.p? mn.ind < wc.ind : mn.p < wc.p);
}

int t, n, k, tab[nax], of;
stack< int > S;
vector< bool > vis;
vector< int > spoj;
Str ilo[nax];

void dfs(const int v, const Graph& gra)
{
    vis[v] = true;
    for (int s : gra[v])
        if (not vis[s])
            dfs(s, gra);
    S.push(v);
}

void dfs2(const int v, const Graph& gra, int id)
{
    spoj[v] = id;
    for (int s : gra[v])
        if (not spoj[s])
            dfs2(s, gra, id);
}

void scc(const Graph& gra)
{
    Graph arg(gra.size());

    for (int i = 0; i < gra.size(); ++i)
        for (int s : gra[i])
            arg[s].push_back(i);

    vis.clear(); vis.resize(arg.size(), false);

    for (int i = 0; i < gra.size(); ++i)
        if (not vis[i])
            dfs(i, gra);

    spoj.clear(); spoj.resize(arg.size(), 0);

    int id = 1;

    while (not S.empty())
    {
        int v = S.top(); S.pop();
        if (spoj[v]) continue;
        dfs2(v, arg, id++);
    }
}

void proceed(V< int >& cur, const int of, Graph& gra)
{

    for (int i = 0; i < cur.size(); ++i)
    {
        gra.push_back(V< int >());
        if (i > 0) gra[gra.size() - 1].push_back(gra.size() - 2);
        gra[gra.size() - 1].push_back(cur[i] + of);
        if (i > 0) gra[cur[i]].push_back(gra.size() - 2);
    }

    reverse(all(cur));

    for (int i = 0; i < cur.size(); ++i)
    {
        gra.push_back(V< int >());
        if (i > 0) gra[gra.size() - 1].push_back(gra.size() - 2);
        gra[gra.size() - 1].push_back(cur[i] + of);
        if (i > 0) gra[cur[i]].push_back(gra.size() - 2);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while (t--)
    {
        cin >> n >> k;

        dump(n, k);

        for (int i = 0; i < n; ++i)
            cin >> tab[i];

        for (int i = 0; i < n - 1; ++i)
            ilo[i].p = {tab[i], tab[i + 1]}, ilo[i].ind = i;

        sort(begin(ilo), begin(ilo) + (n - 1));

        of = n - 1;
        Graph gra(2 * of);

        gra[0 + of].push_back(0);
        gra[n - 1 - 1 + of].push_back(n - 1 - 1);

        for (int i = 0; i < n - 1 - 1; ++i)
        {
            gra[i + of].push_back(i + 1);
            gra[i + 1 + of].push_back(i);
        }

        vector< int > cur;

        for (int i = 0; i < n - 1; ++i)
        {
            if (not cur.empty() and ilo[i - 1].p != ilo[i].p)
            {
                proceed(cur, of, gra);
                cur.clear();
            }

            cur.push_back(ilo[i].ind);
        }

        proceed(cur, of, gra);

        scc(gra);

        bool fl = true;

        for (int i = 0; i < n - 1; ++i)
            if (spoj[i] == spoj[i + of])
                fl = false;

        print((fl? "TAK" : "NIE"));
    }
}