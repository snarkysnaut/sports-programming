#include <bits/stdc++.h>
#ifdef DBG
#define dbg(...) {cerr << "\033[1;96m"; __VA_ARGS__; cerr << "\033[1;00m";}
#else
#define dbg(...)
#endif
#define all(...) begin(__VA_ARGS__), end(__VA_ARGS__)
#define arg(...) atoi(argv[__VA_ARGS__])
#define siz(...) (int)(__VA_ARGS__).size()
#define rsz(...) resize(__VA_ARGS__)
#define psh(...) push_back(__VA_ARGS__)
#define emp(...) emplace_back(__VA_ARGS__)
#define prt(...) print(cout, __VA_ARGS__)
#define dprt(...) dbg(print(cerr, __VA_ARGS__))
#define ddmp(...) dbg(dmp(__VA_ARGS__))
#define dmp(...) print(cerr, #__VA_ARGS__, '=', __VA_ARGS__)
using namespace std; using ll = long long;
template< typename t >void print(ostream& os, const t& a)
{os << a << '\n';}template< typename t, typename... v >
void print(ostream& os, const t& a, v&&... b){os << a << ' '; print(os, b...);}
template< typename... t > using V = vector< t... >;


int n, res = -1;
string s;

inline bool valid(V< int >& cnt)
{
    return (cnt[0] != cnt[1] and cnt[1] != cnt[2] and cnt[2] != cnt[0]);
}

inline void spr(int v)
{
    V< int > cnt (3);
    
    for (int i = v; i < siz(s); ++i)
    {
        if (s[i] == 'C')
            ++cnt[0];
        if (s[i] == 'B')
            ++cnt[1];
        if (s[i] == 'S')
            ++cnt[2];
        
        if (valid(cnt))
            res = max(res, i - v + 1);
    }
}

int main(int argc, char** argv)
{
    (void)(argc); (void)(argv);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> s;
    
    for (int i = 0; i < min(n, 10); ++i)
        spr(i);
    
    reverse(all(s));
    
    for (int i = 0; i < min(n, 10); ++i)
        spr(i);

    if (res == -1)
        prt("NIE");
    else
        prt(res);
}