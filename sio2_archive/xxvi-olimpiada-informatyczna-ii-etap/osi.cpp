/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
#define debug(...) __VA_ARGS__ 
#else
#define debug(...)
#endif
using namespace std;
/*}}}*/

constexpr int nax = 1e6, maxm = 1e6;

int n, m;
int pre[nax + 1];
stack< int > St;
bool vis[nax + 1], ans[maxm + 1];
vector< pair< int, int > > gr[nax + 1];
vector< int > rg[nax + 1], tg[nax + 1];

void dfs1(int v, int oj)
{
    static int t = 0;
    pre[v] = t++;
    vis[v] = true;

    int cnt = 0;

    for (auto& p : gr[v])
    {
        if (p.first == oj)
        {
            ++cnt;
            if (cnt > 1)
            {
                ans[abs(p.second)] = (p.second < 0);
                rg[v].push_back(p.first);
                tg[p.first].push_back(v);
            }
        }
        else if (not vis[p.first])
        {
            ans[abs(p.second)] = (p.second < 0);
            rg[v].push_back(p.first);
            tg[p.first].push_back(v);
            dfs1(p.first, v);
        }
        else
        {
            if (pre[p.first] < pre[v])
            {
                ans[abs(p.second)] = (p.second < 0);
                rg[v].push_back(p.first);
                tg[p.first].push_back(v);
            }
        }
    }
}

void dfs2(int v)
{
    vis[v] = true;
    for (int s : rg[v])
        if (not vis[s])
            dfs2(s);
    St.push(v);
}

void dfs3(int v)
{
    vis[v] = true;
    for (int s : tg[v])
        if (not vis[s])
            dfs3(s);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].emplace_back(q, i);
        gr[q].emplace_back(p, -i);
    }

    for (int i = 1; i <= n; ++i)
        if (not vis[i])
            dfs1(i, i);

    debug({
        for (int i = 1; i <= n; ++i)
        {
            cerr << i << ": ";
            for (int s : rg[i])
                cerr << s << ' ';
            cerr << '\n';
        }
    });
        

    for (int i = 1; i <= n; ++i)
        vis[i] = false;

    for (int i = 1; i <= n; ++i)
        if (not vis[i])
            dfs2(i);

    for (int i = 1; i <= n; ++i)
        vis[i] = false;

    int res = 0;

    while (not St.empty())
    {
        int v = St.top(); St.pop();
        
        if (not vis[v])
            dfs3(v), ++res;
    }

    cout << res << '\n';

    for (int i = 1; i <= m; ++i)
        cout << (ans[i]? '<' : '>');
    
    cout << '\n';
}
