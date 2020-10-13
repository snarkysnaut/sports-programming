/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;if(!(--c_))cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
#define dump(...) debug(print(#__VA_ARGS__, " = ", __VA_ARGS__))
using namespace std; using ll = long long;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, v&&... b){cout<<a<<(sizeof...(b)? " " : "");print(b...);}
template< typename t > using V = vector< t >;
/*}}}*/

constexpr int nax = 5000, dax = 200, pri = 5003, maxm = 1e6, mod[2] = {1000000007, 1000000009};

int d, n, m, res, t;
int vis[nax + 1];
V< int > drp;
V< int > gr[dax + 1][nax + 1];
unordered_map< ll, int > M;
int pw[2][dax + 1], tab[2][nax + 1], fu[dax + 1][nax + 1];

int find(int v, int k)
{
    return fu[k][v] < 0? v : fu[k][v] = find(fu[k][v], k);
}

void join(int p, int q, int k)
{
    //p = find(p, k), q = find(q, k);

    //if (p == q) return;

    //if (-fu[k][p] < -fu[k][q])
        //swap(p, q);

    fu[k][q] += fu[k][p];
    fu[k][p] = q;
}

void dfs(int v, int k, int q)
{
    dump(v, k, q);
    int p = find(v, k);

    if (M.find(tab[0][v] + ((ll)tab[1][v] << 32)) != M.end()) M.erase(tab[0][v] + ((ll)tab[1][v] << 32));
    
    for (int j = 0; j < 2; ++j)
    {
        int odj = ((ll)pw[j][k] * p) % mod[j];
        tab[j][v] -= odj;
        if (tab[j][v] < 0) tab[j][v] += mod[j];
        tab[j][v] += ((ll)pw[j][k] * q) % mod[j];
        if (tab[j][v] >= mod[j]) tab[j][v] -= mod[j];
    }

    res += 2 * M[tab[0][v] + ((ll)tab[1][v] << 32)];
    
    drp.push_back(v);

    vis[v] = t;

    for (int s : gr[k][v])
        if (vis[s] != t)
            dfs(s, k, q);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> d >> n >> m;

    res = n;
    pw[0][0] = pw[1][0] = 1;

    for (int j = 0; j < 2; ++j)
        for (int k = 1; k <= d; ++k) 
            pw[j][k] = ((ll)pw[j][k - 1] * pri) % mod[j];

    for (int k = 1; k <= d; ++k)
        for (int i = 1; i <= n; ++i)
            fu[k][i] = -1;

    for (int j = 0; j < 2; ++j)
        for (int i = 1; i <= n; ++i)
        {
            int hsz = 0;
            for (int k = 1; k <= d; ++k)
                hsz = ((ll)hsz + (ll)i * pw[j][k]) % mod[j];
            tab[j][i] = hsz;
        }

    for (int i = 1; i <= n; ++i)
        ++M[tab[0][i] + ((ll)tab[1][i] << 32)];

    for (int i = 0; i < m; ++i)
    {
        int p, q, k; cin >> p >> q >> k;
        
        p = find(p, k), q = find(q, k);
        
        if (p == q) 
        {
            print(res);
            continue;
        }

        if (q > p) swap(p, q);

        if (-fu[k][p] > -fu[k][q])
            swap(p, q);

        ++t;
        dfs(p, k, q);

        for (auto& p : drp)
            ++M[tab[0][p] + ((ll)tab[1][p] << 32)];

        gr[k][p].push_back(q);
        gr[k][q].push_back(p);

        join(p, q, k);

        print(res);

        drp.clear();
    }
}