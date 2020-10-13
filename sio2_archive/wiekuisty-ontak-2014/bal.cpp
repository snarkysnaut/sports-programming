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

constexpr int maxn = 1e6;

int n;
int tb[maxn];
priority_queue< pair< int, int > > pq;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--)
    {
        cin >> n;

        for (int i = 0; i < n; ++i)
            cin >> tb[i];

        sort(tb, tb + n);

        int cnt = 1;
        for (int i = 0; i < n; ++i)
        {
            if (i == n - 1 or tb[i] < tb[i + 1])
                pq.push({cnt, tb[i]}), cnt = 1;
            else ++cnt;
        }

        int res = 0;
        V< V< int > > odp;

        while (pq.size() >= 3)
        {
            V< pair< int, int > > tmp;

            while (tmp.size() < 3)
            {
                tmp.push_back(pq.top());
                pq.pop();
            }

            ++res;
            odp.push_back(V< int >());
            
            for (auto& p : tmp) 
                odp.back().push_back(p.nd);

            sort(all(odp.back()));
            reverse(all(odp.back()));

            for (auto& p : tmp)
                if (p.st > 1)
                    pq.push({p.st - 1, p.nd});
        }

        print(res);

        for (auto& v : odp)
            print_range(all(v));

        while (not pq.empty())
            pq.pop();

        odp.clear();
    }
}