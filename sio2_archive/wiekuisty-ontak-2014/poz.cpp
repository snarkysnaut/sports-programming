#include <bits/stdc++.h>
constexpr int nax = 1234, mod = 1e7;
using ll = long long;
using namespace std;

int n, ilo[nax]; ll pam[nax + 1];
vector< ll > tab;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> ilo[i];

    srand(((ll)n * ilo[0]) % mod);
    
    for (int i = 1; i <= nax; ++i)
        pam[i] = rand() % mod;
        
    for (int i = 1; i <= nax; ++i)
        pam[i] *= pam[i];

    for (int i = 0; i < n; ++i)
    {
        ll h = 0;
        bool byl[nax + 1];
        for (int i = 1; i <= nax; ++i)
            byl[i] = false;
        for (int j = i; j < n; ++j)
        {
            if (not byl[ilo[j]])
                h += pam[ilo[j]];
            byl[ilo[j]] = true;
            tab.push_back(h);
        }
    }

    sort(begin(tab), end(tab));
    tab.resize(unique(begin(tab), end(tab)) - begin(tab));

    cout << tab.size() << '\n';
}