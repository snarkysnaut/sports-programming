#include <bits/stdc++.h>
#ifdef DBG
#define dbg(...) {cerr<<"\033[96;1m";ostream& cout=cerr;__VA_ARGS__;\
(void)(cout);cerr<<"\033[0m";}
#else
#define dbg(...) {}
#endif
#define nd second
#define st first
#define flg(), __LINE__, __PRETTY_FUNCTION__
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define dmp(...) print(cout, #__VA_ARGS__, __VA_ARGS__)
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template<typename... t>using V = vector< t... >;
template<typename t> void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... v> void print(ostream& os, const t& a,
v&&... b){os<<a<<' ';print(os, b...);}

constexpr int mod = 1e9 + 7, p = 29, maxn = 5e5;

int n;
string s;
bool ok[maxn + 1];
int pref[maxn], pot[maxn + 1];

inline int hasz(int v, int dl)
{
    int r = v + dl - 1;
    int l = v - 1;
    int us = (l < 0? 0 : (((ll)pref[l] * pot[dl]) % mod));
    return pref[r] - us < 0? pref[r] - us + mod : pref[r] - us;
}

inline bool foo(int a, int b, int d)
{
    int lo = 0;
    ddmp(a, b, d);
    for (int q = d; q >= 1; q >>= 1)
        while (lo + q <= d and hasz(a, lo + q) == hasz(b, lo + q))
                lo += q;

    a += lo + 1;
    b += lo + 1;
    d -= lo + 1;

    return hasz(a, d) == hasz(b, d);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = s.size();

    pot[0] = 1;

    for (int i = 1; i <= n; ++i)
        pot[i] = ((ll)pot[i - 1] * p) % mod;

    for (int i = 0; i < n; ++i)
        pref[i] = ((ll)(i == 0? 0 : pref[i - 1]) * p + (s[i] - 'a' + 1)) % mod;

    for (int i = 1; i <= n / 2; ++i)
    {
        bool w = true;
        bool fl = false;
        int h = hasz(i, i);

        for (int k = 0; k < n; k += i)
        {
            if (k + i - 1 < n)
            {
                if (h != hasz(k, i))
                {
                    if (fl)
                    {
                        w = false; break;
                    }

                    if (foo(i, k, i))
                        fl = true;
                    else
                    {
                        w = false; break;
                    }
                }
            }
            else
            {
                int dl = n - k;
                ddmp(k, dl);
                if (hasz(i, dl) != hasz(k, dl))
                {
                    if (fl)
                    {
                        w = false; break;
                    }

                    if (foo(i, k, dl))
                        fl = true;
                    else
                    {
                        w = false; break;
                    }
                }

            }
        }

        if (w)
            ok[i] = true;
        
    }

    for (int i = 1; i < n; ++i)
    {
        bool w = true;
        bool fl = false;
        int h = hasz(0, i);

        for (int k = i; k < n; k += i)
        {
            if (k + i - 1 < n)
            {
                if (h != hasz(k, i))
                {
                    if (fl)
                    {
                        w = false; break;
                    }

                    if (foo(0, k, i))
                        fl = true;
                    else
                    {
                        w = false; break;
                    }
                }
            }
            else
            {
                int dl = n - k;
                ddmp(k, dl);
                if (hasz(0, dl) != hasz(k, dl))
                {
                    if (fl)
                    {
                        w = false; break;
                    }

                    if (foo(0, k, dl))
                        fl = true;
                    else
                    {
                        w = false; break;
                    }
                }

            }
        }

        if (w)
            ok[i] = true;
    }

    int s = 0;
    for (int i = 1; i < n; ++i)
        s += ok[i];

    prt(s);
    for (int i = 1; i < n; ++i)
        if (ok[i]) cout << i << ' ';
    cout << '\n';
}