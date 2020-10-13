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

#include "ofe.h"

constexpr int logg = 13;

int en;
int tab[1 << 15];

inline bool valid(int v)
{
    return 0 <= v and v < en;
}

inline int compare(int a, int b)
{
    if (not valid(b) or not valid(a))
        return valid(a)? a : b;
    return cmp(a + 1, b + 1)? a : b;
}

int main(int argc, char** argv)
{
    en = getN();
    int r = 1;
    while (r < en)
        r <<= 1;
    for (int i = 0; i < en; ++i)
        tab[i + r] = i;
    for (int i = en; i < r; ++i)
        tab[i + r] = en;
    for (int i = r - 1; i >= 1; --i)
    {
        int a = tab[i << 1], b = tab[(i << 1) + 1];
        tab[i] = compare(a, b);
    }
    tab[tab[1] + r] = en;
    for (int i = 1; i < r * 2; ++i)
        dump(i, tab[i]);
    for (int i = r - 1; i >= 1; --i)
    {
        int a = tab[i << 1], b = tab[(i << 1) + 1];
        if (a == tab[i] or b == tab[i]) continue;
        tab[i] = compare(a, b);
    }
    for (int i = 1; i < r * 2; ++i)
        dump(i, tab[i]);
    dump(tab[1] + 1);
    answer(tab[1] + 1);
}