#include <bits/stdc++.h>
#ifdef LOCAL
#define debug(...) {__VA_ARGS__;}
#else
#define debug(...) {}
#endif
#define st first
#define nd second
using namespace std;
using ll = long long;

constexpr int nax = 5e5;

int n, sum[nax + 1]; bool pat[nax + 1];
ll dp[nax + 1], pd[nax + 1];
vector< ll > pre, suf;
vector< pair< int, ll > > dia;
vector< pair< int, ll > > gr[nax + 1];

void dfs1(const int v, const int oj)
{
    sum[v] = 1;
    for (auto& p : gr[v])
    {
        int s = p.st;
        if (s != oj)
            dfs1(s, v), sum[v] += sum[s];
    }
}

pair< ll, int > dfs2(const int v, const int oj)
{
    pair< ll, int > r = {0ll, v};

    for (auto& p : gr[v])
    {
        int s = p.st;
        if (s != oj)
        {
            auto q = dfs2(s, v);
            q.st += p.nd;
            r = max(r, q);
        }
    }

    return r;
}

bool dfs3(const int v, const int oj, const int q, const ll d = 0ll)
{
    if (v == q)
    {
        pat[v] = true;
        dia.push_back({v, d});
        return true;
    }

    for (auto& p : gr[v])
    {
        int s = p.st;
        if (s != oj and dfs3(s, v, q, p.nd))
        {
            pat[v] = true;
            dia.push_back({v, d});
            return true;
        }
    }
    return false;
}

void dfs4(const int v, const int oj)
{
    ll naj = 0, naj2 = 0;
    for (auto& p : gr[v])
        if (not pat[p.st] and p.st != oj)
        {
            dfs4(p.st, v);

            ll d = dp[p.st] + p.nd;
            if (d >= naj)
                naj2 = naj, naj = d;
            else if (d > naj2)
                naj2 = d;
            
            dp[v] = max(dp[v], dp[p.st] + p.nd);
            pd[v] = max(pd[v], pd[p.st]);
        }
    
    if (not pat[v])
        pd[v] = max(pd[v], naj + naj2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n - 1; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].push_back({q, 0ll});
        gr[q].push_back({p, 0ll});
    }
    
    dfs1(1, 1);

    for (int i = 1; i <= n; ++i)
        for (auto& p : gr[i])
        {
            if (sum[p.st] > sum[i])
                p.nd = (ll)sum[i] * (n - sum[i]);
            else
                p.nd = (ll)sum[p.st] * (n - sum[p.st]);
        }

    debug(
        for (int i = 1; i <= n; ++i)
            cerr << sum[i] << ' ';
        cerr << '\n';
        for (int i = 1; i <= n; ++i)
            for (auto& p : gr[i])
                cerr << i << ' ' << p.st << ' ' << p.nd << '\n';
        for (int i = 1; i <= n; ++i)
            cerr << sum[i] << ' ';
        cerr << '\n';
    );

    ll d; int p, q;
    tie(d, p) = dfs2(1, 1);
    tie(d, q) = dfs2(p, p);

    debug(
        cerr << p << ' ' << q << ' ' << d << '\n';
    );

    dfs3(p, p, q);

    reverse(begin(dia), end(dia));

    debug(
        for (auto& p : dia)
            cerr << p.st << ' ' << p.nd << '\n';
    );

    for (int i = 1; i <= n; ++i)
        if (pat[i])
            dfs4(i, i);
            
    debug(
        for (int i = 1; i <= n; ++i)
            cerr << i << ' ' << dp[i] << ' ' << pd[i] << '\n';
    );

    ll su = 0;

    pre.resize(dia.size());
    suf.resize(dia.size());

    for (int i = 0; i < dia.size(); ++i)
    {
        su += dia[i].nd;
        pre[i] = su + dp[dia[i].st];
    }

    su = 0;

    for (int i = (int)(dia.size()) - 1; i >= 0; --i)
    {
        if (i + 1 < dia.size())
            su += dia[i + 1].nd;
        suf[i] = su + dp[dia[i].st];
    }

    for (int i = 1; i < dia.size(); ++i)
        pre[i] = max(pre[i], pre[i - 1]);

    for (int i = (int)(dia.size()) - 2; i >= 0; --i)
        suf[i] = max(suf[i], suf[i + 1]);

    debug(
        for (int i = 0; i < dia.size(); ++i)
            cerr << pre[i] << ' ' << suf[i] << '\n';
    )

    ll res = 0;

    for (int i = 0; i < (int)(dia.size()) - 1; ++i)
        res = max(res, pre[i] + suf[i + 1]);

    for (int i = 0; i < dia.size(); ++i)
        res = max(res, d + pd[dia[i].st]);


    su = 0;
    for (int i = 1; i <= n; ++i)
        for (auto& p : gr[i])
            su += p.nd;

    su >>= 1;

    res = su - res;

    cout << res << '\n';
}