#include <bits/stdc++.h>

constexpr int siz = 15e6, mod = 1e9 + 7, inv = 5e8 + 4;

using ll = long long;
using namespace std;

struct Sum
{
    Sum()
    {
        init();
    }

    map< ll, int > M;
    int pre[siz + 1];

    void init()
    {
        for (int i = 1; i <= siz; ++i)
            pre[i] = i;

        for (int i = 2; i <= siz; ++i)
            if (pre[i] == i)
                for (int j = i; j <= siz; j += i)
                    pre[j] = pre[j] - (pre[j] / i);

        for (int i = 2; i <= siz; ++i)
            pre[i] = (pre[i] + pre[i - 1]) % mod;

    }

    int operator()(ll v)
    {
        if (v <= siz) return pre[v];
        auto it = M.find(v); if (it != M.end()) return (*it).second;
        
        int res = 1;
        res = ((ll)res * (v % mod)) % mod;
        res = ((ll)res * ((v + 1) % mod)) % mod;
        res = ((ll)res * inv) % mod;

        //cout << v << ' ' << res << '\n';

        ll r = 1;
        for (ll i = 1; i * i <= v; ++i)
        {
            ll lo = (v / (i + 1)) + 1;
            ll hi = (v / (i));
            int cnt = (hi - lo + 1) % mod;
            int odj = ((ll)cnt * operator()(i)) % mod;
            res -= odj;
            if (res < 0) res += mod;
            r = i;
        }

        for (ll i = 2; ; ++i) 
        {
            ll a = v / i;
            if (a <= r)
                break;
            res -= operator()(a);
            if (res < 0) res += mod;
        }

        return M[v] = res;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    Sum sum;
    cout << sum(n) << '\n';
}