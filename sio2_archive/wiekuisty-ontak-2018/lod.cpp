#include <bits/stdc++.h>
#ifdef DBG
int c__;
#define dbg(...) {if(!c__)cerr<<"\033[96;1m";++c__; \
ostream& cout=cerr;__VA_ARGS__;--c__;\
(void)(cout);if(!c__)cerr<<"\033[0m";}
#else
#define dbg(...)
#endif
#define st first
#define nd second
#define flg(...) __LINE__, __PRETTY_FUNCTION__
#define mkp(...) make_pair(__VA_ARGS__)
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(prt(__VA_ARGS__))
#define dmp(...) prt(#__VA_ARGS__, __VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
using namespace std; using ll = long long;
template<typename... t>using V=vector<t...>;
template<typename t>void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... v>void print(ostream& os, const t& a,
v&&... b){os<<a<<' ';print(os, b...);}
template<typename t>void inp(t& a){cin >> a;}
template<typename t, typename... v>void inp(t& a, v&... b){cin >> a;inp(b...);}

constexpr int maxn = 1e5 + 1, sqr = 316, rzm = maxn / sqr + 1;

struct Point
{
    ll x, y;
    Point(ll x, ll y):x(x),y(y){}
};

inline ll operator^(const Point& a, const Point& b)
{
    return a.x * b.y - b.x * a.y;
}

inline ll in_upper(const Point& a)
{
    return a.y == 0? a.x > 0 : a.y > 0;
}

inline bool operator<(const Point& mn, const Point& wc)
{
    if (in_upper(mn) != in_upper(wc))
        return in_upper(mn);

    return (mn ^ wc) != 0? (mn ^ wc) > 0 : mn.x > wc.x;
}

inline bool left_turn(Point a, Point b, Point c)
{
    b.x -= a.x, b.y -= a.y;
    c.x -= a.x, c.y -= a.y;

    return (b ^ c) > 0;
}

int n, q;
ll sum[rzm];
int val[maxn + 1];
V< Point > ilo[rzm];

V< Point > convex_hull(V< Point >& tb)
{
    V< Point > conv;

    for (auto& p : tb)
    {
        while (conv.size() >= 2 and 
        left_turn(conv[conv.size() - 2], conv[conv.size() - 1], p))
            conv.pop_back();

        conv.push_back(p);
    }

    return conv;
}

inline void construct(int v)
{
    V< ll > tb(min(sqr, n - (v * sqr) + 1));

    for (int i = 0; i < tb.size(); ++i)
        tb[i] = val[i + v * sqr];

    for (int i = 1; i < tb.size(); ++i)
        tb[i] += tb[i - 1];

    ilo[v].clear();

    for (int i = 0; i < tb.size(); ++i)
    {
        if (i == 0 and v == 0) continue;

        ilo[v].emplace_back(i + v * sqr, tb[i]);
    }

    ilo[v] = convex_hull(ilo[v]);

dbg(
    dprt(v);
    for (auto& p : ilo[v])
        prt(p.x, p.y);
    dprt("");
);
}

inline Point bin_search(int v, ll sm)
{
    int lo = 0;
    for (int b = ilo[v].size() - 1; b >= 1; b >>= 1)
        while (lo + b < ilo[v].size())
        {
            Point a = ilo[v][lo + b];
            Point c = ilo[v][lo + b - 1];

            a.y += sm; c.y += sm;

            if (c < a)
            {
                lo += b; continue;
            }
            else break;
        }


    dprt(v, lo, ilo[v][lo].x, ilo[v][lo].y + sm);
    auto rs = ilo[v][lo];
    rs.y += sm;

    return rs;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        cin >> val[i], sum[i / sqr] += val[i];

    for (int i = 0; i <= n / sqr; ++i)
        construct(i);

    for (int k = 0; k < q; ++k)
    {
        int v, c; cin >> v >> c;

        sum[v / sqr] += (c - val[v]);
        val[v] = c;

        construct(v / sqr);

        Point rs{1, 0};
        ll sm = 0;

        for (int i = 0; i <= n / sqr; ++i)
            rs = max(rs, bin_search(i, sm)), sm += sum[i];

        dprt(rs.x, rs.y);
        prt(rs.x);
    }

}