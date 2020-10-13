// Jakub Wasilewski
#include <iostream>
#include <vector>
#include <ctgmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Vector
{
    ll x, y;
    long double angle;
    Vector( ll x = 0, ll y = 0, long double offset = 0 ) : x( x ), y( y ) 
    {
        ll odl = ( x * x ) + ( y * y );
        if ( x == 0 and y == 0 )
            angle = 0;
        if ( x >= 0 and y >= 0 )
            angle = ( (long double)y / sqrtl( odl ) );
        if ( x < 0 and y >= 0 )
            angle = ( 2 - (long double)y / sqrtl( odl ) );
        if ( x < 0 and y < 0 )
            angle = ( 2 + (long double)( abs( y ) ) / sqrtl( odl ) );
        if ( x >= 0 and y < 0 )
            angle = ( 4 - (long double)( abs( y ) ) / sqrtl( odl ) );    
        angle += offset;
    }
    inline bool operator< ( const Vector& a ) const 
    {
        return angle < a.angle;
    }
};

inline bool lessThen180 ( const Vector& a, const Vector& b )
{
    return b.angle - a.angle - 2 < 0;
}

int n;
vector< Vector > arr;

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    cin >> n;
    for ( int i = 0; i < n; ++i )
    {
        int x, y; cin >> x >> y;
        if ( x != 0 or y != 0 )
            arr.push_back( Vector( x, y ) );
    }
    sort( arr.begin(), arr.end() );
    int siz = arr.size();
    for ( int i = 0; i < siz; ++i )
        arr.push_back( Vector( arr[i].x, arr[i].y, 4 ) );
    ll res = 0;
    ll x = 0, y = 0;
    int kon = -1;
    for ( int pocz = 0; pocz <= siz; ++pocz )
    {
        res = max( res, ( x * x ) + ( y * y ) );
        if ( pocz == siz ) break;
        while ( kon + 1 < pocz + siz and lessThen180( arr[pocz], arr[kon + 1] ) )
        {
            x += arr[kon + 1].x;
            y += arr[kon + 1].y;
            ++kon;
            res = max( res, ( x * x ) + ( y * y ) );
        }
        x -= arr[pocz].x;
        y -= arr[pocz].y;
    }    
    cout << res << '\n';
}