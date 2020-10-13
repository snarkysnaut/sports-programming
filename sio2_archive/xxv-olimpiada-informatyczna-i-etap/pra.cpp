// Jakub Wasilewski
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define R resize
#define EB emplace_back
#define LOG(x) #x << ": " << x
#define ALL(x) (x).begin(), (x).end()
#ifndef DEBUG
#define d(...)
#else
#define d(...) \
cerr<<"\033[36m"<<__VA_ARGS__<<"\033[0m"
#endif
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<typename t>using V=vector<t>;

struct praw
{
    int l, p, id;
    praw( int l = 0, int p = 0, int id = 0 ) : l( l ), p( p ), id( id ) {}
};

inline bool operator< ( const praw& mn, const praw& wc )
{
    return mn.l < wc.l;
}

inline bool by_end ( const praw& mn, const praw& wc )
{
    return mn.p < wc.p;
}

int v;
int res;
int n, m;
int rozm = 1;
V< praw > tab;
V< praw > odp;
priority_queue< int, V< int >, greater< int > > Q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    tab.R( n );
    for ( int i = 0; i < n; ++i )
    {
        cin >> tab[i].l >> tab[i].p;
        tab[i].id = i + 1;
    }
    sort( ALL( tab ) );
    for ( int i = 0; i < n; ++i )
    {
        Q.push( tab[i].p );
        if ( Q.size() > m )
            Q.pop();
        if ( Q.size() == m and
             Q.top() - tab[i].l > res )
        {
            res = Q.top() - tab[i].l;
            v = i;
        }
    }
    for ( int i = 0; i < n; ++i )
        if ( tab[i].l <= tab[v].l and tab[i].p > tab[v].l ) 
            odp.EB( tab[i] );
    sort( ALL( odp ), by_end );  
    reverse( ALL( odp ) );
    cout << res << '\n';
    if ( odp.size() >= m )
        for ( int i = 0; i < m; ++i )
            cout << odp[i].id << ' ';
    cout << '\n';
}