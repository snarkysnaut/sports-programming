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

constexpr int maxn = 2e5;

int n, m;
bool vis[maxn + 1];
int ideg[maxn + 1], odeg[maxn + 1];
V< int > gr[maxn + 1];

int dfs(int v)
{
    vis[v] = true;

    int r = abs(ideg[v] - odeg[v]);

    for (int s : gr[v])
        if (not vis[s])
            r += dfs(s);

    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        ++odeg[b], ++ideg[a];

        gr[a].push_back(b);
        gr[b].push_back(a);
    }

    int res = 0;
    int cnt = 0, ps = 0, sum = 0;

    for (int i = 1; i <= n; ++i)
        if (not vis[i])
        {
            int q = dfs(i);
            q >>= 1;

            ps += (q == 0);
            cnt += (q > 0);
            sum += q;
        }
    
    sum -= (cnt + ps > 1? cnt : 0);

    res += (cnt + ps > 1? cnt + ps : 0);

    prt(res + sum);

}