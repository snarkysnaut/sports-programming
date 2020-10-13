#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int nax = 5e5, maxm = 5e5, logg = 19, rozm = (1 << logg), bs = 101;
constexpr ll mod = 1e9 + 7;

int n, m, fu[nax + 1], res;
vector< int > spo[nax + 1];
ll tree[rozm << 1], pot[nax + 1];

void insert(int v, const int c)
{
    v += rozm;
    tree[v] = c;
    int l = 1;
    for (v >>= 1; v; v >>= 1, l <<= 1)
        tree[v] = (tree[(v << 1)] * pot[l] + tree[(v << 1) + 1]) % mod;
}

ll query(int l, int r)
{
    if (r < l) return 0;

    //cout << l << ' ' << r << ' ';

    l += rozm; r += rozm;

    ll resl = tree[l];
    ll resr = tree[r];
    int rlen = 1;

    if (l == r) 
    {
        //cout << resl << '\n';
        return resl;
    }

    for (int len = 1; (l >> 1) != (r >> 1); l >>= 1, r >>= 1, len <<= 1)
    {
        if ((l & 1) == 0)
            resl = ((ll)resl * pot[len] + tree[l + 1]) % mod;
        if ((r & 1) == 1)
            resr = ((ll)tree[r - 1] * pot[rlen] + resr) % mod, rlen += len;
    }

    //cout << ((ll)resl * pot[rlen] + resr) % mod << '\n';
    return ((ll)resl * pot[rlen] + resr) % mod;
}

void join(int p, int q)
{
    p = fu[p], q = fu[q];
    if (spo[p].size() < spo[q].size()) swap(p, q);
    for (int v : spo[q])
        insert(v, p), fu[v] = p, spo[p].push_back(v);
    spo[q].clear(); spo[q].shrink_to_fit();
    --res;
}

void eval(int p, int q, int d)
{
    while (d)
    {
        if (query(p, p + d - 1) == query(q, q + d - 1))
            return;
        //cout << p << ' ' << q << ' ' << d << '\n';
        int lo = 0, hi = d;
        while (lo < hi)
        {
            int mi = (lo + hi + 1) / 2;
            if (query(p, p + mi - 1) == query(q, q + mi - 1))
                lo = mi;
            else
                hi = mi - 1;
        }
        
        //cout << lo << '\n';

        if (lo == d) return;
        join(p + lo, q + lo);
        p += lo, q += lo;
        d -= lo;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    res = n;
    
    pot[0] = 1;
    for (int i = 1; i <= n; ++i)
        pot[i] = (pot[i - 1] * bs) % mod;

    for (int i = 1; i <= n; ++i)
        fu[i] = i, insert(i, i);
    
    for (int i = 1; i <= n; ++i)
        spo[i].push_back(i);

    int p = n;
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c; cin >> a >> b >> c;
        #ifdef LOCAL
        int x = a, y = b, l = c;
        #else
        int x = ((a + p) % n) + 1;
        int y = ((b + (ll)i * p) % n) + 1;
        int l = (c % (n - max(x, y) + 1)) + 1;
        #endif
        //cout << x << ' ' << y << ' ' << l << '\n';
        eval(x, y, l);
        //for (int i = 1; i <= n; ++i)
            //cout << fu[i] << ' ';
        //cout << '\n';
        cout << res << '\n';
        p = res;
    }
}