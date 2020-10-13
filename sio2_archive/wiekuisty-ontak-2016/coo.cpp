#include <bits/stdc++.h>
#ifdef LOCAL
#define debug(...) {__VA_ARGS_}
#define asrt(...) { \
if (not (__VA_ARGS__)) { \
    cerr << __LINE__; cerr<<": "#__VA_ARGS__ << '\n'; \
    exit(1); \
} }
#else
#define asrt(...) 
#define debug(...) {}
#endif

constexpr int nax = 1e5, kax = 4, logg = 20;

using ll = long long;
using namespace std;
using Ain = array< int, nax + 1 >;
using Apn = array< pair< int, int >, nax + 1 >;
using Per = array< Ain, kax + 1 >;

Ain renum(const int n, const Ain& tab)
{
    Ain res;
    static Apn ilo;

    for (int i = 1; i <= n; ++i)
        ilo[i] = {tab[i], i};

    sort(begin(ilo) + 1, begin(ilo) + n + 1);

    for (int i = 1; i <= n; ++i)
        res[ilo[i].second] = i;

    return res;
}


ll inversions(const int n, const Ain& tab)
{
    static Ain bat, lic;

    //for (int i = 1; i <= n; ++i)
        //cerr << tab[i] << ' ';
    //cerr << '\n';

    for (int i = 1; i <= n; ++i)
        bat[i] = tab[i], lic[i] = 0;
    lic[0] = 0;

    ll res = 0;

    for (int i = 0; i < logg; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (bat[j] & 1) ++lic[bat[j]];
            else res += lic[bat[j] + 1];
            bat[j] >>= 1;
        }

        fill(begin(lic), begin(lic) + n + 1, 0);
    }

    //cerr << res << '\n';

    return res;
}

Ain compose(const int n, const Ain& a, const Ain& b)
{
    Ain res{};

    for (int i = 1; i <= n; ++i)
        res[a[i]] = b[i];

    return res;
}

ll solve(const int n, const int k, const Per& per2)
{
    Per per = per2;
    for (int i = 1; i <= k; ++i)
    {
        const auto& ren = renum(n, per[i]);
        for (int j = 1; j <= n; ++j)
            per[i][j] = ren[j];
    }

    ll sum = 0;

    if (k < 4)
        for (int i = 1; i <= k; ++i)
            for (int j = i + 1; j <= k; ++j)
                sum += inversions(n, compose(n, per[i], per[j]));
    else
        for (int i = 1; i <= 2; ++i)
            for (int j = 3; j <= k; ++j)
                sum += inversions(n, compose(n, per[i], per[j]));
    
    return (ll)n * (n - 1) / 2 - (k == 2? sum : (sum / 2));
}



void unit_tests()
{
    asrt(inversions(3, {0, 1, 2, 3}) == 0);
    asrt(inversions(5, {0, 5, 4, 3, 2, 1}) == 10);
    asrt(inversions(3, {0, 1, 3, 2}) == 1);
    //asrt(renum(5, {0, 132, 3, 123, -12, 4}) == Ain{0, 5, 2, 4, 1, 3});
    cerr << "Passed" << '\n';
}

ll bsolve(const int n, const int k, const Per& per)
{
    ll res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
        {
            int su = 0;
            for (int l = 1; l <= k; ++l)
                su += (per[l][i] < per[l][j]);
            res += ((su == k) or (su == 0));
        }

    return res;
}

void test(const int seed, const int n, const int k)
{
    srand(seed);
    Per per;
    int cnt = 0;
    while (true)
    {
        for (int i = 1; i <= k; ++i)
            for (int j = 1; j <= n; ++j)
                per[i][j] = j;

        //cerr << "Wi";

        for (int i = 1; i <= k; ++i)
            for (int j = 1; j <= n; ++j)
                swap(per[i][j], per[i][rand() % n + 1]);
        
        //cerr << "t";

        if (not (solve(n, k, per) == bsolve(n, k, per)))
        {
            cout << n << ' ' << k << '\n';
            for (int i = 1; i <= k; ++i)
            {
                for (int j = 1; j <= n; ++j)
                    cout << per[i][j] << ' ';
                cout << '\n';
            }
            cout << solve(n, k, per) << ' ' << bsolve(n, k, per) << '\n';
            exit(1);
        }

        //cerr << "am";

        cerr << cnt << '\n';
        ++cnt;
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifdef LOCAL
    unit_tests();
    if (argc > 1)
    {
        int seed = atoi(argv[1]);
        int n = atoi(argv[2]);
        int k = atoi(argv[3]);
        test(seed, n, k);
    }
    #endif

    int n, k;
    cin >> n >> k;

    Per per;

    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> per[i][j];

    int res = solve(n, k, per);

    asrt(res == bsolve(n, k, per));

    cout << solve(n, k, per) << '\n';
}