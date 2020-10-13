#include <bits/stdc++.h>
#define st first
#define nd second
using namespace std;
using ll = long long;

constexpr int nax = 5e5, qax = 5e5, alf = 4, mod = 1e9 + 7;

int n, q, ost[4], ans[qax], dp[nax + 1];
string s;
pair< int, int > que[qax];
vector< int > gr[nax + 1];
vector< int > rg[nax + 1];

void div_and_con(const int lo, const int hi, vector< int >& ilo)
{
    if (lo == hi)
        return;

    int mi = (lo + hi) / 2;

    for (int p : gr[mi])
    {
        if (p > hi) continue;
        for (int i = mi; i >= lo; --i)
        {
            dp[i] = 0;
            for (int s : gr[i])
            {
                if (s > mi) dp[i] += (s == p);
                else dp[i] += dp[s];
                if (dp[i] >= mod) dp[i] -= mod;
            }
        }

        for (int i = p; i <= hi; ++i)
        {
            dp[i] = (i == p);
            for (int s : rg[i])
            {
                if (s >= p) dp[i] += dp[s];
                if (dp[i] >= mod) dp[i] -= mod;
            }
        }

        for (int i = p + 1; i <= hi; ++i)
        {
            dp[i] += dp[i - 1];
            if (dp[i] >= mod) dp[i] -= mod;
        }

        for (int r : ilo)
            if (que[r].st <= mi and que[r].nd >= p)
            {
                ans[r] += ((ll)dp[que[r].st] * dp[que[r].nd]) % mod;
                if (ans[r] >= mod) ans[r] -= mod;
            }
    }

    vector< int > tab[2];
    for (int r : ilo)
    {
        if (que[r].st <= mi)
            que[r].nd = min(que[r].nd, mi);
        tab[que[r].st > mi].push_back(r);
    }

    ilo.clear(); 

    div_and_con(lo, mi, tab[0]);
    div_and_con(mi + 1, hi, tab[1]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> s;

    for (int i = 0; i < alf; ++i)
        ost[i] = n + 1;

    for (int i = n; i >= 0; --i)
    {
        for (int j = 0; j < alf; ++j)
        {
            gr[i].push_back(ost[j]);
            if (ost[j] <= n)
                rg[ost[j]].push_back(i);
        }

        if (i > 0)
            switch (s[i - 1])
            {
                case 'A':
                    ost[0] = i;
                    break;
                case 'C':
                    ost[1] = i;
                    break;
                case 'G':
                    ost[2] = i;
                    break;
                case 'T':
                    ost[3] = i;
                    break;
            }
    }

    for (int i = 0; i < q; ++i)
        cin >> que[i].st >> que[i].nd, --que[i].st;

    vector< int > ilo(q);
    iota(begin(ilo), end(ilo), 0);

    div_and_con(0, n, ilo);

    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}