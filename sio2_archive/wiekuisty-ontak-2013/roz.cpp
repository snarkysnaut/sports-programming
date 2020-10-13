#include <bits/stdc++.h>
#ifndef dbg
#define dbg(...)
#endif
#define bgn(...) begin(__VA_ARGS__)
#define rsz(...) resize(__VA_ARGS__)
#define arg(...) atoi(argv[__VA_ARGS__])
#define emp(...) emplace_back(__VA_ARGS__)
#define psh(...) push_back(__VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) print(cerr, #__VA_ARGS__, __VA_ARGS__)
#define all(...) bgn(__VA_ARGS__), end(__VA_ARGS__)
#define siz(...) static_cast< int >((__VA_ARGS__).size())
using namespace std; using ll = long long;
template< typename... t > using V = vector< t... >;
template< typename... t > using outit = ostream_iterator< t... >;
void print(ostream& os){os << '\n';} template< typename t, typename... v >
void print(ostream& os, const t& a, v&&... b){os << a << ' '; print(os, b...);}

int n, s;
V< int > sum;
V< V< int > > gr;

int dfs(int, int, int);

inline int spr(int v)
{
    return dfs(1, 1, v);
}

int dfs(int v, int oj, int val)
{
    ddmp(v);
    int res = 0;
    sum[v] = 1;
    for (int s : gr[v])
        if (s != oj)
        {
            res += dfs(s, v, val);
            sum[v] += sum[s];
        }

    if (v == oj)
    {
        if (sum[v] < val)
            return --res;
        else
            return res;
    }

    if (sum[v] >= val)
    {
        sum[v] = 0, ++res;
        dprt(v);
    }
    return res;
}

int main(int argc, char** argv)
{
    (void)(argc); (void)(argv);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	
    cin >> n >> s;

    gr.rsz(n + 1);
    sum.rsz(n + 1);
    for (int i = 1; i <= n - 1; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].psh(q);
        gr[q].psh(p);
    }

    int lo = 1;
    for (int b = n - 1; b >= 1; b >>= 1)
        while (lo + b <= n and spr(lo + b) >= s - 1)
            lo += b;
    prt(lo);
}