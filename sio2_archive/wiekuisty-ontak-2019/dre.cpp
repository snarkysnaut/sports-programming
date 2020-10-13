#include <bits/stdc++.h>
#include "drelib.h"
#define st first
#define nd second
using namespace std;

constexpr int nax = 100;

namespace
{
    int n, r, val[nax + 1], ojc[nax + 1];
    vector< int > lef[nax + 1];
    vector< pair< int, int > > tab;
    pair< int, int > ilo[nax + 0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    n = get_n();

    tab.resize(n);
    for (int i = 1; i <= n; ++i)
        tab[i - 1] = {i, 0};

    for (int i = 0; i < n; ++i)
    {
        int v = i + 1; if (v == n) v = 0;
        tab[i].nd = min_max_on_path(tab[i].st, tab[v].st).nd;
    }

    while (tab.size() > 1)
    {
        //cerr << tab.size() << '\n';
        //for (int i = 0; i < tab.size(); ++i)
            //cerr << tab[i].st << ' ' << tab[i].nd << '\n';
        int ma = 0;
        for (int i = 0; i < tab.size(); ++i)
            ma = max(ma, tab[i].nd);
        //cerr << "ma: " << ma << '\n';
        bool con = true;
        for (int i = 0; con and i < tab.size(); ++i)
        {
            int v = i + 1; if (v == tab.size()) v = 0;
            int p = tab[i].st;
            if (tab[i].nd == ma and tab[v].nd == ma)
            {
                val[tab[v].st] = tab[v].nd;
                if (tab.size() > 2)
                {
                    //cerr << "v: " << tab[v].st << '\n';
                    auto it = tab.erase(begin(tab) + v);
                    if (it == tab.end()) it = tab.begin();
                    auto it2 = tab.begin();
                    if (it == tab.begin())
                        it2 = prev(tab.end());
                    else
                        it2 = prev(it);
                    //cerr << "pair: "  << (*it).st << ' ' << (*it2).st << '\n';
                    (*it2).nd = min_max_on_path((*it).st, (*it2).st).nd;
                    con = false;
                }
                else tab.erase(begin(tab) + v), con = false;
            }
        }
        assert(not con);
    }

    r = tab[0].st;

    cerr << "root: " << r << '\n';

    for (int i = 1; i <= n; ++i)
        cerr << val[i] << ' ';

    cerr << '\n';

    for (int i = 1; i <= n; ++i)
        ilo[i - 1] = {val[i], i};

    sort(begin(ilo), begin(ilo) + n);

    auto node = [](int val){return (*lower_bound(begin(ilo), begin(ilo) + n, make_pair(val, 0))).nd;};

    auto recon = [&](int a, int b)
    {
        while (a != b)
        {
            int s = node(min_max_on_path(a, b).st);
            ojc[s] = a;
            a = s;
        }
        int v = b;
        while (true)
        {
            lef[v].push_back(b);
            if (v == r) break;
            v = ojc[v];
        }
    };

    recon(r, ilo[n - 1].nd);
    
    for (int i = n - 2; i >= 0; --i)
    {
        int w, v;
        tie(w, v) = ilo[i];
        if (ojc[v] or v == r) continue;
        int a = r;
        while (true)
        {
            int l = lef[a][rand() % lef[a].size()];
            int s = node(min_max_on_path(v, l).st);
            if (not ojc[s])
            {
                int b = l;
                while (ojc[b] != r and val[ojc[b]] > val[s])
                    b = ojc[b];
                b = ojc[b];
                ojc[s] = b;
                a = s;
                break;
            }
            else 
            {
                if (ojc[s] == a)
                {
                    int q = node(min_max_on_path(a, v).st);
                    if (not ojc[q])
                    {
                        ojc[q] = a;
                        a = q;
                        break;
                    }
                    else a = q;
                }
                else a = ojc[s];
            }
        }
        recon(a, v);
    }

    for (int v = 1; v <= n; ++v)
        if (v != r and ojc[v])
            answer_edge(v, ojc[v], val[v]);
}