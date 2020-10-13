/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_++)cerr<<"\033[96;1m";\
__VA_ARGS__; if (!(--c_))cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define assrt(...) debug( \
if (not (__VA_ARGS__)) \
    exit((cerr<<__LINE__<<": "<<#__VA_ARGS__ << '\n', 1)))
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

constexpr int nax = 3e5, qax = 5e5, inf = 1e9 + 1, logg = 19, rozm = (1 << logg);
constexpr ll linf = 1e18 + 1;

struct Node
{
    int l = inf, r = -inf;
    ll ma = -linf, mi = linf;
    ll ma2 = -linf;
    ll val = 0;
};

int n, q, res; ll off = 0;
int tab[nax];
Node tree[rozm << 1];

void lazy(const int v)
{
    assrt(v < rozm);
    ll d = tree[v].val;
    if (not d) return;
    tree[v].val = 0;
    for (int s : {(v << 1), (v << 1) + 1})
    {
        tree[s].ma += d;
        tree[s].mi += d;
        tree[s].ma2 += d;
        tree[s].val += d;
    }
}

void upd(const int v)
{
    assrt(v < rozm);
    lazy(v);
    tree[v].ma = max(tree[(v << 1) + 1].ma, tree[(v << 1)].ma);
    tree[v].mi = min(tree[(v << 1) + 1].mi, tree[(v << 1)].mi);
    tree[v].ma2 = max(tree[(v << 1) + 1].ma2, tree[(v << 1)].ma2);
}

void insert(int l, int r, ll c, int v = 1)
{
    if (l > r) return;
    if (r < tree[v].l or tree[v].r < l)
        return;
    if (l <= tree[v].l and tree[v].r <= r)
    {
        tree[v].val += c;
        tree[v].ma += c;
        tree[v].mi += c;
        tree[v].ma2 += c;
        return;
    }
    lazy(v);
    insert(l, r, c, (v << 1));
    insert(l, r, c, (v << 1) + 1);
    upd(v);
}

ll query_ma(int l, int r, int v = 1)
{
    if (l > r) return -linf;
    if (r < tree[v].l or tree[v].r < l)
        return -linf;
    if (l <= tree[v].l and tree[v].r <= r)
        return tree[v].ma;
    lazy(v);
    return max(query_ma(l, r, (v << 1)), query_ma(l, r, (v << 1) + 1));
}

ll query_ma2(int l, int r, int v = 1)
{
    if (l > r) return -linf;
    if (r < tree[v].l or tree[v].r < l)
        return -linf;
    if (l <= tree[v].l and tree[v].r <= r)
        return tree[v].ma2;
    lazy(v);
    return max(query_ma2(l, r, (v << 1)), query_ma2(l, r, (v << 1) + 1));
}

void update()
{
    while (true)
    {
        int v = n - 1 - res + 1;
        ll x = query_ma(v, v);
        if (x < query_ma2(v + 1, n - 1))
            --res;
        else break;
    }
}

int find(ll x, int v = 1)
{
    if (v >= rozm) return v - rozm;
    lazy(v);
    if (tree[v].mi > x) return -1;
    if (tree[(v << 1) + 1].mi <= x)
        return find(x, (v << 1) + 1);
    if (tree[(v << 1)].mi <= x)
        return find(x, (v << 1));
    debug(print("wtf"));
    exit(1);
}

int dnif(ll x, int v = 1)
{
    if (v >= rozm) return v - rozm;
    lazy(v);
    if (tree[v].ma < x) return n;
    if (tree[(v << 1)].ma >= x) return dnif(x, (v << 1));
    if (tree[(v << 1) + 1].ma >= x) return dnif(x, (v << 1) + 1);
    debug(print("wtf2"));
    exit(2);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 0; i < n; ++i)
        cin >> tab[i];

    sort(begin(tab), begin(tab) + n);

    for (int i = 0; i < n; ++i)
    {
        int v = i + rozm;
        tree[v].l = tree[v].r = i;
        tree[v].ma = tree[v].mi = tab[i];
        tree[v].ma2 = tab[i] - i;
    }

    for (int i = rozm - 1; i >= 1; --i)
    {
        tree[i].l = tree[(i << 1)].l,
        tree[i].r = max(tree[(i << 1)].r, tree[(i << 1) + 1].r);
    }

    for (int i = rozm - 1; i >= 1; --i)
        upd(i);

    res = n;

    for (int i = 0; i < q; ++i)
    {
        char c; cin >> c;

        if (c == 'Z')
        {
            update();
            cout << res << '\n';
        }
        if (c == 'K')
        {
            ll x, y; cin >> x >> y;
            int v = find(x);
            insert(0, v, -y); // moze byc l > r!
        }
        if (c == 'B')
        {
            ll x, y; cin >> x >> y;
            int v = dnif(x);
            insert(v, n - 1, y); // moze byc l > r!
        }
    }
}