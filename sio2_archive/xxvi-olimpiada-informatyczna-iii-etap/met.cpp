#include <bits/stdc++.h>
constexpr int nax = 3e6;
using namespace std;

int n, k, rs[nax + 1], zl[nax];
vector< int > gr[nax + 1];

pair< int, int > dfs(const int v, const int oj, const bool fl = false)
{
    pair< int, int > res = {0, v};

    for (int s : gr[v])
        if (s != oj)
        {
            auto q = dfs(s, v, fl);
            ++q.first; 
            res = max(res, q);
        }

    if (fl) ++zl[res.first], rs[v] = res.first;

    return res;
}

void getint(int* a)
{
    char c = getc_unlocked(stdin);
    while (not ('0' <= c and c <= '9'))
        c = getc_unlocked(stdin);
    (*a) = 0;
    while ('0' <= c and c <= '9')
    {
        (*a) *= 10;
        (*a) += (c - '0');
        c = getc_unlocked(stdin);
    }
}

void putint(int v)
{
    static char tb[20];
    int k = 0;

    if (v == 0)
    {
        putc_unlocked('0', stdout);
        return;
    }

    while (v)
    {
        tb[k++] = v % 10;
        v /= 10;
    }

    for (int i = k - 1; i >= 0; --i)
        putc_unlocked((tb[i] + '0'), stdout);
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    

    getint(&n); getint(&k);
    //cin >> n >> k;

    for (int i = 0; i < n - 1; ++i)
    {
        int p, q; 
        getint(&p); getint(&q);
        //cin >> p >> q;
        gr[p].push_back(q);
        gr[q].push_back(p);
    }

    int dl, v;
    tie(dl, v) = dfs(1, 1);

    dfs(v, v, true);

    for (int i = 0; i < n; ++i)
        if (zl[i] + 1 <= k)
        {
            putint(i); 
            putc_unlocked(' ', stdout);
            putint(zl[i] + 1);
            putc_unlocked('\n', stdout);
            //cout << i << ' ' << ilo[i].size() + 1 << '\n';
            putint(v);
            putc_unlocked(' ', stdout);
            //cout << v << ' ';
            for (int v = 1; v <= n; ++v)
                if (rs[v] == i)
                {
                    putint(v); 
                    putc_unlocked(' ', stdout);
                    //cout << v << ' ';
                }
            putc_unlocked('\n', stdout);
            //cout << '\n';
            return 0;
        }
}
