/*{{{*/
#include <bits/stdc++.h>
#ifdef LOCAL
int c_ = 0;
#define cout (c_?cerr:cout)
#define debug(...) \
{if(!c_++)cerr<<"\033[96;1m"; \
__VA_ARGS__; \
if(!--c_)cerr<<"\033[0m";}
#else
#define debug(...) {}
#endif
#define assrt(...) debug(\
if (not (__VA_ARGS__))\
    exit((cerr << __LINE__ << ": " << #__VA_ARGS__ << '\n', 0));)
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long;
template < typename t > using V = vector< t >;
void print() {cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{ while (a != b) cout << (*a++) << ' '; cout << '\n';}
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__ << ": "; print_range(__VA_ARGS__))
/*}}}*/

constexpr int nax = 2e5, qax = 2e5, logg = 18;

struct Info
{
    pair< int, int > hs;
    int id;
};


int n, q, kmr[nax][logg];
Info tab[nax];
int arr[nax + 1];
string s;
V< int > ilo[nax + 1][logg];

inline bool operator<(const Info& mn, const Info& wc)
{
    return mn.hs < wc.hs;
}

void fkmr()
{
    string q = s;
    sort(all(q));
    q.resize(unique(all(q)) - begin(q));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < q.size(); ++j)
            if (s[i] == q[j])
                kmr[i][0] = j + 1;

    for (int i = 1; i < logg; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tab[j].id = j;
            tab[j].hs.st = kmr[j][i - 1];
            tab[j].hs.nd = (j + (1 << (i - 1)) >= n? 0 : kmr[j + (1 << (i - 1))][i - 1]);

        }
        sort(begin(tab), begin(tab) + n);

        int cnt = 1;
        for (int j = 0; j < n; ++j)
        {
            if (j > 0 and tab[j].hs != tab[j - 1].hs)
                ++cnt;
            kmr[tab[j].id][i] = cnt;
        }
    }
}

bool check(const int l, const int r, const int e)
{
    if (r + e - 1 >= n or l + e - 1 >= n) return false;
    int a = arr[e];
    dump(l, r, a);
    return kmr[l][a] == kmr[r][a] and kmr[l + e - (1 << a)][a] == kmr[r + e - (1 << a)][a];
}

bool process(const int l, const int r)
{
    {
        int d = 0;
        int p = l + 1;
        while ((1 << d) <= r - p + 1)
        {
            int v = kmr[l][d];
            dump(v);
            dump(l, r, d, p);
            dump_range(all(ilo[v][d]));
            int a = *lower_bound(all(ilo[v][d]), p);
            if ((a + (1 << d) - 1 <= r) and check(l, a, a - l)) return true;
            ++d;
            p = (l + (1 << d));
        }
    }
    {
        int d = 0;
        while ((1 << d) <= (r - l + 1) / 2)
        {
            int v = kmr[r - (1 << d) + 1][d];
            int a = *(upper_bound(all(ilo[v][d]), r - (1 << d) - (1 << d) + 1) - 1);
            int b = a + (1 << d);
            int e = r - b + 1;
            int c = b - 1 - e + 1;
            if (c < l or b < l)
            {
                ++d;
                continue;
            }
            if (check(c, b, e)) return true;
            ++d;
        }
    }
    return false;
}

bool eval(const int l, const int r)
{
    int d = 0;
    while ((1 << d) <= (r - l + 1) / 2)
    {
        dump(l, r, d);
        int v = kmr[l][d];
        int lo = lower_bound(all(ilo[v][d]), max(r - (1 << (d + 1)) + 1 + 1, (l + r) / 2 + 1)) - begin(ilo[v][d]);
        int hi = upper_bound(all(ilo[v][d]), r - (1 << d) + 1) - begin(ilo[v][d]) - 1;

        for (int i = lo; i <= hi; ++i)
        {
            int pz = ilo[v][d][i];
            dump(l, pz, r - pz + 1);
            if (check(l, pz, r - pz + 1))
                return true;
        }

        ++d;
    }
    return false;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> s;

    fkmr();

    for (int i = 0; i < logg; ++i)  
        if ((1 << i) <= n)
            arr[1 << i] = i;

    for (int i = 3; i <= n; ++i)
        if (not arr[i]) arr[i] = arr[i - 1];

    for (int i = 0; i < logg; ++i)
        for (int j = 1; j <= n; ++j)
            ilo[j][i].push_back(-1);

    for (int i = 0; i < logg; ++i)
        for (int j = 0; j < n; ++j)
            ilo[kmr[j][i]][i].push_back(j);

    for (int i = 0; i < logg; ++i)
        for (int j = 1; j <= n; ++j)
            ilo[j][i].push_back(n);

    for (int i = 0; i < q; ++i)
    {
        int l, r; cin >> l >> r;
        --l, --r;
        if (process(l, r))
        {
            print("YES"); continue;
        }
        print(eval(l, r)? "YES" : "NO");
    }
}