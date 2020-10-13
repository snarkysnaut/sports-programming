#pragma GCC optimize("O3")
/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_ = 0;
#define cout (c_?cerr:cout)
#define debug(...) \
{if(!c_++)cerr<<"\033[96;1m"; \
__VA_ARGS__; \
if(!--c_)cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define assrt(...) debug(\
if (not (__VA_ARGS__)) \
    exit((cerr << __LINE__ << ": " << #__VA_ARGS__ << '\n', 0));\
)
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template < typename t > using V = vector< t >;
template < typename t, size_t s > using A = array< t, s >;
void print() {cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{ while (a != b) cout << (*a++) << ' '; cout << '\n';}
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__ << ": "; print_range(__VA_ARGS__))
/*}}}*/

constexpr int nax = 1e6;

int n, gr[nax + 1], dg[nax + 1], dl[nax + 1];
queue< int > Q;
bool vis[nax + 1];

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    cin >> gr[1];
    gr[1] = -1;
    for (int i = 2; i <= n; ++i)
        cin >> gr[i], ++dg[gr[i]];

    for (int i = 1; i <= n; ++i)
        if (not dg[i]) Q.push(i);

    while (not Q.empty())
    {
        int v = Q.front(); Q.pop();
        vis[v] = true;
        if (gr[v] == -1) continue;
        dl[gr[v]] = max(dl[gr[v]], dl[v] + 1);
        --dg[gr[v]];
        if (not dg[gr[v]])
            Q.push(gr[v]);
    }

    int res = 0;
    int cnt = 0;

    for (int i = 1; i <= n; ++i)
        if (not vis[i])
        {
            int naj = 0;
            int d = 0;
            int v = i;
            do
            {
                vis[v] = true;
                naj = max(naj, dl[v]);
                ++d; v = gr[v];
            } while (v != i);

            res += naj + d;
            ++cnt;
        }

    print(cnt, res + dl[1]);
}