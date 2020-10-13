/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m"; \
++c_; __VA_ARGS__ ; --c_; \
if (!c_)cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define st first
#define nd second
#define dump(...) debug(print(#__VA_ARGS__, __VA_ARGS__))
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template< typename t > using V = vector< t >;
void print() { cout << '\n'; }
template< typename t, typename... v > void print(const t& a, v&&... b)
{ cout << a << (sizeof...(b)? " " : ""); print(b...); }
/*}}}*/

constexpr int maxn = 100, maxk = 1e6;

int n, k;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    if (k < n)
        return print("NIE"), 0;

    print("TAK");

    int r = k - (n - 1);
    for (int i = 1; i <= n; ++i)
        for (int k = 1; k <= n; ++k)
            cout << (i == k? r : 1) << " \n"[k==n];
}