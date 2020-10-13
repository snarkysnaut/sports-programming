#include <vector>
#include <iostream>
#include <algorithm>
#ifndef d
#define d(...)
#endif
#define all(x) begin(x), end(x)
#define r(...) resize(__VA_ARGS__)
#define pb(...) push_back(__VA_ARGS__)
#define eb(...) emplace_back(__VA_ARGS__)
using namespace std;using ull = unsigned long long;
template<class t>using V = vector< t >;

struct Ev
{
    bool typ;
    int x, y;
    ull val;
    int t, y_id;
    Ev(bool typ, int x, int y, ull val, int t, int y_id = 0)
    :typ(typ),x(x)  ,y(y),val(val),t(t),y_id(y_id){}
};

inline bool operator< (const Ev& mn, const Ev& wc)
{
    return mn.x == wc.x? mn.typ < wc.typ : mn.x < wc.x;
}

int maxy;
int q, t; 
V< Ev > evs;

inline void gen2 (int lo, int hi, V< int >& v)
{
    if (v.empty())
        return;

    int mid = (hi - lo) / 2 + lo;
    int pop = -1; 
    ull sum1 = 0, cnt1 = 0, sum2 = 0, cnt2 = 0;
    for (int k : v)
    {
        auto& ev = evs[k];
        if ((ev.y_id <= mid and ev.typ == 0) or 
            (ev.y_id >= mid and ev.typ == 1))
        {
            ull dl = ev.x - pop;
            sum1 += dl * cnt1;
            sum2 += dl * cnt2;
            if (ev.typ == 0)
            {
                ull odl = mid - ev.y + 1;
                cnt1 += ev.val * odl;
                sum1 += ev.val * odl;
                cnt2 += ev.val;
                sum2 += ev.val;
            }
            if (ev.typ == 1)
                ev.val += sum1 + sum2 * (ev.y - (ull)mid);
            pop = ev.x;
        }
    }
    if (lo < hi)
    {
        V< V< int > > ilo(2);
        for (int k : v)
        {
            if (evs[k].y_id == mid and evs[k].typ == 1)
                continue;
            ilo[evs[k].y_id > mid].pb(k);
        }
        gen2(lo, mid, ilo[0]);
        gen2(mid + 1, hi, ilo[1]);
    }
}

int piv;

inline void gen1 (int lo, int hi, V< int >& v)
{
    if (lo == hi or v.empty())
        return;
    int mid = piv;
    V< int > tab, low;
    for (int k : v)
    {
        auto& ev = evs[k];
        if ((ev.t <= mid and ev.typ == 0) or 
            (ev.t > mid and ev.typ == 1))
        {
            tab.pb(k);
            low.pb(ev.y);
        }
    }
    sort(all(low));
    low.resize(unique(all(low)) - low.begin());
    for (int k : tab)
        evs[k].y_id = lower_bound(all(low), evs[k].y) - low.begin();
    gen2(0, low.size(), tab);
    //V< V< int > > ilo(2);
    /*
    for (int k : v)
        ilo[evs[k].t > mid].pb(k);
    gen1(lo, mid, ilo[0]);
    gen1(mid + 1, hi, ilo[1]);
    */
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q; 
    int l, w; cin >> l >> w;

    for (int i = 0; i < n; ++i)
    {
        int a, b, c, d;
        cin >> a >> c >> b >> d;
        --b, --d;
        ull val = 1;
        evs.eb(0, a, c, val, t++);
        evs.eb(0, b + 1, c, 0u - val, t++);
        evs.eb(0, a, d + 1, 0u - val, t++);
        evs.eb(0, b + 1, d + 1, val, t++);
        maxy = max(maxy, d + 1);
    }

    piv = t - 1;

    for (int i = 0; i < q; ++i)
    {
        int a, c; cin >> a >> c;
        int b = a + l - 1;
        int d = c + w - 1;
        evs.eb(1, b, d, 0, t++);
        evs.eb(1, a - 1, c - 1, 0, t++);
        evs.eb(1, b, c - 1, 0, t++);
        evs.eb(1, a - 1, d, 0, t++);
        maxy = max(maxy, d);
    }

/*
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int typ; cin >> typ;
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (typ == 1)
        {
            uint val; cin >> val;
            evs.eb(0, a, c, val, t++);
            evs.eb(0, b + 1, c, 0u - val, t++);
            evs.eb(0, a, d + 1, 0u - val, t++);
            evs.eb(0, b + 1, d + 1, val, t++);
            maxy = max(maxy, d + 1);
        }
        if (typ == 2)
        {
            evs.eb(1, b, d, 0, t++);
            evs.eb(1, a - 1, c - 1, 0, t++);
            evs.eb(1, b, c - 1, 0, t++);
            evs.eb(1, a - 1, d, 0, t++);
            maxy = max(maxy, d);
        }
    }
*/
        
    V< int > tmp(t);
    for (int i = 0; i < tmp.size(); ++i)
        tmp[i] = i;

    sort(all(evs));
    gen1(0, t, tmp);

    for (int i = 0; i < evs.size(); ++i)    
        while (evs[i].t != i)
            swap(evs[i], evs[evs[i].t]);

//    for (auto& ev : evs)
//        cout << ev.typ << ' ' << ev.x << ' ' << 
//        ev.y << ' ' << ev.val << ' ' << ev.t << '\n';

    for (int i = 0; i < evs.size(); ++i)
        if (evs[i].typ == 1)
            cout << evs[i].val + evs[i + 1].val - evs[i + 2].val - 
            evs[i + 3].val << '\n', i += 3;
}