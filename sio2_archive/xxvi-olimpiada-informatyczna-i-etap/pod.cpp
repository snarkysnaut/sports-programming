//Jakub Wasilewski
/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define debug(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) debug(print(#__VA_ARGS__, '=',  __VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
using namespace std; using ll = long long; 
template< typename t > using V = vector< t >; void print(){cout<<'\n';}
template< typename t, typename... v > void print(const t& a, v&&... b)
{cout << a << (sizeof...(b)? " " : ""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
/*}}}*/

constexpr int dax = 150;

int tab[dax], prv[dax], dp[dax], mks = -1;
int cnt[2 * dax + 1][2 * dax + 1];
pair< string, string > ans[2 * dax + 1][2 * dax + 1];

void gen(int v)
{
    if (v and dp[v - 1] > dax * 2) return;

    int pd[dax], vrp[dax];

    for (int i = 0; i < dax; ++i)
        pd[i] = 0, vrp[i] = v;

    string s;
    for (int i = 0; i < v; ++i)
        s += string(1, 'a' + tab[i]);

    debug(if (v) dump(s, dp[v - 1]));

    for (int i = v - 1; i >= 0; --i)
    {
        int q = tab[i]; pd[i] = (i == v - 1? 1 : pd[i + 1]) << 1;

        if (vrp[q] != v)
            pd[i] -= (vrp[q] + 1 < v? pd[vrp[q] + 1] : 1);

        vrp[q] = i;

        ll a = (i == 0? 1 : dp[i - 1]);
        ll b = pd[i];
        ll c = dp[v - 1];

        dump(a, b, c);

        if (a * b >= dax * 2 + 1) continue;
        if (cnt[a * b][c] and cnt[a * b][c] < mks + 1) continue;

        cnt[a * b][c] = mks + 1;
        ans[a * b][c] = {s.substr(0, i), s.substr(i)};
    }
    
    if (v == dax) return;

    for (int i = 0; i < dax; ++i)
    {
        tab[v] = i; dp[v] = (v == 0? 1 : dp[v - 1]) << 1;

        if (prv[i] != -1)
            dp[v] -= (prv[i] - 1 >= 0? dp[prv[i] - 1] : 1);

        int tmp = prv[i];
        if (prv[i] == -1) mks = i;
        prv[i] = v;

        gen(v + 1);

        prv[i] = tmp;
        if (prv[i] == -1) mks = i - 1;
        
        if (prv[i] == -1) break;
    }
}

inline char foo(int v)
{
    if ('a' + v <= 'z') return (char)v + 'a';
    v -= 'z' - 'a' + 1;
    if ('0' + v <= '9') return (char)v + '0';
    v -= '9' - '0' + 1;
    if ('A' + v <= 'Z') return (char)v + 'A';
    return '!';
}

inline string solve(ll v, int q = 0)
{
    if (v == 1) return "";
    for (int i = 2; i < 2 * dax + 1; ++i)
        if (ans[i][v % i].nd.size())
        {
            string res;
            dump(i, v % i, ans[i][v % i].st, ans[i][v % i].nd);
            for (char c : ans[i][v % i].st)
                res += string(1, foo(c - 'a' + q));
            res += solve((v / i) + ((v % i == 0? 0 : 1)), q + cnt[i][v % i]);
            for (char c : ans[i][v % i].nd)
                res += string(1, foo(c - 'a' + q));
            return res;
        }
    return string((int)1e3 + 1, '!');
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < dax; ++i)
        prv[i] = -1;

    for (int i = 2; i < 2 * dax + 1; ++i)
        ans[i][0] = {string(), string(i - 1, 'a')}, cnt[i][0] = 1;

    gen(0);

debug(
    for (int i = 2; i < 2 * dax + 1; ++i)
    {
        cerr << i << ": ";
        for (int k = 0; k < i; ++k)
            cerr << (cnt[i][k]) << ' ' << ans[i][k].st << ' ' << ans[i][k].nd << '\n';
        cerr << '\n';
    }
);

    int q; cin >> q;
    while (q--)
    {
        ll v; cin >> v;
        auto s = solve(v);
        print(s);
    }
        
}