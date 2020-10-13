/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define debug(...) {}
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

constexpr int nax = 1e5;

inline ostream& operator<<(ostream& os, const pair< ll, ll >& a)
{
    return os << '(' << a.st << ", " << a.nd << ')';
}

int n; ll t;
ll ilo[4 * nax + 1];
pair< ll, ll > rt, sm;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;

    for (int i = 1, v = 1; i <= 4 * n; ++i, ++v)
    {
        if (v == n + 1) v = 1;
        if (v == i) cin >> ilo[i];
        else ilo[i] = ilo[v];
    }

    cin >> rt.st >> rt.nd;

    for (int i = 0; i < 4 * n; ++i)
    {
        sm.st += (i & 2? -1 : 1) * (i & 1) * ilo[i + 1];
        sm.nd += (i & 2? -1 : 1) * !(i & 1) * ilo[i + 1];
        dump(sm.st, sm.nd);
    }

    sm.st = -sm.st; sm.nd = -sm.nd;

    dump(sm);
        
    for (int i = 1; i <= 4 * n; ++i)
        ilo[i] += ilo[i - 1] + 1;

    ll lim = (t + ilo[4 * n] - 1) / ilo[4 * n];

    ll res = not rt.st and not rt.nd;

    if (t == 0) return print(res), 0;

    pair< ll, ll > lp = {sm.st * (lim - 1) + rt.st, sm.nd * (lim - 1) + rt.nd};
    pair< ll, ll > pp, qq;
    for (int i = 0; i < 4 * n; ++i, pp = qq)
    {
        qq.st += (i & 2? -1 : 1) * (i & 1) * (ilo[i + 1] - ilo[i] - 1);
        qq.nd += (i & 2? -1 : 1) * !(i & 1) * (ilo[i + 1] - ilo[i] - 1);
        auto q = qq, p = pp, r = rt, s = sm, l = lp;

        if (p.st != q.st)
            swap(p.st, p.nd), swap(q.st, q.nd), swap(r.st, r.nd), swap(s.st, s.nd), swap(l.st, l.nd);

        if (l.st == p.st and min(p.nd, q.nd) <= l.nd and l.nd <= max(p.nd, q.nd))
        {
            ll k = ilo[4 * n] * (lim - 1) + ilo[i] + abs(l.nd - p.nd);
            if (l.nd != p.nd and k <= t) 
            {
                dump(i, pp, qq, l);
                ++res;
            }
        }

        if (s.st)
        {
            if ((p.st - r.st) % s.st) continue;
            ll a = (p.st - r.st) / s.st;
            dump(a, p, q, r);
            if (a < 0 or a >= lim - 1) continue;
            ll y = a * s.nd + r.nd;
            ll k = a * ilo[4 * n] + abs(y - p.nd);
            if (not (min(p.nd, q.nd) <= y and y <= max(p.nd, q.nd)))
                continue;
            if (y != p.nd and k <= t) ++res;
        }
        else
        {
            if (s.nd)
            {
                if (r.st != p.st) continue;
                ll lo = p.nd; ll hi = q.nd;
                lo += (lo < hi? 1 : -1);
                dump(p, q, r, s, lo, hi);
                if (lo > hi) swap(lo, hi);
                lo -= r.nd; hi -= r.nd;
                if (s.nd < 0) lo = -lo, hi = -hi, s.nd = -s.nd, swap(lo, hi);
                dump(lo, hi);
                if (hi < 0) continue;
                lo = max(lo, 0ll);
                ll a = (lo + s.nd - 1) / s.nd;
                ll b = hi / s.nd;
                b = min(b, lim - 2);
                res += max(0ll, b - a + 1);
                if (b - a + 1 > 0)
                    dump(p, q, r, lo, hi, a, b);
            }
            else
            {
                if (r.st == p.st and min(p.nd, q.nd) <= r.nd and r.nd <= max(p.nd, q.nd) and r.nd != p.nd)
                    res += lim - 1;
            }
        }
    }

    cout << res << '\n';
}