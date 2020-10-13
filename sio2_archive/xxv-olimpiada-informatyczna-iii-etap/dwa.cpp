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
using ull = unsigned long long;

struct Point
{
    int x, y;
    Point(int x, int y):
    x(x), y(y){}
};

inline bool in_upper_part(const Point& a)
{
    return a.y == 0? a.x > 0 : a.y > 0;
}

inline void operator+= (Point& a, const Point& b)
{
    a.x += b.x; a.y += b.y;
}

inline void operator-= (Point& a, const Point& b)
{
    a.x -= b.x; a.y -= b.y;
}

inline ll operator^ (const Point& a, const Point& b)
{
    return (ll)a.x * b.x + (ll)a.y * b.y;
}

inline ll operator* (const Point& a, const Point& b)
{
    return (ll)a.x * b.y - (ll)a.y * b.x;
}

inline bool operator< (const Point& a, const Point& b)
{
    if (in_upper_part(a) not_eq in_upper_part(b))
        return in_upper_part(a);
    return a * b > 0;
}

inline ull foo(const Point& a)
{
    return (ull)((ll)a.x * a.x) + (ull)((ll)a.y * a.y);
}

inline bool reversed(const Point& a, const Point& b)
{
    return a.x == -b.x and a.y == -b.y;
}

int n;
ull res = 0;
V< Point > tb;


int main(int argc, char** argv)
{
    (void)(argc); (void)(argv);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    
    for (int i = 0; i < n; ++i)
    {
        int x, y; cin >> x >> y;
        
        if (x == 0 and y == 0)
        {
            --n, --i;
            continue;
        }
        
        tb.emp(x, y);       
        tb.emp(-x, -y);
    }
    
    sort(all(tb));

dbg(
    for (auto& p : tb)
        prt(p.x, p.y);
);
    
    int siz = tb.size();
    for (int i = 0; i < siz; ++i)
        tb.psh(tb[i]);

dbg(
    cerr << '\n';
    for (auto& p : tb)
        prt(p.x, p.y);
    cerr << '\n';
);

    
    Point sum(0, 0);
    int hi = -1;
    for (int lo = 0; lo < tb.size(); ++lo)
    {
        while (hi + 1 < siz(tb) and (tb[lo] * tb[hi + 1]) >= 0 
        and not reversed(tb[lo], tb[hi + 1]))
        {
            ++hi, sum += tb[hi];
            res = max(res, foo(sum));
        }
        
        dprt(lo, hi);
        res = max(res, foo(sum));
        sum -= tb[lo];
        res = max(res, foo(sum));
    }   
    
    /*for (int i = 0; i < tb.size(); ++i)
    {
        Point sum(0, 0);
        for (int k = i; k < tb.size(); ++k)
            sum += tb[k], res = max(res, foo(sum));
    }*/
    
    prt(res);
   
             
}