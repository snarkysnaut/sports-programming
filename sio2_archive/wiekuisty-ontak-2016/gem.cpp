#include <bits/stdc++.h>
#define st first
#define nd second

constexpr int nax = 2e5;
constexpr long long inf = 1e18;

using ll = long long;
using namespace std;
using Apn = array< pair< int, int >, nax >;

struct Route
{
    ll su, mi, v;
    Route(ll su, ll mi, ll v) : su(su), mi(mi), v(v) {}
    Route() : Route(inf, inf, inf) {}
};

using Vr = vector< Route >;

int solve(const int n, const Apn& tab)
{
    Vr rou;
    
    ll su = 0, mi = 0;

    for (int i = 0; i < n; ++i)
    {
        auto& ev = tab[i];

        if (ev.st == 0)
        {
            su += ev.nd;
            mi = min(mi, su);
        }
        else
        {
            rou.emplace_back(su, mi, ev.nd);
            su = 0, mi = 0;
        }
    }

    rou.emplace_back(su, mi, inf);

    multiset< ll > S;

    su = 0;

    for (auto& r : rou)
    {
        while (su + r.mi < 0)
        {
            if (S.empty())
                exit((cout << -1 << '\n', 0));
            auto it = S.end(); --it;
            su += (*it);
            S.erase(it);
        }

        su += r.su;

        if (r.v != inf)
        {
            su -= r.v;
            S.insert(r.v);
        }
    }

    return S.size();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Apn tab;

    for (int i = 0; i < n; ++i)
        cin >> tab[i].st >> tab[i].nd;

    cout << solve(n, tab) << '\n';
}