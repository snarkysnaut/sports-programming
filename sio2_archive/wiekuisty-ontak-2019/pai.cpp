#include <bits/stdc++.h>
#define st first
#define nd second
using namespace std;
using ll = long long;

constexpr int nax = 4e4;

struct Event
{
    int t, lo, hi, v;
    Event(int t, int lo, int hi, int v) : t(t), lo(lo), hi(hi), v(v) {}
};

inline bool operator<(const Event& mn, const Event& wc)
{
    return mn.t < wc.t;
}

struct Node
{
    int siz = 0, val = 0, res = 0;
};

ll ser = 0;
int n, rozm = 1; ll res;
vector< Node > tree;
vector< pair< int, int > > low;
vector< Event > evs[16];

void update(const int v)
{
    //if (v == 1)
        //cerr << "fafd" << ' ' << tree[(v << 1)].res << ' ' <<  tree[(v << 1) + 1].res << ' ' << tree[1].val << ' ' << tree[1].siz << '\n';

    if (tree[v].val)
        tree[v].res = tree[v].siz;
    else if (v < rozm)
        tree[v].res = tree[(v << 1)].res + tree[(v << 1) + 1].res;
    else
        tree[v].res = 0;

    //if (v == 1)
        //cerr << tree[v].res << '\n';
}

void insert(int l, int r, int c)
{
    //cerr << l << ' ' << r << ' ' << c << '\n';
    if (r < l) return;
    l += rozm; r += rozm;
    //cerr << l << ' ' << r << ' ' << c << '\n';

    tree[l].val += c;
    if (l != r) tree[r].val += c;

    update(l); update(r);

    while ((l >> 1) != (r >> 1))
    {
        if ((l & 1) == 0)
            tree[l + 1].val += c, update(l + 1);
        if ((r & 1) == 1)
            tree[r - 1].val += c, update(r - 1);

        update(l); update(r);
        l >>= 1; r >>= 1;
    }

    update(l); update(r);

    for (l >>= 1; l; l >>= 1)
        update(l);
}

int adj(int v, int q)
{
    while ((((v % 4) + 4) % 4) != q) ++v;
    return v;
    /*
    //cerr << v << ' ' << q << ' ';
    int a = q - (v % 4);
    if (a < 0) a += 4;
    //cerr << v + a << '\n';
    return v + a;
    */
}

int jda(int v, int q)
{
    while ((((v % 4) + 4) % 4) != q) --v;
    return v;
    /*
    //cerr << v << ' ' << q << ' ';
    int a = (v % 4) - q;
    if (a < 0) a += 4;
    //cerr << v - a << '\n';
    return v - a;
    */
}

int left(const int v, const int a)
{
    int r = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            int ni = i - a;
            if (ni < 0) ni += 4;
            r += ((bool)((1 << (ni * 4 + j)) & v) * (1 << (i * 4 + j)));
        }
    return r;
}

int down(const int v, const int a)
{
    int r = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            int nj = j - a;
            if (nj < 0) nj += 4;
            r += ((bool)((1 << (i * 4 + nj)) & v) * (1 << (i * 4 + j)));
        }
    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int x1, y1, x2, y2, p;
        cin >> x1 >> y1 >> x2 >> y2 >> p;

        p = left(p, x1 % 4);
        p = down(p, y1 % 4);

        //cerr << p << '\n';

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (p & (1 << (i * 4 + j)))
                {
                    int nx1 = adj(x1, i), ny1 = adj(y1, j), nx2 = jda(x2, i), ny2 = jda(y2, j);
                    //ser += (nx2 / 4 - nx1 / 4 + 1) * (ny2 / 4 - ny1 / 4 + 1);
                    //cerr << i << ' ' << j << ' ' << nx1 << ' ' << ny1 << ' ' << nx2 << ' ' << ny2 << '\n';
                    if (nx1 >= 0 and nx2 >= 0 and ny1 >= 0 and ny2 >= 0)
                    {
                        evs[i * 4 + j].emplace_back(nx1 / 4, ny1 / 4, ny2 / 4, 1);
                        evs[i * 4 + j].emplace_back(nx2 / 4 + 1, ny1 / 4, ny2 / 4, -1);
                    }
                }
    }

    for (int i = 0; i < 16; ++i)
    {
        sort(begin(evs[i]), end(evs[i]));

        for (auto& ev : evs[i])
            low.push_back({ev.lo, ev.lo}), low.push_back({ev.hi, ev.hi});

        sort(begin(low), end(low));
        low.resize(unique(begin(low), end(low)) - begin(low));

        int siz = low.size();
        for (int i = 1; i < siz; ++i)
            if (low[i].st - low[i - 1].st > 1)
                low.push_back({low[i - 1].st + 1, low[i].st - 1});

        sort(begin(low), end(low));

        rozm = 2;
        while (rozm < low.size()) rozm <<= 1;
        tree.resize(rozm << 1);

        for (int i = 0; i < low.size(); ++i)
            tree[i + rozm].siz = low[i].nd - low[i].st + 1;

        for (int i = rozm - 1; i >= 1; --i)
            tree[i].siz = tree[i << 1].siz + tree[(i << 1) + 1].siz;

        int p = 0;
        for (auto& ev : evs[i])
        {
            int sk = ev.t - p;
            res += ((ll)tree[1].res * sk);
            //cerr << i << ' ' << ev.t << ' ' << p << ' ' << tree[1].res << ' ' << sk << '\n';
            int lo = lower_bound(begin(low), end(low), make_pair(ev.lo, ev.lo)) - begin(low);
            int hi = lower_bound(begin(low), end(low), make_pair(ev.hi, ev.hi)) - begin(low);
            insert(lo, hi, ev.v);
            p = ev.t;
        }

        tree.clear(); low.clear();
    }
        
    //cerr << ser << '\n';
    cout << res << '\n';
}