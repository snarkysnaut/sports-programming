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

constexpr int maxn = 5e4, dl = 5, sk = 750;

int n;
string tb[maxn];
int bt[maxn];
V< int > ilo[1 << dl];
set< pair< int, int > > S;

void finish()
{
    print(S.size());
    for (auto& p : S)
        print(p.st + 1, p.nd + 1);
    exit(0);
}

void solve()
{
    for (int i = 0; i < n; ++i)
        bt[i] = 0;

    for (int k = 0; k < 5; ++k)
    {
        V< bool > zl(256);
        for (int i = 0; i < zl.size(); ++i)
            zl[i] = rand() % 2;

        for (int i = 0; i < n; ++i)
            if (zl[tb[i][k]])
                bt[i] += (1 << k);
    }

    for (int i = 0; i < n; ++i)
        ilo[bt[i]].push_back(i);

    for (int i = 0; i < (1 << dl); ++i)
    {
        int g = (~i & ((1 << dl) - 1));
        dump(i, g);
        if (g < i) continue;
        for (int v = 0; v < ilo[i].size(); ++v)
            for (int w = 0; w < ilo[g].size(); ++w)
            {
                int a = min(ilo[i][v], ilo[g][w]);
                int b = max(ilo[i][v], ilo[g][w]);
                S.insert(make_pair(a, b));
                if (S.size() == (int)1e5)
                    finish();
            }
    }

    for (int i = 0; i < (1 << dl); ++i)
        ilo[i].clear();
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> tb[i];

    for (int i = 0; i < sk; ++i)
        solve();

    finish();
}