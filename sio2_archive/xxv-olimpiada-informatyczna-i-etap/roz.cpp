// Jakub Wasilewski
#include <set>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxC = (int)1e5;

struct Ev
{
    int lo, hi, l, p;
    Ev( int lo, int hi, int l, int p ) :
    lo( lo ), hi( hi ), l( l ), p( p ) {}
};

inline bool operator< ( const Ev& mn, const Ev& wk )
{
    return mn.l < wk.l;
}

int n, m, r;
vector< vector< Ev > > ilo;
vector< vector< int > > tab;
typedef set< Ev >::iterator IT;

inline void add ( const Ev& ev, int t )
{
    int hi = min( ev.hi, t - 1 );
    ++tab[ev.lo][ev.l];
    --tab[ev.lo][ev.p + 1];
    --tab[hi + 1][ev.l];
    ++tab[hi + 1][ev.p + 1];
}

inline void foo ( int v )
{
    set< Ev > S;
    S.insert( Ev( 0, -1, 0, 0 ) );
    S.insert( Ev( 0, -1, m + 1, m + 1 ) );
    for ( Ev& e : ilo[v] )
    {
        IT it = S.lower_bound( e );
        IT pop = --it; ++it;
        if ( (*pop).p >= e.l )
        {
            add( (*pop), e.lo );
            Ev tmp = (*pop);
            S.erase( pop );
            if ( e.lo <= tmp.hi )
                S.insert( Ev( e.lo, tmp.hi, tmp.l, e.l - 1 ) );
        }
        while ( (*it).p <= e.p )
        {
            add( (*it), e.lo );
            IT tmp = it++;
            S.erase( tmp );
        }
        if ( (*it).l <= e.p )
        {
            add( (*it), e.lo );
            Ev tmp = (*it);
            S.erase( it );
            if ( e.lo <= tmp.hi )
                S.insert( Ev( e.lo, tmp.hi, e.p + 1, tmp.p ) );
        }
        S.insert( e );
    }
    IT it = S.begin();
    while ( it != S.end() )
    {
        add( (*it), INT_MAX );
        ++it;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> r;
    ilo.resize( maxC + 1 );
    tab.resize( n + 2, vector< int >( m + 2 ) );
    for ( int i = 1; i <= n; ++i )
        for ( int k = 1; k <= m; ++k )
        {
            int p; cin >> p;
            ilo[p].emplace_back( max( 1, i - r + 1 ), min( i, n - r + 1 ), max( 1, k - r + 1 ), min( k, m - r + 1 ) );
        }
    for ( int i = 1; i <= maxC; ++i )
        if ( !ilo[i].empty() )
            foo( i );
    for ( int i = 0; i <= n; ++i )
        for ( int k = 1; k <= m; ++k )
            tab[i][k] += tab[i][k - 1];
    for ( int i = 1; i <= n; ++i )
        for ( int k = 0; k <= m; ++k )
            tab[i][k] += tab[i - 1][k];
    ll res = 0;
    int maks = 0;
    for ( int i = 1; i <= n; ++i )
        for ( int k = 1; k <= m; ++k )
        {
            maks = max( maks, tab[i][k] );
            res += tab[i][k];
        }
    cout << maks << ' ' << res << '\n';
}