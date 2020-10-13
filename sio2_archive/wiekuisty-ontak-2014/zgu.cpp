#include <bits/stdc++.h>
using namespace std;
constexpr int nax = 300;

struct Edge
{
    int p, q, wg;
    Edge() : Edge(-1, -1, -1) {}
    Edge(int p, int q, int wg) : p(p), q(q), wg(wg) {}
};

inline bool operator<(const Edge& mn, const Edge& wc)
{
    return mn.wg < wc.wg;
}

inline bool by_ans(const Edge& mn, const Edge& wc)
{
    return make_pair(mn.p, mn.q) < make_pair(wc.p, wc.q);
}

int n, mat[nax + 1][nax + 1];
bool rel[nax + 1][nax + 1];
Edge S[(nax + 1) * (nax + 1)];
//multiset< Edge > S;
vector< Edge > ans;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int pt = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            cin >> mat[i][j];
            if (mat[i][j] > 0)
                S[pt++] = Edge(i, j, mat[i][j]);
                //S.emplace(i, j, mat[i][j]);
        }

    sort(begin(S), begin(S) + pt);

    for (int i = 0; i < pt; ++i)
    //while (not S.empty())
    {
        //auto ed = *S.begin(); S.erase(S.begin());
        auto ed = S[i];
        if (rel[ed.p][ed.q]) continue;
        ans.push_back(ed);
        for (int i = 1; i <= n; ++i)
            if (mat[ed.p][i] > 0 and mat[ed.q][i] > 0)
                if (mat[ed.p][i] - mat[ed.q][i] == ed.wg)
                    rel[ed.p][i] = true;
        for (int i = 1; i <= n; ++i)
            if (mat[i][ed.p] > 0 and mat[i][ed.q] > 0)
                if (mat[i][ed.q] - mat[i][ed.p] == ed.wg)
                    rel[i][ed.q] = true;
    }

    sort(begin(ans), end(ans), by_ans);

    cout << ans.size() << '\n';
    for (auto& ed : ans)
        cout << ed.p << ' ' << ed.q << ' ' << ed.wg << '\n';
}