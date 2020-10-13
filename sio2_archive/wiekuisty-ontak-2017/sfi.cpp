#include <bits/stdc++.h>
using namespace std;
using byte = uint8_t;

constexpr int nax = 1e5, maxm = 3e5, kax = 200;

using Big = vector< byte >;

Big operator+(const Big& a, const Big& b)
{
    Big res;
    byte c = 0;
    for (int i = 0; i < max(b.size(), a.size()); ++i)
    {
        if (i < a.size()) c += a[i];
        if (i < b.size()) c += b[i];
        res.push_back(c % 10); 
        c /= 10;
    }
    if (c) res.push_back(c);
    return res;
}

Big to_big(int a)
{
    Big res; 
    while (a > 0)
    {
        res.push_back(a % 10); a /= 10;
    }
    return res;
}

ostream& operator<<(ostream& os, const Big& a)
{
    if (a.empty()) os << 0;
    for (int i = (int)(a.size()) - 1; i >= 0; --i)
        os << (int)a[i];
    return os;
}

int n, m, s, t, k, fu[kax + 1][nax + 1], val[nax + 1];
bool ena[kax + 1][nax + 1], res[kax + 1];
Big pot[kax];
vector< int > tab[kax];
vector< int > gr[nax + 1];

int find(const int f, const int v)
{
    return fu[f][v] < 0? v : fu[f][v] = find(f, fu[f][v]);
}

bool join(const int f, int p, int q)
{
    //cerr << f << ' ' << p << ' ' << q << '\n';
    p = find(f, p); q = find(f, q);
    if (p == q) return false;
    if (fu[f][p] > fu[f][q]) 
        swap(p, q);
    fu[f][p] += fu[f][q];
    fu[f][q] = p;
    return true;
}

void drop(const int q)
{
    //cerr << q << '\n';
    vector< pair< int, int > > ilo[kax + 1];

    for (int i = 0; i < q; ++i)
        for (int v : tab[q - 1])
            ena[i][v] = true;

    for (int v : tab[q - 1])
        for (int s : gr[v])
        {
            int a = 0;
            if (not ena[0][v]) a = max(a, val[v] + 1);
            if (not ena[0][s]) a = max(a, val[s] + 1);
            //cerr << a << ' ' << s << ' ' << v << '\n';
            ilo[a].push_back({s, v});
        }

    for (int i = 0; i < q; ++i)
    {
        for (auto& p : ilo[i])
            if (join(i, p.first, p.second))
                ilo[i + 1].push_back(p);
        ilo[i].clear();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t >> k;
    
    for (int i = 1; i <= n; ++i)
    {
        int v; cin >> v;
        tab[v].push_back(i);
        val[i] = v;
    }

    for (int i = 0; i < m; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].push_back(q);
        gr[q].push_back(p);
    }

    for (int i = 1; i <= n; ++i)
        fu[0][i] = -1;

    for (int i = 1; i <= k; ++i)
    {
        for (int j = 1; j <= n; ++j)
            fu[i][j] = fu[i - 1][j], ena[i][j] = ena[i - 1][j];

        for (int v : tab[i - 1])
        {
            ena[i][v] = true;
            for (int s : gr[v])
                if (ena[i][v] and ena[i][s])
                    join(i, v, s);
        }
    }

    //cerr << 'j' << '\n';
    
    while (find(0, s) != find(0, t))
        for (int i = 1; i <= k; ++i)
            if (find(i, s) == find(i, t))
            {
                res[i] = true;
                drop(i);
                break;
            }

    //cerr << 'j' << '\n';

    pot[0] = to_big(1);
    for (int i = 1; i < k; ++i)
        pot[i] = pot[i - 1] + pot[i - 1];

    Big r;

    for (int i = 1; i <= k; ++i)
        if (res[i])
            r = r + pot[i - 1];

    cout << r << '\n';
}