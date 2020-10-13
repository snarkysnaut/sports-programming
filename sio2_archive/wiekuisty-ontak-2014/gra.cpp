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

constexpr int maxn = 1e6;

int n;
string s;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    int st = 0;
    for (int i = 0; i < n; ++i)
        if (s[i] == 'R')
            st = st xor (i + 1);

    int res = 0;
    for (int i = 0; i < n; ++i)
        if (s[i] == 'R')
            if (((i + 1) xor st) < i + 1)
                ++res;

    print(res);
}