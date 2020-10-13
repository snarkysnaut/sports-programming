/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {cerr<<(!c_?"\033[96;1m":"");\
++c_;__VA_ARGS__;--c_;cerr<<(!c_?"\033[0m":"");}
#else
#define debug(...) {}
#endif
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
using namespace std; using ll = long long;
template< typename... t > using V = vector< t... >;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":"");print(b...);}
int argc_; char** argv_;
/*thread_local mt19937 gen;
inline ll arg(int v, ll def = 0)
{return v < argc_? atoll(argv_[v]) : def;}
template< typename t >
t rng(t min, t max) 
{return uniform_int_distribution< t >{min, max}(gen);}*/
/*}}}*/

constexpr int nax = 1e6, inf = nax + 1;

int n;
int tab[2][nax];
int odl[2][nax];
bool ilo[2][nax];
bool vis[nax + 1];

inline void dfs(int i, int k)
{
    ilo[i][k] = false;
    if (ilo[1 - i][k] and tab[1 - i][k] == tab[i][k])
        dfs(1 - i, k);
    if (k < n - 1 and ilo[i][k + 1] and tab[i][k + 1] == tab[i][k])
        dfs(i, k + 1);
    if (k > 0 and ilo[i][k - 1] and tab[i][k - 1] == tab[i][k])
        dfs(i, k - 1);
}

deque< pair< int, int > > dq;

inline void git(int a, int b, int c, int d, int j)
{
    if (not (0 <= c and c < 2 and 0 <= d and d < n))
        return;

    if (((not (tab[a][b] == tab[c][d])) == j) or ilo[c][d] == j)
        if (odl[a][b] + j < odl[c][d])
        {
            odl[c][d] = odl[a][b] + j;
            if (j) dq.push_back({c, d});
            else dq.push_front({c, d});
        }
}

inline void bfs(int i, int k)
{
    odl[i][k] = 0;

    dq.push_front({i, k});

    while (not dq.empty())
    {
        auto p = dq.front(); dq.pop_front();
        tie(i, k) = p;

        for (int j = 0; j < 2; ++j)
        {
            git(i, k, 1 - i, k, j);
            git(i, k, i, k + 1, j);
            git(i, k, i, k - 1, j);
        }
    }
}

int main(int argc, char** argv)
{
    argc_ = argc; argv_ = argv;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //gen = mt19937(arg(1));
    
    cin >> n;

    for (int i = 0; i < 2; ++i)
        for (int k = 0; k < n; ++k) 
            cin >> tab[i][k], ilo[i][k] = true, odl[i][k] = inf;

    int res = 0;

    for (int k = n - 1; k >= 0; --k)
        for (int i = 0; i < 2; ++i)
            if (ilo[i][k])
            {
                if (i == 0 and k == 0) continue;
                if (vis[tab[i][k]]) continue;
                vis[tab[i][k]] = true;
                dfs(i, k);
                ++res;
            }

    res -= not ilo[0][0];

    bfs(0, 0);

    debug(
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < n; ++j)
                cout << ilo[i][j] << ' ';
            cout << '\n';
        }
                

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < n; ++j)
                cout << odl[i][j] << ' ';
            cout << '\n';
        }
    );

    print(res + min(odl[0][n - 1], odl[1][n - 1]));
}