/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define dbg(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) dbg(print(#__VA_ARGS__, __VA_ARGS__))
#define dump_range(...) dbg(cerr<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
using namespace std; using ll = long long; 
template< typename t > using V = vector< t >; void print(){cout<<'\n';}
template< typename t, typename... v > void print(const t& a, v&&... b)
{cout << a << ' '; print(b...);}
template< typename t > void print_range(t a, const t& b)
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
/*}}}*/

constexpr int maxn = 2e5, maxm = 5e5;

struct Edge
{
    int p, q, wg;
};

inline bool operator<(const Edge& mn, const Edge& wc)
{
    return mn.wg < wc.wg;
}

int n, m;
Edge eds[maxm];
int fu[maxn + 1];

int find(int v)
{
    if (fu[v] < 0) return v;
    return fu[fu[v]] < 0? fu[v] : fu[v] = find(fu[v]);
}

void join(int p, int q)
{
    p = find(p), q = find(q);
    if (p == q) return;
    if (fu[p] > fu[q]) swap(p, q);
    fu[p] += fu[q];
    fu[q] = p;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        fu[i] = -1;

    for (int i = 0; i < m; ++i)
        cin >> eds[i].p >> eds[i].q >> eds[i].wg;

    sort(eds, eds + m);

dbg(
    for (int i = 0; i < m; ++i)
    {
        auto& ed = eds[i];
        print(ed.wg);
    }
);

    ll res = 0;

    for (int i = m - 1; i >= 0; --i)
    {
        if (eds[i].wg < 0) break;
        if (find(eds[i].p) != find(eds[i].q))
        {
            join(eds[i].p, eds[i].q);
            res += eds[i].wg;
            dbg(print(eds[i].wg));
        }
    }

    res = -res;

    for (int i = 0; i < m; ++i)
        res += eds[i].wg;

    print(res);
}