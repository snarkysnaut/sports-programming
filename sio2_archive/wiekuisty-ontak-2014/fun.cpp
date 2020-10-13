#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int curr = 1;
const int rozm = 70;
const int mod = 1e9 + 7;
vector< vector< int > > odp;
vector< vector< int > > binomial;

int pow ( int a, int wyk )
{
	if ( wyk == 1 ) return a;
	if ( wyk % 2 == 0 ) return ( (ll)pow( a, wyk / 2 ) * pow( a, wyk / 2 ) ) % mod;
	return ( (ll)pow( a, wyk - 1 ) * a ) % mod;
}

int dp [71][71][71];

int foo ( int count, int pop, int zost )
{
	if ( dp[count][pop][zost] != -1 )
		return dp[count][pop][zost];
	if ( count == 0 ) return 1;
	if ( zost == 0 ) return 0;
	int res = 0;
	for ( int i = 1; i <= count; ++i )
	{
		int tmp = foo( count - i, i, zost - 1 );
//		cout << count - 1 << ' ' << i << ' ' << zost - 1 << ' ' << tmp << '\n';
		tmp = ( (ll)tmp * pow( pop, i ) ) % mod;
		tmp = ( (ll)tmp * binomial[count][i] ) % mod;
		res = ( res + tmp ) % mod;
	}
	dp[count][pop][zost] = res;
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	binomial.resize( rozm + 1, vector< int >( rozm + 1 ) );
	for ( int i = 0; i <= rozm; ++i )
	{
		binomial[i][0] = 1;
		binomial[i][i] = 1;
	}
	for ( int i = 1; i <= rozm; ++i )
		for ( int k = 1; k < i; ++k )
			binomial[i][k] = ( binomial[i - 1][k - 1] + binomial[i - 1][k] ) % mod;
//	for ( int i = 0; i <= rozm; ++i )
//		for ( int k = 0; k <= i; ++k )
//			cout << binomial[i][k] << ( k == i ? '\n' : ' ' );
	for ( int i = 0; i < 71; ++i )
		for ( int k = 0; k < 71; ++k )
			for ( int j = 0; j < 71; ++j )
				dp[i][k][j] = -1;
	int ile;
	cin >> ile;
	for ( int i = ile - 1; i >= 1; --i )
	{
		int tmp = foo( ile - 1, 1, i );
//		cout << ile - 1 << ' ' << 1 << ' ' << i << ' ' << tmp << '\n';
	}
	for ( int i = 1; i < ile; ++i )
		cout << ( ( (ll)dp[ile - 1][1][i] * binomial[ile][1] ) % mod )  << ' ';
	cout << '\n';
}