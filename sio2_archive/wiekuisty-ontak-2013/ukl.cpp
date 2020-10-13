/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define debug(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) debug(print(#__VA_ARGS__, '=',  __VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
using namespace std; using ll = long long; 
template< typename t > using V = vector< t >; void print(){cout<<'\n';}
template< typename t, typename... v > void print(const t& a, v&&... b)
{cout << a << (sizeof...(b)? " " : ""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
/*}}}*/

constexpr int maxn = 25e4, maxk = 10, logg = 19, rzm = (1 << logg), inf = 1e9 + 1;

int n, k, q;
int mks[rzm << 1];
int tree[rzm << 1][maxk - 1];

void mrg(int v, int l, int r)
{
    int lp = 0, rp = 0;

    for (int i = 0; i < k - 1; ++i)
    {
        if (lp < k - 1 and (rp >= k - 1 or tree[l][lp] < tree[r][rp]))
            tree[v][i] = tree[l][lp++];
        else
            tree[v][i] = tree[r][rp++];
    }

}
            

void mrg2(int res[], int a[], int b[])
{
    int rs[maxk - 1];
    int ap = 0, bp = 0;

    for (int i = 0; i < k - 1; ++i)
    {
        if (ap < k - 1 and (bp >= k - 1 or a[ap] < b[bp]))
            rs[i] = a[ap++];
        else
            rs[i] = b[bp++];
    }

    for (int i = 0; i < k - 1; ++i)
        res[i] = rs[i];
}

ll query(int l, int r)
{
    l += rzm, r += rzm;
    int resl[maxk - 1], resr[maxk - 1];
    for (int i = 0; i < maxk - 1; ++i)
        resl[i] = tree[l][i], resr[i] = tree[r][i];
    if (l == r)
        return accumulate(resl, resl + k - 1, 0ll);
    while ((l >> 1) != (r >> 1))
    {
        if ((l & 1) == 0)
            mrg2(resl, resl, tree[l + 1]);
        if ((r & 1) == 1)
            mrg2(resr, tree[r - 1], resr);
        l >>= 1; r >>= 1;
    }

    mrg2(resl, resl, resr);
    return accumulate(resl, resl + k - 1, 0ll);
}

int maks(int l, int r)
{
    l += rzm, r += rzm;
    int res = max(mks[l], mks[r]);
    while ((l >> 1) != (r >> 1))
    {
        if ((l & 1) == 0)
            res = max(res, mks[l + 1]);
        if ((r & 1) == 1)
            res = max(res, mks[r - 1]);
        l >>= 1; r >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 1; i < (rzm << 1); ++i)
        for (int j = 0; j < maxk - 1; ++j)
            tree[i][j] = inf;

    for (int i = 0; i < n; ++i)
        cin >> tree[i + rzm][0], mks[i + rzm] = tree[i + rzm][0];

    for (int i = (rzm - 1); i >= 1; --i)
        mrg(i, (i << 1), (i << 1) + 1), mks[i] = max(mks[(i << 1)], mks[(i << 1) + 1]); 
    cin >> q;

    while (q--)
    {
        int a, b; 
        cin >> a >> b;
        --a; --b;
        if (b - a + 1 < k)
        {
            print("TAK"); continue;
        }
        ll p = query(a, b);
        int q = maks(a, b);
        print(p <= q? "NIE" : "TAK");
    }
}