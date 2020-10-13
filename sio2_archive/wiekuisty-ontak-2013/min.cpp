/*{{{*/
#include <bits/stdc++.h>
#define st first
#define nd second
#ifdef LOCAL
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;if(!(--c_))cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
#define dump(...) debug(print(#__VA_ARGS__, " = ", __VA_ARGS__))
using namespace std; using ll = long long;
void print(){cout << '\n';}
template< typename t, typename... v >
void print(const t& a, v&&... b){cout<<a<<(sizeof...(b)? " " : "");print(b...);}
template< typename t > using V = vector< t >;
/*}}}*/

constexpr int nax = 1e5, logg = 18, rozm = (1 << logg);

int t, n;
stack< int > S;
V< int > gr[nax], rg[nax];
V< int > sr[nax + 1];
bool vis[nax];
ll poz[nax]; int lo[nax], hi[nax], slo[nax], shi[nax], spoj[nax + 1];
pair< ll, int > mi[rozm << 1], ma[rozm << 1];

void dfs(int v)
{
    vis[v] = true;

    for (int s : gr[v])
        if (not vis[s])
            dfs(s);

    S.push(v);
}

void dfs2(int v, int id)
{
    spoj[v] = id;

    for (int s : rg[v])
        if (not spoj[s])
            dfs2(s, id);
}

void dfs3(int v)
{
    vis[v] = true;
    for (int s : sr[v])
    {
        if (not vis[s]) 
            dfs3(s);

        slo[v] = min(slo[v], slo[s]);
        shi[v] = max(shi[v], shi[s]);
    }
}

void insertmi(int v, const pair< ll, int > c)
{
    v += rozm;
    mi[v] = c;
    for (v >>= 1; v >= 1; v >>= 1)
        mi[v] = min(mi[(v << 1)], mi[(v << 1) + 1]);
}

void insertma(int v, const pair< ll, int > c)
{
    v += rozm;
    ma[v] = c;
    for (v >>= 1; v >= 1; v >>= 1)
        ma[v] = max(ma[(v << 1)], ma[(v << 1) + 1]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while (t--)
    {
        cin >> n;

        for (int i = 0; i < n; ++i)
        {
            gr[i].clear(), rg[i].clear(), spoj[i] = vis[i] = 0;
            sr[i].clear();
            shi[i + 1] = -1;
            slo[i + 1] = n;
        }

        for (int i = 0; i < n; ++i)
        {
            ll v, r; cin >> v >> r;
            poz[i] = v;
            insertmi(i, {v - r, i});
            insertma(i, {v + r, i});
            //mi[i + rozm] = {v - r, i};
            //ma[i + rozm] = {v + r, i};
        }

        //for (int i = (rozm + n - 1) / 2; i >= 1; --i)
        //{
            //mi[i] = min(mi[i << 1], mi[(i << 1) + 1]);
            //ma[i] = max(ma[i << 1], ma[(i << 1) + 1]);
        //}
        
        for (int i = 0; i < n; ++i)
        {
            int l = lower_bound(poz, poz + n, mi[i + rozm].st) - poz;
            int r = upper_bound(poz, poz + n, ma[i + rozm].st) - poz - 1;
            lo[i] = l, hi[i] = r;
            pair< ll, int > a = {LLONG_MAX, 0};
            pair< ll, int > b = {LLONG_MIN, 0};

            l += rozm, r += rozm;
            a = min(mi[l], mi[r]);
            b = max(ma[l], ma[r]);

            while ((l >> 1) != (r >> 1))
            {
                if ((l & 1) == 0)
                {
                    a = min(mi[l + 1], a);
                    b = max(ma[l + 1], b);
                }
                
                if ((r & 1) == 1)
                {
                    a = min(mi[r - 1], a);
                    b = max(ma[r - 1], b);
                }
                l >>= 1; r >>= 1;
            }

            gr[i].push_back(a.nd);
            gr[i].push_back(b.nd);
            rg[a.nd].push_back(i);
            rg[b.nd].push_back(i);

        }

    debug(
        for (int i = 0; i < n; ++i)
            print(i, lo[i], hi[i]);
        for (int i = 0; i < n; ++i)
        {
            cout << i << ": ";
            for (int s : gr[i])
                cout << s << ' ';
            cout << '\n';
        }
    );

        for (int i = 0; i < n; ++i)
            if (not vis[i])
                dfs(i);

        int id = 0;
        while (not S.empty())
        {
            int v = S.top(); S.pop();

            if (not spoj[v])
                dfs2(v, ++id);
        }

        for (int i = 0; i < n; ++i)
            vis[i] = false;

        for (int i = 0; i < n; ++i)
        {
            slo[spoj[i]] = min(slo[spoj[i]], lo[i]);
            shi[spoj[i]] = max(shi[spoj[i]], hi[i]);
        }

        for (int i = 0; i < n; ++i)
            for (int s : gr[i])
                if (spoj[s] != spoj[i])
                    sr[spoj[i]].push_back(spoj[s]);

        for (int i = 1; i <= id; ++i)
            if (not vis[i])
                dfs3(i);

        for (int i = 0; i < n; ++i)
        {
            lo[i] = slo[spoj[i]];
            hi[i] = shi[spoj[i]];
        }

        for (int i = 0; i < n; ++i)
            cout << (hi[i] - lo[i] + 1) << ' ';
        cout << '\n';

    debug(
        for (int i = 0; i < n; ++i)
            print(i, lo[i], hi[i], spoj[i], slo[i], shi[i]);
    );
    }
}