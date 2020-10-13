#include <bits/stdc++.h>
using namespace std;

constexpr int nax = 1e6;

using Ain = array< int, nax + 1 >;

int n, tab[nax + 1], bat[nax + 1];
string s;

vector< int > neg(const int k)
{
    bool sta[nax + 1];
    fill_n(sta + 1, n, true);

    vector< int > res(n + 1, n + 1);

    int pt = 0, cnt = 1;
    res[0] = pt;

    for (int i = 1; i <= n; ++i)
    {
        sta[bat[i]] = false;
        if (bat[i] > pt)
            ++cnt;
        while (cnt > k + 1)
            ++pt, cnt -= (sta[pt] == 0);
        res[i] = pt;
    }

    return res;
}

vector< int > gen(const int k)
{
    bool sta[nax + 1];
    fill_n(sta + 1, n, false);

    vector< int > res(n + 1);

    int pt = n + 1, cnt = 1;
    res[n] = pt;
    for (int i = n; i >= 1; --i)
    {
        sta[bat[i]] = true;
        if (bat[i] < pt)
            ++cnt;
        while (cnt > k + 1)
            --pt, cnt -= (sta[pt] == 1);
        res[i - 1] = pt;
    }

    return move(res);
}

bool spr(const int k)
{
    int f = 0, b = 0;
    for (int i = 0; i < k; ++i)
        if (s[i] == 'F') ++f;
        else ++b;

    vector< int > fe = gen(f);
    vector< int > be = neg(b);

    for (int i = 0; i <= n; ++i)
        if (fe[i] < be[i])
            return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> tab[i], bat[tab[i]] = i;

    cin >> s;

    int lo = 0, hi = s.size();
    while (lo < hi)
    {
        int mi = (lo + hi) / 2;
        if (spr(mi))
            hi = mi;
        else
            lo = mi + 1;
    }

    cout << lo << '\n';
}