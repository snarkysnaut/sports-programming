#include <bits/stdc++.h>
using namespace std;

constexpr int nax = 2e3;

int n, q, typ[nax + 1][nax + 1], lef[nax + 1][nax + 1], upp[nax + 1][nax + 1], fu[2 * nax + 1], uf[2 * nax + 1], col[2 * nax + 1], vis[2 * nax + 1];
vector< int > gr[2 * nax + 1];

int find(const int v)
{
    return fu[v] < 0? v : fu[v] = find(fu[v]);
}

int dnif(const int v)
{
    return uf[v] < 0? v : uf[v] = find(uf[v]);
}

void join(int p, int q)
{
    p = find(p);
    q = find(q);
    if (p == q) return;
    if (fu[p] > fu[q]) swap(p, q);
    fu[p] += fu[q];
    fu[q] = p;
}

bool dfs(const int v, const int c)
{
    vis[v] = true;
    col[v] = c;
    int siz = gr[v].size();
    int cnt = 0;
    for (int i = 0; i < siz; ++i)
    {
        int s = gr[v][i];
        if (not vis[s])
        {
            ++cnt;
            if (not dfs(s, 1 - c)) return false;
        }
        else
        {
            if (col[s] == col[v]) return false;
            gr[v][i] = gr[v][siz - 1];
            --siz;
            --i;
            continue;
        }
        if (col[s] == col[v]) return false;
    }
    gr[v].resize(siz);
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= 2 * n; ++i)
        fu[i] = -1;

    for (int i = 1; i <= 2 * n; ++i)
        gr[i].reserve(n);

    for (int i = 1; i <= n; ++i)
    {
        string s; cin >> s;
        for (int j = 1; j <= n; ++j)
            typ[i][j] = (s[j - 1] == 'B'? 1 : 0);
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            lef[i][j] = lef[i][j - 1] xor typ[i][j - 1];

    for (int j = 1; j <= n; ++j)
        for (int i = 1; i <= n; ++i)
            upp[i][j] = upp[i - 1][j] xor typ[i - 1][j];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if ((typ[i][j] == 0) and ((1 xor upp[i][j] xor lef[i][j]) == 0))
                join(i, j + n);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if ((typ[i][j] == 0) and ((1 xor upp[i][j] xor lef[i][j]) == 1))
                gr[find(i)].push_back(find(j + n)), gr[find(j + n)].push_back(find(i));

    bool fla = true;

    for (int i = 1; fla and (i <= 2 * n); ++i)
        if (not vis[find(i)])
            if (not dfs(find(i), 0)) fla = false;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            upp[i][j] xor_eq typ[i][j], lef[i][j] xor_eq typ[i][j];

    int su = 0;
    for (int i = 1; i <= 2 * n; ++i)
        su += gr[i].size();

    //if (fla)
        //assert(su <= 2 * n);

    for (int i = 0; i < q; ++i)
    {
        if (not fla)
        {
            cout << "NO" << '\n'; continue;
        }

        string p[2], q[2];
        cin >> p[1] >> q[1] >> p[0] >> q[0];

        bool fl = true;
        int val[2 * nax + 1];

        for (int i = 1; i <= 2 * n; ++i)
            val[i] = -1;

        for (int i = 0; fl and i < 2; ++i) 
            for (int j = 1; fl and j <= n; ++j)
            {
                if (val[find(i * n + j)] == -1)
                    val[find(i * n + j)] = p[i][j - 1];
                if (val[find(i * n + j)] != p[i][j - 1])
                    fl = false;
            }

        for (int i = 1; fl and i <= 2 * n; ++i)
            if (val[i] != -1)
                for (int s : gr[i])
                    if (val[s] == val[i])
                        fl = false;

        for (int i = 1; fl and i <= n; ++i)
        {
            int a = p[0][i - 1] - '0';
            int b = q[0][i - 1] - '0';
            if ((lef[i][n] xor a xor b) == 1)
                fl = false;
        }

        for (int j = 1; fl and j <= n; ++j)
        {
            int a = p[1][j - 1] - '0';
            int b = q[1][j - 1] - '0';
            if ((upp[n][j] xor a xor b) == 1)
                fl = false;
        }

        cout << (fl? "YES" : "NO") << '\n';
    }
}