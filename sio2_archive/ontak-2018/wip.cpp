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

constexpr int maxn = 3e5;

int n;
ll res = 0;
pair< ll, ll > val[maxn];
V< pair< int, int > > gr[maxn];

void dfs(int v)
{
    if (gr[v].size() == 0)
    {
        val[v] = {0, 0};
        return;
    }

    V< pair< ll, int > > evs;

    for (auto& p : gr[v])
    {
        dfs(p.st);
        evs.push_back({val[p.st].st + p.nd, -1});
        evs.push_back({val[p.st].nd + p.nd, -1});
    }

    sort(all(evs));

    ll sum = 0;
    int cntp = gr[v].size();

    ll crt = evs[0].st;

    ll lo = crt, hi = crt, naj = sum;

    for (auto& p : gr[v])
        sum += abs(val[p.st].st + p.nd - crt);
    naj = sum;
    dprt(sum);

    for (auto& ev : evs)
    {
        sum -= (ev.st - crt) * cntp;

        crt = ev.st;

        if (sum < naj)
            naj = sum, lo = crt, hi = crt;
        else if (sum == naj)
            hi = crt;

        cntp += ev.nd;
    }

    ddmp(v, naj, lo, hi);

    res += naj;

    val[v] = {lo, hi};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ddmp(-3e14);

    cin >> n;

    for (int i = 1; i < n; ++i)
    {
        int p, v; cin >> p >> v;
        gr[p].push_back({i, v});
    }

    dfs(0);

    prt(res);
}