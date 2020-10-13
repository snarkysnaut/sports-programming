/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;if(!(--c_))cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define st first
#define nd second
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
#define dump(...) debug(print(#__VA_ARGS__, " = ", __VA_ARGS__))
using namespace std; using ll = long long;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, v&&... b){cout<<a<<(sizeof...(b)? " " : "");print(b...);}
template< typename t > using V = vector< t >;
/*}}}*/

constexpr int nax = 1e5;
constexpr int mod[2] = {1000000000 + 7, 1000000000 + 9};

int n, k, q;
pair< int, int > ful;
V< int > gr[nax + 1];
int val[nax + 1], sum[nax + 1], hsz[2][nax + 1];
bool vis[nax + 1], res[nax + 1], zl[nax + 1];

void dfs1(int v, int oj)
{
    sum[v] = 1;
    for (int i = 0; i < gr[v].size(); ++i)
    {
        int s = gr[v][i];
        if (vis[s])
        {
            gr[v][i] = gr[v].back();
            gr[v].pop_back(); --i;
            continue;
        }
        if (s == oj) continue;
        dfs1(s, v);
        sum[v] += sum[s];
    }
}

int centro(int v)
{
    int oj = v;
    bool fl = true;
    int sm = sum[v];
    while (fl)
    {
        fl = false;
        for (int s : gr[v])
            if (s != oj and sum[s] * 2 > sm)
            {
                oj = v; v = s;
                fl = true;
                break;
            }
    }
    return v;
}

int rot = 0;
V< pair< ll, ll > > tab;
set< pair< int, int > > S;

bool dfs2(int v, int oj, pair< int, int > d)
{
    if (zl[val[v]]) return false;
    zl[val[v]] = true;
    bool fl = false;

    d.st = (d.st + hsz[0][val[v]]) % mod[0];
    d.nd = (d.nd + hsz[1][val[v]]) % mod[1];

    auto q = ful;
    q.st -= d.st;
    q.nd -= d.nd;
    if (q.st < 0) q.st += mod[0];
    if (q.nd < 0) q.nd += mod[1];
    if (S.find({q.st, q.nd}) != S.end())
        fl = true;

    auto r = d;
    r.st -= hsz[0][val[rot]];
    r.nd -= hsz[1][val[rot]];
    if (r.st < 0) r.st += mod[0];
    if (r.nd < 0) r.nd += mod[1];

    tab.push_back(r);

    for (int s : gr[v])
        if (s != oj)
            fl |= dfs2(s, v, d);

    res[v] |= fl;
    zl[val[v]] = false;
    
    return fl;
}

void eval(int v)
{
    rot = v;
    zl[val[v]] = true;
    for (int i = 0; i < 2; ++i)
    {
        S.clear();
        S.insert({0, 0});
        for (int s : gr[v])
        {
            if (dfs2(s, v, {hsz[0][val[v]], hsz[1][val[v]]}))
                res[v] = true;
            for (auto& p : tab)
                S.insert(p);
            tab.clear();
        }
        reverse(all(gr[v]));
    }
    zl[val[v]] = false;
}

void deco(int v)
{
    dfs1(v, v);
    int c = centro(v);
    eval(c);
    vis[c] = true;
    for (int s : gr[c])
        deco(s);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> q;

    srand(123);
    for (int l = 0; l < 2; ++l)
        for (int i = 1; i <= k; ++i)
        {
            int q = rand() % mod[l];
            q xor_eq i;
            int h = 1;
            for (int j = 0; j < 3; ++j)
                h = ((ll)h * q) % mod[l];
            hsz[l][i] = h;
            if (l == 0) ful.st = (ful.st + hsz[l][i]) % mod[l];
            if (l == 1) ful.nd = (ful.nd + hsz[l][i]) % mod[l];
        }

    for (int i = 1; i <= n; ++i)
        cin >> val[i];

    for (int i = 0; i < n - 1; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].push_back(q);
        gr[q].push_back(p);
    }

    deco(1);
    
    while (q--)
    {
        int v; cin >> v;
        print(res[v]? "YES" : "NO");
    }
}