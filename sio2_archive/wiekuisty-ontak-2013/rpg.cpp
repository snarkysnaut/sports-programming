/*{{{*/
#include <bits/stdc++.h>
#include "crpglib.h"
#define st first
#define nd second
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

int main(int argc, char** argv)
{
    argc_ = argc; argv_ = argv;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //gen = mt19937(arg(1));
    
    V< pair< int, int > > tmp = inicjuj();

    int n = tmp.size();

    ll val1 = 0, val2 = 0;

    for (auto p : tmp)
        val1 += p.st, val2 += p.nd;

    V< pair< ll, int > > tab;

    for (int i = 0; i < tmp.size(); ++i)
    {
        auto p = tmp[i];
        tab.push_back({val1 * p.st + val2 * p.nd, i + 1});
    }

    sort(all(tab));

    reverse(all(tab));

    V< bool > vis(n);

    ll sum[2] = {0, 0};

    for (int i = 0; i < n; ++i)
        sum[i & 1] += tab[i].st;

    bool z = sum[0] > sum[1];

    wybierz(z);

    int pt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!z xor (i & 1))
        {
            int q = przeciwnik();
            vis[q - 1] = true;
        }
        else
        {
            while (vis[tab[pt].nd - 1])
                ++pt;
            wez(tab[pt++].nd);
        }
    }
}