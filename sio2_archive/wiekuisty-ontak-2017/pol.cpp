#include <bits/stdc++.h>
#ifndef dbg
#define dbg(...)
#endif
#define all(x) begin(x), end(x)
#define rsz(...) resize(__VA_ARGS__)
#define psh(...) push_back(__VA_ARGS__)
#define emp(...) emplace_back(__VA_ARGS__)
#define prt(...) print(cout, __VA_ARGS__)
#define dmp(...) print(cerr, #__VA_ARGS__, '=', __VA_ARGS__)
#define dprt(...) dbg(print(cerr,__VA_ARGS__))
#define ddmp(...) dbg(dmp(__VA_ARGS__))
using namespace std;using ll=long long;
template<typename t>using V=vector<t>;
template<typename t>void print(ostream& os, const t& a){os<<a<<'\n';}
template<typename t, typename... A>void print
(ostream& os, const t& a, A&&... b){os<<a<<' ';print(os, b...);}

int n, m, id;
stack< int > S;
V< bool > odw;
V< int > encd;
V< V< int > > gr;
V< V< int > > tr;

inline void dfs (int v)
{
    odw[v] = true;
    for (int s : gr[v])
        if (odw[s] == false)
            dfs(s);
    S.push(v);
}

inline void dfs2 (int v)
{
    encd[v] = id;
    odw[v] = true;
    for (int s : tr[v])
        if (odw[s] == false)
            dfs2(s);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;    
    tr.rsz(n + 1);
    gr.rsz(n + 1);
    odw.rsz(n + 1);
    encd.rsz(n + 1);
    
    for (int i = 0; i < m; ++i)
    {
        int p, q; cin >> p >> q;
        gr[p].psh(q);
        tr[q].psh(p);    
    }
    
    for (int i = 1; i <= n; ++i)
        if (odw[i] == false)
            dfs(i);
    
    fill(all(odw), false);
    
    while (!S.empty())  
    {
        if (odw[S.top()] == false)
        {
            dfs2(S.top());
            ++id;
        }
        
        S.pop();
    }    
    
    V< int > deg (id);
    
    for (int i = 1; i <= n; ++i)
        for (int s : gr[i])
            if (encd[i] != encd[s])
                ++deg[encd[s]];
    
    int cnt = 0;
    for (int c : deg)
        cnt += c == 0;
    
    if (cnt > 1)
        return prt(0), 0;    
                    
    V< int > odp;
    for (int i = 1; i <= n; ++i)
        if (deg[encd[i]] == 0)
            odp.psh(i);
    
        
    cout << odp.size() << '\n';
    for (int v : odp)
        cout << v << ' ';
    cout << '\n';    
}