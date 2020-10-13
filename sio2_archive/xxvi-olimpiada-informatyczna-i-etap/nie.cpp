/*{{{*/
#include <bits/stdc++.h>
#ifdef _GLIBCXX_DEBUG
int c_;
#define cout (c_?cerr:cout)
#define debug(...) {if(!c_)cerr<<"\033[96;1m";++c_;\
__VA_ARGS__;--c_; if(!c_)cerr<<"\033[0m";}
#else
#define debug(...)
#endif
#define st first
#define nd second
#define all(...) (__VA_ARGS__).begin(), (__VA_ARGS__).end()
#define dump(...) debug(print(#__VA_ARGS__, '=',  __VA_ARGS__))
#define dump_range(...) debug(cerr<<#__VA_ARGS__<<": ";print_range(__VA_ARGS__))
using namespace std; using ll = long long; 
template< typename t > using V = vector< t >; void print(){cout<<'\n';}
template< typename t, typename... v > void print(const t& a, v&&... b)
{cout << a << (sizeof...(b)? " " : ""); print(b...);}
template< typename t > void print_range(t a, const t& b)
{while (a!=b) cout << (*a++) << ' '; cout << '\n';}
/*}}}*/

constexpr int nax = 1e6;

int pt[2][nax];
V< int > ilo[2];
string rs, tb[2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (auto& s : tb) cin >> s;

    for (char l : {'A', 'T', 'C', 'G'})
    {
        for (int i = 0; i < 2; ++i)
        {
            auto& s = tb[i]; 
            auto& p = pt[i];
            auto& il = ilo[i];

            il.clear(); il.push_back(s.size());

            for (int i = s.size() - 1, v = (int)rs.size() - 1; i >= 0 and v >= 0; --i)
                if (s[i] == rs[v])
                    il.push_back(i), --v;

            for (int i = s.size() - 1, v = s.size(); i >= 0; --i)
            {
                if (s[i] == l) v = i;
                p[i] = v;
            }
        }
        
debug(
        for (int j = 0; j < 2; ++j)
        {
            dump(j); dump_range(pt[j], pt[j] + tb[j].size());
            dump_range(all(ilo[j]));
        }
);

        string nrs;
        int it[2] = {-1, -1};

        for (int i = -1; i < (int)rs.size(); ++i)
        {
            dump(i, it[0], it[1], nrs);
            if (i >= 0)
            {
                ++it[0], ++it[1];
                for (int j = 0; j < 2; ++j)
                    while (tb[j][it[j]] != rs[i])
                        ++it[j];

                nrs += string(1, rs[i]);
            }

            while (true)
            {
                bool fl = true;
                for (int j = 0; j < 2; ++j)
                    if (it[j] + 1 >= tb[j].size())
                        fl = false;

                if (not fl) break;

                int nit[2] = {pt[0][it[0] + 1], pt[1][it[1] + 1]};

                for (int j = 0; j < 2; ++j)
                    if (nit[j] >= ilo[j][(int)rs.size() - i - 1])
                        fl = false;

                if (not fl) break;

                for (int j = 0; j < 2; ++j)
                    it[j] = nit[j];

                nrs += string(1, l);
            }
        }

        dump(l, nrs);

        rs = nrs;
    }

    print(rs);
}