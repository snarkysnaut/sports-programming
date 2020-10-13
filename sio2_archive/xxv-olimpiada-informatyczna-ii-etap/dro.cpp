#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std; using ll = long long;
template<typename t> using V = vector< t >;
#ifdef DBG 
#define d(...) {__VA_ARGS__;}
#else
#define d(...) 
#endif
#define r(...) resize(__VA_ARGS__)
#define pb(...) push_back(__VA_ARGS__)
#define eb(...) emplace_back(__VA_ARGS__)
#define all(x) begin(x), end(x)

int n, m, t = 1, id;
V< int > dp;
V< int > odw;
V< int > encod;
stack< int > S;
V< V< int > > gr;
V< V< int > > tr;
V< V< int > > sc;

inline void dfs (int v)
{
	odw[v] = t;
	for (int s : gr[v])
		if (odw[s] != t)
			dfs(s);	
	S.push(v);
}

inline void dfs2 (int v)
{
	odw[v] = t;
	encod[v] = id;
	for (int s : tr[v])
		if (odw[s] != t)
			dfs2(s);
	
}

inline void dfs3 (int v)
{
	odw[v] = t;
	for (int s : sc[v])
		if (odw[s] != t)	
			dfs3(s);
	for (int s : sc[v])
		dp[v] += dp[s];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 	cin >> n >> m;   
 	gr.r(n + 1);
 	tr.r(n + 1);
 	odw.r(n + 1);
 	encod.r(n + 1);
 	for (int i = 0; i < m; ++i)
 	{
 		int p, q; cin >> p >> q;
 		gr[p].pb(q);
 		tr[q].pb(p);
 	}
	for (int i = 1; i <= n; ++i)
		if (odw[i] != t)
			dfs(i);
	++t;
	 	
 	while (!S.empty())
 	{
 		int v = S.top(); S.pop();
 		if (odw[v] != t)
 		{
 			++id;
 			dfs2(v);
 		}
 	}	

//	for (int i = 1; i <= n; ++i)	
//		cout << encod[i] << '\n';
	++t;
	sc.r(id + 1);
	dp.r(id + 1);
	for (int i = 1; i <= n; ++i)
	{
		++dp[encod[i]];
		for (int s : gr[i])
			if (encod[i] != encod[s])
				sc[encod[i]].pb(encod[s]);
	}
	
	for (int i = 1; i <= id; ++i)
		if (odw[i] != t)
			dfs3(i);
	
	 for (int i = 1; i <= n; ++i)
	 	cout << dp[encod[i]] - 1 << '\n';
}