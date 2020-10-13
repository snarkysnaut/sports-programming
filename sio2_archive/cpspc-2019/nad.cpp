#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int nax = 1e7, maxm = 1e9, sko = 1e7, mod = 1e9 + 7;

using Ain = array< int, nax >;
using Aio = array< int, 1 >;

int pre[] = {1, 924724006, 582347126, 500419162, 881147799, 693776109, 435873621, 279027658, 727951124, 398578768, 678364145, 204828554, 345795998, 116118093, 359401113, 236930793, 856493327, 207383191, 617606889, 933753281, 26701748, 329394893, 360779992, 416008308, 187501984, 165706817, 328891607, 16385287, 117411011, 404196042, 765064133, 239669664, 761588352, 566114869, 673499119, 840260100, 352356536, 53839501, 178657924, 373444237, 227300165, 207172723, 444208499, 367531373, 297449176, 605324209, 729265513, 567907756, 125889461, 250743107, 666666670, 598576559, 632705086, 295855233, 185718228, 414607857, 737215408, 863388390, 182290465, 707552496, 881713600, 417895708, 490627919, 364521407, 775935292, 972492338, 473340273, 920880265, 530581, 696910290, 64037482, 649527920, 756691728, 283805222, 711255329, 825205499, 263679166, 341083474, 914727729, 919247968, 465317279, 960145703, 274813468, 393588827, 65909169, 521964827, 794328994, 484551338, 521297378, 54488990, 591837535, 255746228, 25827429, 177799409, 92011129, 469664591, 35708489, 197025781, 288851931, 254032854};

int n, m, a;
Ain pot, inv1, inv2; Aio fac;

int fpow(int v, int w)
{
    int r = 1;
    while (w)
    {
        if (w & 1)
            r = ((ll)r * v) % mod;
        v = ((ll)v * v) % mod;
        w >>= 1;
    }
    return r;
}

int inv(const int v)
{
    return fpow(v, mod - 2);
}

int sil(const int v)
{
    int d = (v / sko) * sko;
    int r = pre[d / sko];
    for (; d < v; ++d)
        r = ((ll)r * (d + 1)) % mod;
    return r;
}

template< size_t t >
void fill_pow(const int p, const int n, array< int, t >& tab)
{
    tab[0] = fpow(a - 1, p);
    for (int i = 1; i < n; ++i)
        tab[i] = ((ll)tab[i - 1] * (a - 1)) % mod;
}

template< size_t t >
void fill_inv(const int p, const int n, array< int, t >& tab)
{
    const int q = (p + n - 1);
    tab[n - 1] = inv(sil(q));
    //cout << ((ll)inv(sil(q)) * sil(q)) % mod << '\n';
    for (int i = n - 2; i >= 0; --i)
        tab[i] = ((ll)tab[i + 1] * (p + i + 1)) % mod;
}

template< size_t t >
void fill_fac(const int p, const int n, array< int, t >& tab)
{
    tab[0] = sil(p);
    for (int i = 1; i < n; ++i)
        tab[i] = ((ll)tab[i - 1] * (p + i)) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a;

    fill_pow(m - (n - 1), n, pot);
    fill_inv(0, n, inv1);
    fill_inv(m - n + 1, n, inv2);
    fill_fac(m, 1, fac);

    #ifdef LOCAL
    cout << fac[0] << '\n';
    for (int i = 0; i < n; ++i)
        cout << pot[i] << ' ';
    cout << '\n';
    for (int i = 0; i < n; ++i)
        cout << (((ll)inv1[i] * sil(i)) % mod) << ' ';
    cout << '\n';
    for (int i = 0; i < n; ++i)
        cout << (((ll)inv2[i] * sil(m - n + 1 + i)) % mod) << ' ';
    cout << '\n';
    #endif

    int acc = 0;
    for (int i = 0; i < n; ++i)
    {
        int d = ((ll)pot[n - 1 - i] * fac[0]) % mod;
        d = ((ll)d * inv1[i]) % mod;
        d = ((ll)d * inv2[n - 1 - i]) % mod;
        acc += d;
        if (acc >= mod) acc -= mod;
    }

    #ifdef LOCAL
    cout << acc << ' ' << fpow(a, m) << '\n';
    #endif

    int res = fpow(a, m) - acc;
    if (res < 0) res += mod;

    cout << res << '\n';
}