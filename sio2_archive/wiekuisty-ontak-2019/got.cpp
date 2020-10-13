#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

constexpr int nax = 12e4;
constexpr ld eps = 1e-9;

struct State
{
    int v, c;
};

int n; ld r;
State dp[nax + 1][2];
bool vil[nax + 1];
vector< int > gr[nax + 1];

ld eval(const State& a)
{
    return a.v - a.c * r;
}

bool operator<(const State& a, const State& b)
{
    return eval(a) < eval(b);
}

bool operator>(const State& b, const State& a)
{
    return eval(a) < eval(b);
}

State operator+(const State& a, const State& b)
{
    return State{a.v + b.v, a.c + b.c};
}

bool comp(const State& a, const State& b)
{
    return (ll)a.v * b.c < b.v * a.c;
}

State mur(const State& a)
{
    return State{a.v + 1, a.c};
}

State kill(const State& a, bool fl = true)
{
    return State{a.v - fl, a.c - 1};
}

void dfs(const int v, const int oj)
{
    dp[v][0] = {0, 1}, dp[v][1] = {1, 1};

    for (int s : gr[v]) 
        if (s != oj) dfs(s, v);

    for (int s : gr[v])
        if (s != oj)
        {
            if (not vil[v])
                dp[v][1] = min({mur(dp[v][0]) + kill(dp[s][1]),
            mur(dp[v][0]) + kill(dp[s][0], 0), dp[v][1] + min(dp[s][0], kill(dp[s][1]))});
            if (vil[v])
                dp[v][1] = min({mur(dp[v][0]) + kill(dp[s][1]),
            mur(dp[v][0]) + kill(dp[s][0], 0), dp[v][1] + min(dp[s][0], kill(dp[s][1])), dp[v][1] + kill(dp[s][1])});
            dp[v][0] = min(dp[v][0] + dp[s][0], dp[v][0] + dp[s][1]);
        }

    if (vil[v])
        dp[v][0] = {nax + 1, 1};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    string s; cin >> s;
    for (int i = 1; i <= n; ++i)
        vil[i] = (s[i - 1] == 'V');

    for (int i = 0; i < n - 1; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].push_back(q);
        gr[q].push_back(p);
    }

    ld lo = 0.0l, hi = 1.0l;

    State res{1, 1};

    for (int i = 1; i <= 40; ++i)
    {
        r = (lo + hi) / 2;
        //cerr << r << '\n';
        dfs(1, 1);
        State s = comp(dp[1][0], dp[1][1])? dp[1][0] : dp[1][1];
        //cerr << s.v << ' ' << s.c << '\n';
        if (comp(s, res))
            res = s;
        //cerr << eval(s) << '\n';
        if (not (eval(dp[1][0]) - eps > 0) or not (eval(dp[1][1]) - eps > 0))
            hi = r;
        else lo = r;
    }

    int g = __gcd(res.v, res.c);
    cout << res.v / g << ' ' << res.c / g << '\n';
}

//p/q <= r
//p <= q*r
//p - q*r <= 0