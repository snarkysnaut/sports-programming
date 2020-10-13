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

constexpr int maxn = 2e5, maxk = 9;

int n, k;
int tb[maxn];
int deg[maxn];
int odp[maxn];
V< int > gr[maxn];

inline bool add(V< int >& ilo, int& inw, int q)
{
    if (q - inw > (int)ilo.size() or q < inw)
        return false;

    int v = q - inw + 1;

    inw = q;

    for (int i = 0; i < ilo.size(); ++i)
        if (ilo[i] >= v) ++ilo[i];

    ilo.insert(begin(ilo), v);

    return true;
}

inline void pop(V< int >& ilo, int& inw)
{
    inw -= ilo.size() - ilo[ilo.size() - 1];
    for (int i = 0; i < ilo.size() - 1; ++i)
        if (ilo[i] > ilo[ilo.size() - 1]) --ilo[i];
    ilo.pop_back();
}

int qwe = n;

inline bool spr(V< int > ilo)
{
dbg(
    prt("poczatek:");
    for (int v : ilo)
        cerr << v << ' ';
    cerr << '\n';
);

    int pt = n - ilo.size();

    int inw = 0;
    for (int i = 0; i < ilo.size(); ++i)
        for (int k = i + 1; k < ilo.size(); ++k)
            inw += ilo[k] < ilo[i];

    for (int i = qwe; i < n; ++i)
        gr[i].clear();

    for (int i = 0; i < ilo.size(); ++i)
        for (int k = 0; k < ilo.size(); ++k)
            if (i != k and ilo[i] < ilo[k])
                gr[pt + i].push_back(pt + k);

    for (--pt; pt >= 0; --pt)
    {
        qwe = pt;
        if (not add(ilo, inw, tb[pt]))
            return false;

        dbg(
            for (int v : ilo)
                cerr << v << ' ';
            cerr << '\n';
        );

        for (int i = 1; i < ilo.size(); ++i)
        {
            if (ilo[0] < ilo[i])
                gr[pt].push_back(i + pt);
            else
                gr[i + pt].push_back(pt);
        }

        pop(ilo, inw);

        dbg(
            for (int v : ilo)
                cerr << v << ' ';
            cerr << '\n';
        );
    }

    dprt("sukces");

    for (int i = 0; i < n; ++i)
        deg[i] = 0;

    for (int i = 0; i < n; ++i)
        for (int s : gr[i])
            ++deg[s];

    int rs = 1;

    queue< int > Q;

    for (int i = 0; i < n; ++i)
        if (not deg[i])
            Q.push(i);

    while (not Q.empty())
    {
        int v = Q.front(); Q.pop();
        odp[v] = rs++;

        for (int s : gr[v])
            if (not (--deg[s]))
                Q.push(s);
    }

    if (rs != n + 1)
        return false;

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 0; i < n - k + 1; ++i)
        cin >> tb[i];

    V< int > perm(k - 1);
    for (int i = 1; i <= k - 1; ++i)
        perm[i - 1] = i;

    do
    {
        dbg(
            prt("przed petla:");
            for (int v : perm)
                cerr << v << ' ';
            cerr << '\n';
        );
        if (spr(perm)) 
            break;
    } while (next_permutation(all(perm)));


    for (int i = 0; i < n; ++i)
        cout << odp[i] << ' ';
    cout << '\n';
}