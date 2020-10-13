// Jakub Wasilewski
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge
{
    int p, q, wg;
    Edge( int p, int q, int wg ) : p( p ), q( q ), wg( wg ) {}
};

int ile;
vector< int > d;
vector< int > l;
vector< Edge > graf;

bool twoVerticles ()
{
    if ( ile == 2 )
    {
        graf.emplace_back( 1, 2, 1 );
        return true;
    }
    return false;
}

bool edge ()
{
    int roz = abs( l[2] - d[2] );
    for ( int i = 3; i <= ile - 1; ++i )
        if ( abs( l[i] - d[i] ) != roz )
            return false;
    if ( roz == 0 ) return false;
    graf.emplace_back( 1, ile, roz );
    for ( int i = 2; i <= ile - 1; ++i )
    {
        int v = ( l[i] > d[i] )? 1 : ile;
        graf.emplace_back( v, i, max( l[i], d[i] ) - roz );
    }
    return true;
}

bool path ()
{
    int odl = INT_MAX;
    for ( int i = 2; i <= ile - 1; ++i )
        odl = min( odl, d[i] + l[i] );
    vector< int > tab( odl + 1, -1 );
    tab[0] = 1; tab[odl] = ile;
    for ( int i = 2; i <= ile - 1; ++i )
        if ( d[i] + l[i] == odl )
        {
            if ( tab[d[i]] != -1 )
                return false;
            else
                tab[d[i]] = i;
        }
    for ( int i = 2; i <= ile - 1; ++i )
        if ( d[i] + l[i] > odl )
        {
            int wg = ( d[i] + l[i] - odl ) / 2;
            int odlOdDw = d[i] - wg;
            if ( ( d[i] + l[i] - odl ) % 2 == 1 or odlOdDw > odl
                 or odlOdDw < 0 or tab[odlOdDw] == -1 )
                return false;
            graf.emplace_back( tab[odlOdDw], i, wg );
        }
    int pop = 1;
    int currOdl = 0;
    for ( int i = 1; i <= odl; ++i )
        if ( tab[i] != -1 )
        {
            graf.emplace_back( pop, tab[i], i - currOdl );
            currOdl = i; pop = tab[i];
        }
    return true;
}

int main()
{
    ios_base::sync_with_stdio( false );
    cin.tie( nullptr );
    cin >> ile;
    d.resize( ile + 1 ); 
    l.resize( ile + 1 );
    for ( int i = 2; i <= ile - 1; ++i )
        cin >> d[i];
    for ( int i = 2; i <= ile - 1; ++i )
        cin >> l[i];
    if ( twoVerticles() or edge() or path() )
    {
        cout << "TAK" << '\n';
        for ( auto& e : graf )
            cout << e.p << ' ' << e.q << ' ' << e.wg << '\n';
    }
    else
       cout << "NIE" << '\n';
}