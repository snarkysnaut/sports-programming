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

constexpr int nax = 1e9, maxm = 5e5;
constexpr ll inf = 1e18;

struct SegTree
{
    int rozm = 1;
    V< ll > tree;
    SegTree(const int n)
    {
        while (rozm < n)
            rozm <<= 1;
        tree.reserve(rozm << 1);
        tree.resize(rozm << 1, inf);
    }
    void insert(int v, const ll c)
    {
        for (v += rozm; v >= 1; v >>= 1)
            tree[v] = min(tree[v], c);
    }

    ll query(int l, int r)
    {
        l += rozm; r += rozm;
        ll res = min(tree[l], tree[r]);
        while ((l >> 1) != (r >> 1))
        {
            if ((l & 1) == 0)
                res = min(res, tree[l + 1]);
            if ((r & 1) == 1)
                res = min(res, tree[r - 1]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

struct Ryn
{
    int l, r, h, w;
};

int m, n, siz;
Ryn ryn[maxm];
V< int > low;

int renum(const int v)
{
    return lower_bound(all(low), v) - begin(low);
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    if (n == 1)
    {
        print(0);
        return 0;
    }

    for (int i = 0; i < m; ++i)
        cin >> ryn[i].l >> ryn[i].r >> ryn[i].h >> ryn[i].w;

    for (int i = 0; i < m; ++i)
        low.push_back(ryn[i].l), low.push_back(ryn[i].r), low.push_back(ryn[i].h);

    low.push_back(n);
    low.push_back(1);
    
    sort(all(low));
    low.resize(unique(all(low)) - begin(low));

    siz = low.size();

    for (int i = 0; i < siz - 1; ++i)
        if (low[i + 1] - low[i] > 1)
            low.push_back(low[i] + 1);

    sort(all(low));

    for (int i = 0; i < m; ++i)
        ryn[i].l = renum(ryn[i].l), ryn[i].r = renum(ryn[i].r), ryn[i].h = renum(ryn[i].h);

    siz = low.size();

    low.clear(); low.shrink_to_fit();

    SegTree lef(siz), rig(siz);

    lef.insert(0, 0);
    rig.insert(siz - 1, 0);

    ll res = inf;

    for (int i = 0; i < m; ++i)
    {
        ll l = lef.query(ryn[i].l, ryn[i].r);
        ll r = rig.query(ryn[i].l, ryn[i].r);
        res = min(res, l + r + ryn[i].w);
        lef.insert(ryn[i].h, l + ryn[i].w);
        rig.insert(ryn[i].h, r + ryn[i].w);
    }

    print(res == inf? -1ll : res);
}