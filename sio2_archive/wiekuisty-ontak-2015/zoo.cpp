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

constexpr int nax = 5e4, maxm = 2e5;

int n, m; 
int fu[nax + 1];
bool vis[nax + 1];
bool act[nax + 1];
int deg[nax + 1];
int val[maxm + 1];
V< int > gr[nax + 1];

int find(int v)
{
    return fu[v] < 0? v : fu[v] = find(fu[v]);
}

inline bool join(int p, int q)
{
    dump(p, q);
    p = find(p); q = find(q);
    if (p == q) return false;
    if (fu[p] < fu[q]) swap(p, q);
    fu[q] += fu[p];
    fu[p] = q;
    return true;
}

int main(int argc, char** argv)
{
    argc_ = argc; argv_ = argv;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //gen = mt19937(arg(1));
    
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        int s; cin >> s;
        while (s--)
        {
            int v; cin >> v;
            val[v] xor_eq i;
            gr[i].push_back(v);
            ++deg[i];
        }
    }

    queue< int > Q;
    for (int i = 1; i <= n; ++i)
        if (deg[i] <= 5 and not vis[i])
            Q.push(i), vis[i] = true;

    while (not Q.empty())
    {
        int v = Q.front(); Q.pop();
        for (int i = 0; i < gr[v].size(); ++i)
        {
            int q = gr[v][i];
            if (v xor val[q])
            {
                val[q] xor_eq v;
                --deg[val[q]];
                if (deg[val[q]] <= 5 and not vis[val[q]])
                    Q.push(val[q]), vis[val[q]] = true;
            }
            else
            {
                gr[v][i] = gr[v].back();
                gr[v].pop_back();
                --i;
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        fu[i] = -1;

    int q; cin >> q;
    while (q--)
    {
        int s; cin >> s;
        V< int > tab(s);
        for (int& v : tab)
            cin >> v, act[v] = true;
        int il = tab.size();
        int e = 0;
        for (int v : tab)
            for (int q : gr[v])
                if (act[val[q]])
                    ++e, il -= join(val[q], v);
        int res = -(int)tab.size() + e + il + 1;
        dump(il, e, tab.size());
        --res; print(res);
        for (int v : tab)
            fu[v] = -1, act[v] = false;
    }

}