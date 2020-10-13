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

constexpr int maxn = 1e5;
constexpr ll inf = 1e18;

struct Line
{
    ll a, b;
    Line(ll a, ll b):a(a),b(b){}
    ll operator()(ll x)
    {
        return x * a + b;
    }
};

inline long double inter(const Line& a, const Line& b)
{
    return (long double)(a.b - b.b) / (b.a - a.a);//
}

struct Edge
{
    int v, w;
    Edge(int v, int w):v(v),w(w){}
    operator int(){return v;}
};


int z, n, s, t;
ll odl[maxn + 1];
int sum[maxn + 1];
int ksz[maxn + 1];
bool vis[maxn + 1];
V< Edge > gr[maxn + 1];
V< Line > arr[maxn + 1];
pair< int, int > ilo[maxn];
V< pair< int, int > > tb[maxn + 1];

void subs(int v, int oj)
{
    sum[v] = 1;

    for (int i = 0; i < (int)gr[v].size(); ++i)
    {
        if (vis[gr[v][i].v])
        {
            swap(gr[v][i], gr[v][gr[v].size() - 1]);
            gr[v].pop_back();
            --i; continue;
        }

        int s = gr[v][i].v;

        if (s != oj)
        {
            subs(s, v);
            sum[v] += sum[s];
        }
    }
}

int centroid(int v, int q)
{
    int oj = v;
    while (true)
    {
        bool fl = false;
        for (int s : gr[v])
            if (s != oj and sum[s] * 2 >= q)
            {
                fl = true;
                oj = v;
                v = s;
                break;
            }

        if (not fl) break;
    }

    return v;
}

void add(int v, int oj, int c, int d = 0)
{
    tb[v].push_back({c, d});

    for (auto& ed : gr[v])
        if (ed.v != oj) 
            add(ed.v, v, c, d + ed.w);
}

void deco(int v)
{
    subs(v, v);

    v = centroid(v, sum[v]);

    add(v, v, v);

    vis[v] = true;

    dmp(v);

    for (int s : gr[v])
        if (not vis[s]) 
            deco(s);
}

ll query(int v, int arg)
{
    dmp(v, arg);
    if (arr[v].empty())
        return inf;

    int lo = 0;
    for (int b = arr[v].size() - 1; b >= 1; b >>= 1)
        while (lo + b < arr[v].size() and arr[v][lo + b](arg) < arr[v][lo + b - 1](arg))
            lo += b;

    dmp(arr[v][lo](arg));
    return arr[v][lo](arg);
}

void add(int v, Line l)
{
    dmp(v, l.a, l.b);
    while (arr[v].size() >= 2)
    {
        if (arr[v][arr[v].size() - 1].a == l.a)
        {
            if (l.b <= arr[v][arr[v].size() - 1].b)
            {
                arr[v].pop_back();
                continue;
            }
            else
                return;
        }
        if (inter(arr[v][arr[v].size() - 1], arr[v][arr[v].size() - 2]) >=
        inter(arr[v][arr[v].size() - 1], l))
        {
            arr[v].pop_back();
            continue;
        }

        break;
    }

    arr[v].push_back(l);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> z;
    while (z--)
    {
        cin >> n >> s >> t;

        for (int i = 0; i < n; ++i)
            ilo[i].nd = i + 1, cin >> ilo[i].st, ksz[i + 1] = ilo[i].st;

        ilo[t - 1].st = 0;
        ksz[t] = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            int p, q, w; cin >> p >> q >> w;
            gr[p].emplace_back(q, w);
            gr[q].emplace_back(p, w);
        }

        deco(1);

dbg(
        for (int i = 1; i <= n; ++i)
        {
            dprt(i, ':');
            for (auto p : tb[i])
                dprt(p.st, p.nd);
        }
);
                

        sort(ilo, ilo + n);

        for (int i = 1; i <= n; ++i)
            odl[i] = inf;

        odl[s] = 0;

        int pt = 0;
        for (int i = n - 1; i >= 0; --i)
            if (ilo[i].nd == s)
            {
                pt = i; break;
            }

        for (int i = pt; i >= 0; --i)
        {
            int v = ilo[i].nd;

            for (auto p : tb[v])
                odl[v] = min(odl[v], query(p.st, p.nd));

                for (auto l : arr[1])
                    dprt(l.a, l.b);




            for (auto p : tb[v])
                add(p.st, Line(ksz[v], (ll)p.nd * ksz[v] + odl[v]));

            dmp(v, odl[v]);
        }

        prt(odl[t]);

        for (int i = 1; i <= n; ++i)
            gr[i].clear(), tb[i].clear(), vis[i] = false, arr[i].clear();
    }
}