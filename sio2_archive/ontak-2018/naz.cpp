#include <bits/stdc++.h>
#ifdef DBG
#define dbg(...) {cerr<<"\033[96;1m";ostream& cout=cerr;__VA_ARGS__;\
(void)(cout);cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define nd second
#define st first
#define flg(), __LINE__, __PRETTY_FUNCTION__
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) print(cout, #__VA_ARGS__, __VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template<typename... t>using V = vector< t... >;
template<typename t> void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... v> void print(ostream& os, const t& a,
v&&... b){os<<a<<' ';print(os, b...);}

struct Ev
{
    int t, v;
    Ev(int t = 0, int v = 0):t(t),v(v){}
};

struct Ve
{
    int h; Ev e;   
    Ve(int h = -1, Ev e = Ev()):h(h),e(e){}
};

inline bool operator< (const Ve& mn, const Ve& wc)
{
    return mn.h < wc.h;
}

string s;
int n, k;
V< Ve > tb;
V< int > pref;
V< V< Ev > > dp;

void gen_pref()
{
    pref.resize(s.size());
    pref[0] = 0;
    int v = 0, r = 0;
    for (int i = 1; i < s.size(); ++i)
    {
        if (i <= r)
            pref[i] = min(r - i + 1, pref[i - v]);

        while (i + pref[i] < s.size() and s[pref[i]] == s[i + pref[i]])
            ++pref[i];

        if (r < i + pref[i] - 1)
        {
            r = i + pref[i] - 1;
            v = i;
        }
    }

    for (int i = 1; i < s.size(); ++i)
        pref[i] = min(i, pref[i]);

dbg(
    for (int i = 0; i < s.size(); ++i)
        cerr << pref[i] << ' ';
    cerr << '\n';
    for (int i = 0; i < s.size(); ++i)
        cerr << s[i] << ' ';
    cerr << '\n';
);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> k;

    n = s.size();

    gen_pref();

    tb.resize(n + 1);
    dp.resize(k + 1, V< Ev >(n + 1));

    dp[0][0] = Ev(3, 0);

    for (int i = 1; i <= k; ++i)
    {
        char c; cin >> c;

        if (c == '?')
        {
            for (auto& ve : tb)
                ve = Ve();

            for (int j = 0; j < n; ++j)
                if (dp[i - 1][j].t)
                    tb[j + 1] = 
                    max(tb[j + 1], Ve(pref[j] + j, Ev(2, j)));

            for (int j = 0; j < n; ++j)
                if (dp[i - 1][j].t)
                    dp[i][j + 1] = {1, s[j]};

            Ve mk;
            for (int j = 0; j <= n; ++j)
            {
                mk = max(mk, tb[j]);

                if (j <= mk.h)
                    dp[i][j] = {mk.e.t, j - mk.e.v};
            }
        }
        else if (c == 'B')
        {
            c = 2; 
            int v; cin >> v;

            for (int j = 0; j < n; ++j)
                if (dp[i - 1][j].t and pref[j] >= v)
                    dp[i][j + v] = {c, v};
        }
        else if (c == 'A')
        {
            c = 1;
            char q; cin >> q;

            for (int j = 0; j < n; ++j)
                if (dp[i - 1][j].t and s[j] == q)
                    dp[i][j + 1] = {c, q};
        }
    }

    if (dp[k][n].t)
    {
        dprt("YES");
    }
    else
    {
        dprt("NO");
        return prt(-1), 0;
    }

    V< pair< char, int > > odp;

    int i = k, j = n;
    while (dp[i][j].t != 3)
    {
        if (dp[i][j].t == 1)
        {
            odp.push_back({'A', dp[i][j].v});
            --j;
        }
        else if (dp[i][j].t == 2)
        {
            odp.push_back({'B', dp[i][j].v});
            j -= dp[i][j].v;
        }

        --i;

        assert(dp[i][j].t);
    }

    reverse(all(odp));

    prt(k);
    for (int i = 0; i < k; ++i)
        if (odp[i].st == 'A')
            prt(odp[i].st, (char)(odp[i].nd));
        else
            prt(odp[i].st, odp[i].nd);
}