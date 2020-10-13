#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; using ll = long long;
template<typename t> using V = vector< t >;
#define all(x) begin(x), end(x)
#define r(...) resize(__VA_ARGS__)
#define pb(...) push_back(__VA_ARGS__)
#define eb(...) emplace_back(__VA_ARGS__)
#ifdef DBG
#define d(...) {__VA_ARGS__;}
#else
#define d(...)
#endif

struct Ev
{
	bool typ;
	int x, s, a, t;
	Ev(bool typ, int x, int s, int a, int t):typ(typ), x(x), s(s), a(a), t(t){}
};

inline bool operator< (const Ev& mn, const Ev& wc)
{
	return mn.x == wc.x? mn.typ < wc.typ : mn.x < wc.x;
}

int t;
int n, m; int id_zap;
V< Ev > evs;
V< pair< int, int > > tab;
V< pair< ll, pair< int, int > > > odp;

inline ll foo (ll pocz, ll pro, int odl)
{
	ll kon = pocz + (pro * (odl - 1));
	return ((pocz + kon) * odl) / 2;
}

inline void gen (int lo, int hi, V< int >& v)
{
	if (lo == hi or v.empty())
		return;
	int mid = (lo + hi) / 2;
//	d(
//	cerr << lo << ' ' << hi << ' ' << mid << '\n';
//	for (int k : v)
//		cerr << k << ' ';
//	cerr << '\n';
//	);
//	cerr << "k: " << lo << ' ' << hi << ' ' << mid << '\n';
	ll cnt = 0;
	ll cur = 0;
	ll sum = 0;
	int pop = 0;
	for (int k = 0; k < v.size(); ++k)
	{
		auto& ev = evs[v[k]];
		if ((ev.t <= mid and ev.typ == 0) or (ev.t > mid and ev.typ == 1))
		{
//			cerr << ev.typ << ' ' << ev.x << ' ' << ev.s << ' ' << ev.a << ' ' << ev.t << '\n';
			int odl = ev.x - pop;
			sum += foo(cur + cnt, cnt, odl);
			cur += cnt * odl;
			if (ev.typ == 1)
			{
				int id = ev.a;
				int z = ev.s;
//				cerr << "zap: " << ev.x << ' ' << sum << ' ' << cur << '\n';
				odp[id].first += sum * z;
			}
			if (ev.typ == 0)
			{
//				cerr << "dod: " << ev.x << ' ' << ev.s << ' ' << ev.a << '\n';
				sum += ev.s;
				cur += ev.s;
				cnt += ev.a;	
			}
			pop = ev.x;
//			cerr << cnt << ' ' << cur << ' ' << sum << '\n';
		}
	}
	
	V< V< int > > ilo;
	ilo.r(2);
	for (int k : v)
		ilo[evs[k].t > mid].pb(k);
		
	gen(lo, mid, ilo[0]);
	gen(mid + 1, hi, ilo[1]);
}

inline void dodaj (int x, int s, int a)
{
	int st = 0;
	int odl = s / a;
	if (x - odl < 1)
		st = s - (x - 1) * a;
	else
		st = s - odl * a;
	evs.eb(0, max(1, x - odl), st, a, t++);
	evs.eb(0, x, 0, -(2 * a), t++);
	int mt = s - odl * a;
	evs.eb(0, min(n + 1, x + odl), 0, a, t++);
	evs.eb(0, min(n + 1, x + odl + 1), -mt, 0, t++);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 	cin >> n >> m;
 	tab.r(n + 1);
	for (int i = 0; i < m; ++i)
	{
		char c; cin >> c;
		if (c == 'P')
		{
			int x, s, a;
			cin >> x >> s >> a;
			dodaj(x, s, a);
			tab[x] = {s, a};
		}
		if (c == 'U')
		{
			int x;
			cin >> x;
			int s, a;
			s = tab[x].first;
			a = tab[x].second;
			s = -s; a = -a;
			dodaj(x, s, a);			
		}
		if (c == 'Z')
		{
			int lo, hi;
			cin >> lo >> hi;
			odp.pb({0,{lo, hi}});
			evs.eb(1, lo - 1, -1, id_zap, t++);
			evs.eb(1, hi, 1, id_zap, t++);	
			++id_zap;
		}
	}
	sort(all(evs));
//	for (int i = 0; i < evs.size(); ++i)
//		cerr << evs[i].typ << ' ' << evs[i].x << ' ' << evs[i].s << ' ' << evs[i].a << ' ' << 
//		evs[i].t << '\n';
	
	V< int > tmp(evs.size());
	for (int i = 0; i < tmp.size(); ++i)
		tmp[i] = i;
	
	gen(0, tmp.size() - 1, tmp);
	
	for (auto& p : odp)
	{
//		cerr << p.first << '\n';
		cout << p.first / (p.second.second - p.second.first + 1) << '\n';
	}
}
