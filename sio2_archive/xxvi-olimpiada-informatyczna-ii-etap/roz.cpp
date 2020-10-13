//Jakub Wasilewski
using ll = long long;
constexpr int maxm = 1e6;

int m, q; ll sum, tree[maxm + 1];

inline int max(int a, int b)
{
    return (a > b? a : b);
}

inline int magic(int v)
{
    return (v - ((v - 1) & v));
}

inline void insert(int v, ll c)
{
    for (; v <= m; v += magic(v))
        tree[v] += c;
}

inline ll query(int v)
{
    if (v == m) return sum;
    ll res = 0;
    for (; v; v -= magic(v))
        res += tree[v];
    return res;
}

inline ll query(int l, int r)
{
    return ((l > r)? 0ll : query(r) - query(l - 1));
}

void inicjuj(int em)
{
    m = q = em;
}

void dodaj(int k) 
{
    q = (q == m? 1 : q + 1);
    ll tmp = k - query(q, q);
    sum += tmp;
    insert(q, tmp);
}

void koryguj(int v, int c) 
{
    v = q - v + 1;
    sum += c;
    insert((v <= 0? v + m : v), c);
}

long long suma(int i)
{
    return query(max(q - i + 1, 1), q) + query(m - (i - q) + 1, m);
}
