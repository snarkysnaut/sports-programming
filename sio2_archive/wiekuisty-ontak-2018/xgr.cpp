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

constexpr int logg = 22, maxn = 1e5, maxa = (1 << logg);

int n;
char pop[maxa];
char naj[maxa];
bool tb[logg][maxa];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i < maxa; ++i)
        pop[i] = pop[i >> 1] + (i & 1);

    naj[0] = -1;

    for (int i = 1; i < maxa; ++i)
        naj[i] = naj[i >> 1] + 1;

    for (int i = 0; i < n; ++i)
    {
        int v; cin >> v;

        int q = (~v) & ((1 << naj[v]) - 1);

        tb[naj[v]][q] = true;
    }

    for (int i = 0; i < logg; ++i)
        for (int k = (1 << i) - 1; k >= 0; --k)
            for (int j = 0; j < i; ++j)
                tb[i][k] = tb[i][k] or tb[i][k | (1 << j)];

    int rs = 0;
    for (int i = 1; i < maxa; ++i)
    {
        bool fl = true;
        for (int k = 0; k <= naj[i]; ++k)
            if ((1 << k) & i)
                if (not tb[k][i & ((1 << k) - 1)])
                    fl = false;

        if (fl) rs = max(rs, (int)pop[i]);
    }

    prt(rs);
}