#pragma GCC optimize("O3")
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
if (not (__VA_ARGS__)) \
    exit((cerr << __LINE__ << ": " << #__VA_ARGS__ << '\n', 0));\
)
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
using namespace std; using ll = long long; using ld = long double;
template < typename t > using V = vector< t >;
template < typename t, size_t s > using A = array< t, s >;
void print() {cout << '\n';}
template< typename t, typename... v >
void print(const t& a, const v&... b)
{cout << a << (sizeof...(b)?" ":""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{ while (a != b) cout << (*a++) << ' '; cout << '\n';}
#define dump(...) debug(print(#__VA_ARGS__,'=',__VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__ << ": "; print_range(__VA_ARGS__))
/*}}}*/

/*
 * 0. Odjac jeden od doslownie wszystkiego na wejsciu
 * 1. Policzyc rozklad na czynniki pierwsze wszystkich zapytan (przenumerowac wystepujace w nich liczby pierwsze
 * 2. Policzyc rozklad na czynniki pierwsze liczby c (proba)
 * 3. dla kazdej ilosci jednego z pary ustalic ile ma byc drugiego
 * 4. Jesli dla jakies ilosci wyjdzie zgodnie to trzeba ograniczyc liczbe mnozen (do 2 * log z ilosci) i wypisac
*/

using ll = long long;
#define int ll

constexpr int qax = 5e3, sqr = 1e4, inf = 1e9;

int q, l;
string c;
bool com[sqr + 1];
V< int > pri, cnt, tnc[2], irp;
pair< int, int > que[qax];
V< pair< int, int > > tab[qax * 2], ilo;

void dec(string& c)
{
    for (int i = 0; i < c.size(); ++i)
        if (c[c.size() - 1 - i] == '0')
            c[c.size() - 1 - i] = '9';
        else
        {
            --c[c.size() - 1 - i];
            break;
        }
    
    if (c[0] == '0')
        c = c.substr(1);
}

bool div(const int d)
{
    string r;

    dump(d);

    int v = 0;
    for (int i = 0; i < c.size(); ++i)
    {
        v = v * 10 + (c[i] - '0');
        int a = v / d;
        if (a or not r.empty())
            r.push_back(a + '0');
        v = v % d;
    }

    if (not v) 
    {
        c = move(r);
        return true;
    }
    
    return false;
}

void fpow(int v, int w, V< pair< int, int > >& ans)
{
    dump(v, w);
    int a = v;
    int r = v;
    --w;
    while (w)
    {
        //dump(w);
        if (w & 1)
        {
            ans.push_back({a, r});
            r = ans.size() + 1;
        }
        w >>= 1;
        if (w)
        {
            ans.push_back({a, a});
            a = ans.size() + 1;
        }
    }
}

void answer(int p, int q)
{
    dump(p, q);
    V< pair< int, int > > ans;

    if (p == 0)
    {
        fpow(1, q, ans);
    }   
    else if (q == 0)
    {
        fpow(0, p, ans);
    }
    else
    {
        fpow(0, p, ans);
        int a = (p == 1? 0 : ans.size() + 1);
        fpow(1, q, ans);
        int b = (q == 1? 1 : ans.size() + 1);
        ans.push_back({a, b});
    }

    print(ans.size());
    for (auto& p : ans)
        cout << p.st << ' ' << p.nd << ' ';
    print();
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> c >> q >> l;

    for (int i = 0; i < q; ++i)
        cin >> que[i].st >> que[i].nd;

    //0
    for (int i = 0; i < q; ++i)
        --que[i].st, --que[i].nd;

    dump(c);
    dec(c);
    dump(c);

    //1
    
    for (int i = 0; i < q; ++i)
    {
        ilo.push_back({que[i].st, i * 2});
        ilo.push_back({que[i].nd, i * 2 + 1});
    }
    
    for (int i = 2; i <= sqr; ++i)  
        if (not com[i])
            for (int j = i + i; j <= sqr; j += i)
                com[j] = true;

    for (int i = 2; i <= sqr; ++i)  
        if (not com[i])
        {
            int p = -1;
            for (int j = 0; j < ilo.size(); ++j)
                if (ilo[j].st % i == 0)
                {
                    if (p == -1)
                        p = pri.size(), pri.push_back(i);
                    tab[ilo[j].nd].push_back({p, 0});
                    while (ilo[j].st % i == 0)
                    {
                        ++tab[ilo[j].nd].back().nd;
                        ilo[j].st /= i;
                    }
                    if (ilo[j].st == 1)
                    {
                        ilo[j] = ilo.back();
                        ilo.pop_back(); 
                        --j;
                    }
                }
        }

    sort(begin(ilo), end(ilo));

    for (int i = 0; i < ilo.size(); ++i)
        if (i == 0 or ilo[i].st != ilo[i - 1].st)
        {
            pri.push_back(ilo[i].st);
            for (int j = i; j < ilo.size() and ilo[j].st == ilo[i].st; ++j)
                tab[ilo[j].nd].push_back({(int)pri.size() - 1, 1});
        }

    //2
    cnt.resize(pri.size());

    for (int i = 0; i < pri.size(); ++i)
        while (div(pri[i]))
            ++cnt[i];

    debug(
        dump_range(all(pri));
        dump_range(all(cnt));

        for (int i = 0; i < q * 2; ++i)
        {
            for (auto& p : tab[i])
                cout << p.st << ' ' << p.nd << ':';
            print();
        }
    );

    if (c != "1")
    {
        for (int i = 0; i < q; ++i)
            print(-1);
        return 0;
    }

    //3

    tnc[0].resize(pri.size());
    tnc[1].resize(pri.size());

    int a = 0;
    for (int i = 0; i < pri.size(); ++i)
        if (cnt[i]) ++a, irp.push_back(i);

    for (int i = 0; i < q; ++i)
    {

        int b = 0;
        int hi[2] = {inf, inf};
        int lo[2] = {0, 0};

        for (int j = 0; j < 2; ++j)
            for (auto& p : tab[i * 2 + j])
            {
                if (not tnc[0][p.st] and not tnc[1][p.st] and cnt[p.st])
                    ++b;
                tnc[j][p.st] = p.nd;
            }

        for (int j = 0; j < 2; ++j)
            for (auto& p : tab[i * 2 + j])
            {
                if (tnc[j][p.st])
                    hi[j] = min(hi[j], cnt[p.st] / tnc[j][p.st]);
                if (not tnc[1 - j][p.st])
                    lo[j] = max(lo[j], (cnt[p.st] + tnc[j][p.st] - 1) / tnc[j][p.st]);
            }

        dump(a, b);

        if (b < a)
            print(-1);
        else
        {
            bool fla = false;
            for (int i = lo[0]; i <= hi[0]; ++i)
            {
                dump(i);
                bool fl = true;
                int k = -1;
                for (int j : irp)
                {
                    int p = cnt[j] - i * tnc[0][j];
                    if (tnc[1][j] and (p % tnc[1][j]))
                    {
                        fl = false;
                        break;
                    }
                    if (tnc[1][j] and k == -1)
                        k = p / tnc[1][j];
                    if (tnc[1][j] and k != -1 and k != p / tnc[1][j])
                    {
                        fl = false;
                        break;
                    }
                    if (k != -1 and (k < lo[1] or hi[1] < k))
                    {
                        fl = false;
                        break;
                    }
                }
                if (fl)
                {
                    answer(i, (k == -1? 0 : k));
                    fla = true;
                    break;
                }
            }

            if (not fla)
                print(-1);
        }

        for (int j = 0; j < 2; ++j)
            for (auto& p : tab[i * 2 + j])
                tnc[j][p.st] = 0;
    }
}