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

constexpr int maxn = 3e5, rozm = (1 << 19);

int n, q;
int odp[maxn];
int le[rozm << 1], ri[rozm << 1];
pair< int, int > mi[rozm << 1]; int va[rozm << 1];
V< pair< int, int > > ilo[maxn];

inline void update(int v)
{
    mi[v] = min(mi[v << 1], mi[(v << 1) + 1]);
    mi[v].st += va[v];
}

inline void insert(int l, int r, int c = 1, int v = 1)
{
    ddmp(l, r, v, le[v], ri[v]);
    if (ri[v] < l or le[v] > r) return;

    if (l <= le[v] and ri[v] <= r)
    {
        mi[v].st += c;
        va[v] += c;
        return;
    }

    for (auto s : {v * 2, v * 2 + 1})
        insert(l, r, c, s);

    update(v);
}

inline pair< bool, int > query(int l, int r, int v = 1)
{
    if (ri[v] < l or le[v] > r) return {false, -1};

    if (l <= le[v] and ri[v] <= r)
    {
        if (mi[v].st) return {false, -1};
        else return {true, mi[v].nd};
    }

    if (mi[v].st) return {false, -1};

    for (auto s : {v * 2, v * 2 + 1})
    {
        auto w = query(l, r, s);
        if (w.st) return w;
    }

    return {false, -1};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 0; i < q; ++i)
    {
        int l, r, v;
        cin >> l >> r >> v;
        ilo[v].push_back({l, r});
    }

    for (int i = rozm; i < (rozm << 1); ++i)
    {
        le[i] = ri[i] = i - rozm;
        mi[i] = {0, i - rozm};
    }

    for (int i = rozm - 1; i >= 1; --i)
    {
        le[i] = min(le[i << 1], le[(i << 1) + 1]);
        ri[i] = max(ri[i << 1], ri[(i << 1) + 1]);
        mi[i] = min(mi[i << 1], mi[(i << 1) + 1]);
    }


    for (int i = n - 1; i >= 0; --i)
        for (auto& p : ilo[i])
            insert(p.st, p.nd);

    for (int i = 0; i < n; ++i)
    {
        ddmp(i);
        for (auto& p : ilo[i])
            insert(p.st, p.nd, -1);

        int lo = 0, hi = n - 1;
        for (auto& p : ilo[i])
            lo = max(lo, p.st), hi = min(hi, p.nd);

        ddmp(lo, hi);

        if (lo > hi)
            return prt(-1), 0;

        auto r = query(lo, hi);

        ddmp(r.st, r.nd);

        if (not r.st)
            return prt(-1), 0;

        insert(r.nd, r.nd);

        odp[r.nd] = i;
    }

    for (int i = 0; i < n; ++i)
        cout << odp[i] << ' ';
    cout << '\n';
}