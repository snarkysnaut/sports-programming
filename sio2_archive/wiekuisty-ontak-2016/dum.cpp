#include <bits/stdc++.h>

constexpr int nax = 1e5, logg = 19, rozm = (1 << logg), wex = 3;

using ll = long long;
using namespace std;
using Sum = array< ll, wex >;

struct Node
{
    int dl;
    Sum sum;

    Node() : dl(0), sum({0, 0, 0}) {}
    Node(int v) : dl(1), sum({v, v, v}) {}
};

Node merge(const Node& l, const Node& r)
{
    Node res; 
    res.dl = l.dl + r.dl;
    res.sum[0] = l.sum[0] + r.sum[0];
    res.sum[1] = l.sum[1] + r.sum[1] + r.sum[0] * l.dl;
    res.sum[2] = l.sum[2] + r.sum[2] + r.sum[1] * l.dl * 2 + r.sum[0] * l.dl * l.dl;
    return res;
}

struct SegTree
{
    array< Node, (rozm << 1) > tree;

    void insert(int v, int c)
    {
        v += rozm;
        tree[v] = Node(c);
        for (v >>= 1; v >= 1; v >>= 1)
            tree[v] = merge(tree[v << 1], tree[(v << 1) + 1]);
    }

    ll query(int l, int r, int s)
    {
        l += rozm; r += rozm;
        Node ls = tree[l], rs = tree[r];
        if (l == r) return ls.sum[s];
        while ((l >> 1) != (r >> 1))
        {
            if ((l & 1) == 0)
                ls = merge(ls, tree[l + 1]);
            if ((r & 1) == 1)
                rs = merge(tree[r - 1], rs);
            l >>= 1; r >>= 1;
        }
        //cerr << l << ' ' << r << ' ' << s << ' ' << ls.sum[s] << ' ' << rs.sum[s] << '\n';
        auto res = merge(ls, rs);
        return res.sum[s];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    //cout << merge(merge(Node(9), Node(11)), Node(13)).sum[1] << '\n';
    //cout << merge(Node(9), merge(Node(11), Node(13))).sum[1] << '\n';
    //cout << merge(Node(7), Node(9)).sum[2] << '\n';

    SegTree tree;

    for (int i = 1; i <= n; ++i)
    {
        int v; cin >> v;
        tree.insert(i, v);
    }

    int q; cin >> q;

    while (q--)
    {
        int v; cin >> v;
        if (v >= 0)
        {
            int l, r; cin >> l >> r;
            cout << tree.query(l, r, v) << '\n';
        }
        else
        {
            int d; cin >> d;
            tree.insert(-v, d);
        }
    }
}