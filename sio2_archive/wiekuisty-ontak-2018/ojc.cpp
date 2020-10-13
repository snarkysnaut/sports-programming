#include <bits/stdc++.h>
#ifdef DBG
#define dbg(...) {cerr<<"\033[96;1m";ostream& cout=cerr;__VA_ARGS__;\
(void)(cout);cerr<<"\033[0m";}
#else
#define dbg(...) {}
#endif
#define nd second
#define st first
#define flg(), __LINE__, __PRETTY_FUNCTION__
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) print(cout, #__VA_ARGS__, __VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template<typename... t>using V = vector< t... >;
template<typename t> void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... v> void print(ostream& os, const t& a,
v&&... b){os<<a<<' ';print(os, b...);}

constexpr int maxn = 3e5, maxt = 1e6, rzm = (1 << 19);

int n, t, q;
set< int > S[maxt + 1];
int tb[rzm << 1], ma[rzm << 1], mi[rzm << 1];

void insertb(int v, int c)
{
    v += rzm;
    tb[v] = c;

    for (v >>= 1; v >= 1; v >>= 1)
        tb[v] = min(tb[(v << 1)], tb[(v << 1) + 1]);
}

void insertmi(int v, int c)
{
    v += rzm;
    mi[v] = c;

    for (v >>= 1; v >= 1; v >>= 1)
        mi[v] = min(mi[(v << 1)], mi[(v << 1) + 1]);
}

void insertma(int v, int c)
{
    v += rzm;
    ma[v] = c;

    for (v >>= 1; v >= 1; v >>= 1)
        ma[v] = max(ma[(v << 1)], ma[(v << 1) + 1]);
}

int querymi(int l, int r)
{
    l += rzm; r += rzm;
    int rs = min(mi[l], mi[r]);

    while ((l >> 1) != (r >> 1))
    {
        if ((l & 1) == 0) rs = min(rs, mi[l + 1]);
        if ((r & 1) == 1) rs = min(rs, mi[r - 1]);

        l >>= 1; r >>= 1;
    }

    return rs;
}

int queryma(int l, int r)
{
    l += rzm; r += rzm;
    int rs = max(ma[l], ma[r]);

    while ((l >> 1) != (r >> 1))
    {
        if ((l & 1) == 0) rs = max(rs, ma[l + 1]);
        if ((r & 1) == 1) rs = max(rs, ma[r - 1]);

        l >>= 1; r >>= 1;
    }

    return rs;
}

int querytb(int l, int r)
{
    l += rzm; r += rzm;
    int rs = min(tb[l], tb[r]);

    while ((l >> 1) != (r >> 1))
    {
        if ((l & 1) == 0) rs = min(rs, tb[l + 1]);
        if ((r & 1) == 1) rs = min(rs, tb[r - 1]);

        l >>= 1; r >>= 1;
    }

    return rs;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;

    for (int i = 1; i <= t; ++i)
    {
        S[i].insert(0);
        S[i].insert(n + 1);
    }

    for (int i = 1; i <= n; ++i)
    {
        int v; cin >> v;

        ma[i + rzm] = mi[i + rzm] = v;

        auto it = S[v].insert(i).first;

        insertb((*prev(it)), (*it));
        insertb((*it), (*next(it)));
    }

    for (int i = rzm - 1; i >= 1; --i)
    {
        ma[i] = max(ma[i << 1], ma[(i << 1) + 1]);
        mi[i] = min(mi[i << 1], mi[(i << 1) + 1]);
        tb[i] = min(tb[i << 1], tb[(i << 1) + 1]);
    }

    cin >> q;

    for (int i = 0; i < q; ++i)
    {
        int t; cin >> t;

        if (t == 1)
        {
            int l, r; cin >> l >> r;

            int q = queryma(l, r);
            int p = querymi(l, r);

            ddmp(l, r, q, p);

            if ((q - p + 1) != (r - l + 1))
            {
                prt("NO"); continue;
            }

            int w = querytb(l, r);

            ddmp(w);

            if (w <= r)
            {
                prt("NO"); continue;
            }

            prt("YES");
        }
        else if (t == 2)
        {
            int v, c;
            cin >> v >> c;

            int p = ma[rzm + v];

            insertma(v, c);
            insertmi(v, c);

            auto it = S[p].find(v);

            it = S[p].erase(it);

            --it;

            insertb((*it), (*next(it)));

            it = S[c].insert(v).first;

            insertb((*it), (*next(it)));
            insertb((*prev(it)), (*it));
        }
    }
}