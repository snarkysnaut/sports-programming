#include <iostream>
constexpr int sax = 4e5;
using namespace std;

struct State
{
    int n, m, p, k;
};

int n, m, a, b, k, pt = 0;
State tab[sax];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a >> b >> k;

    tab[0].n = n, tab[0].m = m, tab[0].p = a - 1, tab[0].k = k;

    int res = 0;

    while (true)
    {
        auto& e = tab[pt];
        auto& ne = tab[pt + 1];

        //cerr << e.n << ' ' << e.m << ' ' << e.p << ' ' << e.k << '\n';

        if (e.p < e.n) // jesli pierwszy ktory padnie to samiec
        {
            if (a >= (e.n + e.m)) // jesli kazdy zaspiewa
            {
                if (e.k == 1)
                {
                    res = e.p; break;
                }

                int ind = (a + e.p - 1) % (e.n + e.m - 1);

                ne.n = e.n - 1;
                ne.m = e.m;
                ne.k = e.k - 1;
                ne.p = ind;
                ++pt;
            }
            else
            {
                int odl = (e.n - 1) - e.p; // ile trzeba skoczyc do ostatniego
                int cnt = odl / a; // ile skokow wykonamy - 1
                if (e.k <= 1 + cnt) // jesli k wieksze rowne od tego ile zginie w tym ruchu
                {
                    res = (e.k - 1) * a + e.p; //indeks tego ktory zginie ost
                    break; // przejdz do odtwarzania wyniku
                }

                int ind = (((long long)(cnt + 1) * a + e.p - (cnt + 1)) % (e.n + e.m - (cnt + 1)));
                ne.n = e.n - (1 + cnt);
                ne.m = e.m;
                ne.p = ind;
                ne.k = e.k - (1 + cnt);
                ++pt;
            }
        }
        else
        {
            if (b >= (e.n + e.m)) // jesli kazdy zaspiewa
            {
                if (e.k == 1)
                {
                    res = e.p; break;
                }

                int ind = (b + e.p - 1) % (e.n + e.m - 1);

                ne.n = e.n;
                ne.m = e.m - 1;
                ne.k = e.k - 1;
                ne.p = ind;
                ++pt;
            }
            else
            {
                int odl = (e.n + e.m - 1) - e.p;
                int cnt = odl / b;
                if (e.k <= 1 + cnt)
                {
                    res = (e.k - 1) * b + e.p;
                    break;
                }

                int ind = (((long long)(cnt + 1) * b + e.p - (cnt + 1)) % (e.n + e.m - (cnt + 1)));

                ne.n = e.n;
                ne.m = e.m - (cnt + 1);
                ne.p = ind;
                ne.k = e.k - (1 + cnt);
                ++pt;
            }
        }
    }

    //cerr << res << '\n';

    for (int i = pt - 1; i >= 0; --i)
    {
        auto& e = tab[i];
        int nres = -1;

        //cerr << e.n << ' ' << e.m << ' ' << e.p << ' ' << e.k << ' ' << res << '\n';

        if (e.p < e.n) // jesli pierwszy ktory padnie to samiec
        {
            if (a >= (e.n + e.m))
            {
                nres = (res >= e.p? res + 1 : res);
            }
            else
            {
                int odl = (e.n - 1) - e.p; // ile trzeba skoczyc do ostatniego
                int cnt = odl / a; // ile skokow wykonamy - 1

                long long lo = 0, hi = (e.n + e.m - 1);

                while (lo < hi)
                {
                    int mi = (lo + hi) / 2;

                    int nid = -1;
                    if (mi < e.p)
                        nid = mi;
                    else
                        nid = mi - min((mi - e.p) / a + 1, cnt + 1);

                    if (nid >= res)
                        hi = mi;
                    else
                        lo = mi + 1;
                }
                nres = lo;
            }
        }
        else
        {
            if (b >= (e.n + e.m))
            {
                nres = (res >= e.p? res + 1 : res);
            }
            else
            {
                int odl = (e.n + e.m - 1) - e.p;
                int cnt = odl / b;

                long long lo = 0, hi = (e.n + e.m - 1);

                while (lo < hi)
                {
                    int mi = (lo + hi) / 2;

                    int nid = -1;
                    if (mi < e.p)
                        nid = mi;
                    else
                        nid = mi - min((mi - e.p) / b + 1, cnt + 1);

                    if (nid >= res)
                        hi = mi;
                    else
                        lo = mi + 1;
                }

                nres = lo;
            }
        }

        res = nres;
    }


    cout << res + 1 << '\n';
}
