#pragma GCC optimize("O3")
/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_ = 0;
#define cout (c_?cerr:cout)
#define debug(...) \
{if(!c_++)cerr<<"\033[96;1m"; \
__VA_ARGS__; \
if(!--c_)cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define assrt(...) debug(\
if (not (__VA_ARGS__)) \
    exit((cerr << __LINE__ << ": " << #__VA_ARGS__ << '\n', 0));\
)
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long; using ld = long double;
template < typename t > using V = vector< t >;
template < typename t, size_t s > using A = array< t, s >;
void print() {cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{ while (a != b) cout << (*a++) << ' '; cout << '\n';}
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__ << ": "; print_range(__VA_ARGS__))
/*}}}*/

constexpr int tax = 200, nax = 1e6, inf = 1e9;

int t, n, tab[nax + 1], ost[nax + 1], pot[nax + 1], lew[nax + 1], wel[nax + 1];
bool vis[nax + 1];
V< int > gr[nax + 1];

void add_edge(int p, int q, const bool rev)
{
    dump(p, q, rev);

    if (rev)
    {
        if (p > q) swap(p, q);
        ++p;
        p = n + 1 - p;
        q = n + 1 - q;
        --q;
    }

    dump(p, q);

    gr[p].push_back(q);
    gr[q].push_back(p);
}

void process(const int v, const bool rev)
{
    int lo = 0;
    for (int i = v; i > lo; --i)
        lo = max(lo, pot[i]);

    for (int hi = v; lo < v and hi <= n; ++hi, lo = max(lo, pot[hi]))
    {
        int lo2 = max(lo, lew[wel[hi]]);
        int dl = tab[wel[hi]];
        if (hi - dl + 1 > lo2 and hi - dl + 1 <= v)
            add_edge(hi - dl, hi, rev);
    }
}

void eval(const bool rev)
{
    for (int i = 1; i <= n; ++i)
        pot[i] = ost[tab[i]], ost[tab[i]] = i;

    tab[0] = inf + 1;
    lew[0] = 0;

    for (int i = 1; i <= n; ++i)
    {
        int k = i - 1; 
        while (tab[k] <= tab[i])
            k = lew[k];
        lew[i] = k;
    }

    int p = 1;

    for (int i = 1; i <= n; ++i)
    {
        if (tab[i] == 1) p = i;
        wel[i] = (lew[i] >= p? wel[lew[i]] : i);
    }

    dump_range(lew + 1, lew + n + 1);
    dump_range(wel + 1, wel + n + 1);

    for (int i = 1; i <= n; ++i)
        if (tab[i] == 1) process(i, rev);
    
    for (int i = 1; i <= n; ++i)
        ost[i] = 0;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while (t--)
    {
        cin >> n;

        for (int i = 1; i <= n; ++i)
            cin >> tab[i];

        bool fl = true;
        for (int i = 1; i <= n; ++i)
            if (tab[i] > n)
            {
                fl = false;
                print("NO"); break;
            }

        if (not fl) continue;

        eval(false);

        reverse(tab + 1, tab + n + 1);

        eval(true);

        for (int i = 0; i <= n; ++i)
            sort(all(gr[i]));

        for (int i = 0; i <= n; ++i)
            gr[i].resize(unique(all(gr[i])) - begin(gr[i]));

        vis[0] = true;
        for (int i = 0; i < n; ++i)
            if (vis[i])
                for (int s : gr[i])
                    vis[s] = true;
        print(vis[n]? "YES" : "NO");

        for (int i = 0; i <= n; ++i)
            gr[i].clear(), vis[i] = false;
    }
}