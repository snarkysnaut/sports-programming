#include <bits/stdc++.h>

constexpr int nax = 3e5;

using namespace std;
using ll = long long;
using Seq = array< ll, nax + 1 >;
using Map = map< ll, ll >;
using Deq = deque< pair< ll, int > >;

ll gcd(ll a, ll b)
{
    return (b == 0? a : gcd(b, a % b));
}

Map process(const int n, const Seq& tab)
{
    Map dic;
    Deq deq;
    
    for (int i = 1; i <= n; ++i)
    {
        Deq nde; ll v = tab[i];

        deq.push_back({v, i});
        nde.push_back({1ll, 0});

        for (auto p : deq)
        {
            p.first = gcd(p.first, v);
            if (nde.back().first == p.first)
                nde.back().second = p.second;
            else
                nde.push_back(p);
        }

        int r = 0;
        for (auto p : nde)
        {
            int l = p.second - r;
            dic[p.first] += l;
            r = p.second;
        }

        deq = move(nde);
    }

    return move(dic);
}

Seq answer(const int q, const Seq& evs, Map& dic)
{
    ll x = 0;
    Seq ans;

    for (int i = 1; i <= q; ++i)
    {
        ll v = evs[i];
        v xor_eq x;
        x = dic[v];
        ans[i] = x;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    Seq tab;

    for (int i = 1; i <= n; ++i)
        cin >> tab[i];

    auto dic = process(n, tab);

    //for (auto& p : dic)
        //cout << '(' << p.first << ", " << p.second << ')' << '\n';

    int q; 
    cin >> q;

    Seq evs;

    for (int i = 1; i <= q; ++i)
        cin >> evs[i];
    
    auto ans = answer(q, evs, dic);

    for (int i = 1; i <= q; ++i)
        cout << ans[i] << '\n';
}