#include "gralib.hpp"
#define nd second
#define st first
#include <vector>
#include <algorithm>
constexpr int nax = 25e4, tax = 100, inf = 1e9, kax = nax;
using namespace std;
using ld = double;

ld dp[nax + 1]; int piv[nax + 1];
vector< pair< ld, int > > ilo[nax + 1];

void preprocess(const int n, const int k, const int m)
{
    for (int i = 1; i <= k; ++i)
        for (int j = 0; j <= n; j += i)
            ilo[j].push_back({0, i});

    dp[n] = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        dp[i] = inf;

        for (auto& p : ilo[i])
            p.st = (p.nd + i <= n? dp[p.nd + i] : inf);

        sort(begin(ilo[i]), end(ilo[i]));

        ld sum = 0;

        for (int j = 0; j < ilo[i].size(); ++j)
        {
            if (ilo[i][j].st == inf)
                break;
            sum += ilo[i][j].st;
            ld rs = (sum) / (j + 1) + (ld)(k) / (j + 1);
            if (rs < dp[i])
                dp[i] = rs, piv[i] = j;
        }
    }

    //for (int i = 0; i <= n; ++i)
        //cerr << dp[i] << ' ';
    //cerr << '\n';

    //cerr << dp[0] << '\n';
}

bool tab[kax + 1];

void graj(const int n, const int k, const int m)
{
    int v = 0;
    while (v < n)
    {
        //cerr << v << '\n';
        for (int i = 0; i <= piv[v]; ++i)   
            tab[ilo[v][i].nd] = true;
        
        int q = -1;
        do q = nastepna(); while (tab[q] == false);

        zwieksz();

        for (int i = 0; i <= piv[v]; ++i)   
            tab[ilo[v][i].nd] = false;

        v += q;
    }
    koniec();
}

int main() {
//    #ifdef LOCAL
//        int n; cin >> n;
//        int k; cin >> k;
//        int m; cin >> m;
//    #else
        int n = dajN();
        int k = dajK();
        int m = dajM();
    //#endif

    preprocess(n, k, m);
    for (int i = 0; i < tax; ++i)
        graj(n, k, m);
}
