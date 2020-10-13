// Jakub Wasilewski
#include <iostream>
#include <vector>
#include <algorithm>
#define R resize
#define EB emplace_back
#define ALL(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<typename t>using V=vector<t>;

const int mod = 1e9 + 7;

struct Edge
{
    int p, q, val;
    Edge( int p, int q, int val ) : p( p ), q( q ), val( val ) {}
};

inline bool operator< ( const Edge& mn, const Edge& wc )
{
    return mn.val < wc.val;
}

struct Node
{
    int v, siz, res, h;
    Node( int v = -1, int siz = 1, int res = 1, int h = 0 ) : 
    v( v ), siz( siz ), res( res ), h( h ) {}
};

int n, m, H;
V< Edge > ed;
V< Node > graf;

inline int find ( int v )
{
    return graf[v].v != graf[graf[v].v].v? graf[v].v = find( graf[v].v ) : graf[v].v;
}

inline void join ( Edge e )
{
    e.p = find( e.p );
    e.q = find( e.q );
    if ( graf[e.p].siz < graf[e.q].siz )
        swap( e.p, e.q );
    graf[e.q].v = e.p;
    graf[e.p].siz += graf[e.q].siz;
    graf[e.p].res = ( (ll)( graf[e.p].res + e.val - graf[e.p].h ) * (ll)( graf[e.q].res + e.val - graf[e.q].h ) ) % mod;
    graf[e.p].h = e.val;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> H;
    graf.R( n * m + 1 );
    for ( int i = 0; i < n * m + 1; ++i )
        graf[i].v = i;
    graf[n * m].h = H;
    for ( int i = 0; i < n; ++i )
        for ( int k = 0; k < m - 1; ++k )
        {
            int val; cin >> val;
            ed.EB( i * m + k, i * m + k + 1, val );
        }
    for ( int i = 0; i < n - 1; ++i )
        for ( int k = 0; k < m; ++k )
        {
            int val; cin >> val;
            ed.EB( i * m + k, ( i + 1 ) * m + k, val );
        }
    sort( ALL( ed ) );
    ed.EB( 0, n * m, H );
    for ( auto& e : ed )
        if ( find( e.p ) != find( e.q ) )
            join( e );
    cout << graf[find( n * m )].res << '\n';
}