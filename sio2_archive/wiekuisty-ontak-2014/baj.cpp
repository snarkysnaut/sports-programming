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

constexpr int maxz = 20, maxn = 1e9;

int z, n;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> z;
    while (z--)
    {
        cin >> n;
        ll res = 0;
        int i = 1;
        for (; i * i <= n; ++i)
        {
            dump(i);
            res += n % i;
        }

        int a = i;

        for (int i = 1; i * i < n; ++i)
        {
            int lo = max(a, n / (i + 1) + 1);
            int hi = n / i;
            if (lo > hi) break;
            dump(lo, hi);
            dump(n % lo, n % hi);
            dump(hi - lo + 1);
            dump((ll)((n % lo) + (n % hi)) * (hi - lo + 1) / 2);
            res += (ll)((n % lo) + (n % hi)) * (hi - lo + 1) / 2;
        }

        print(res);
    }
}