#include <bits/stdc++.h>
#define st first
#define nd second
using namespace std;

constexpr int nax = 1e6, mod = 1e9 + 7;

int n, row[nax + 1], col[nax + 1], res = 1;
pair< int, int > a = {1, 1}, b = {1, 1}, dne;

void panic()
{
    cout << "NO" << '\n' << 0 << endl;
    exit(0);
}

void valid(const pair< int, int > v)
{
    if (not (1 <= v.st and v.st <= n and 1 <= v.nd and v.nd <= n))
        panic();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    dne = {n, n};

    for (int i = 1; i <= n; ++i)    
        cin >> row[i];

    for (int i = 1; i <= n; ++i)
        cin >> col[i];

    --row[1], --col[1];

    while (a != dne or b != dne)
    {
        valid(a); valid(b);
        if (a.st < b.st and row[a.st] > 0)
        {
            while (row[a.st] > 0)
                ++a.nd, valid(a), --row[a.st], --col[a.nd];
        }
        else if (b.nd < a.nd and col[b.nd] > 0)
        {
            while (col[b.nd] > 0)
                ++b.st, valid(b), --row[b.st], --col[b.nd];
        }
        else if (a == b)
        {
            if (row[a.st] > 0 and col[b.nd] > 0)
            {
                res += res; if (res >= mod) res -= mod;
                ++a.nd; valid(a); --row[a.st], --col[a.nd];
                ++b.st; valid(b); --row[b.st], --col[b.nd];
            }
            else if (row[a.st] > 0)
            {
                ++a.nd; valid(a); --row[a.st], --col[a.nd];
                b = a;
            }
            else if (col[b.nd] > 0)
            {
                ++b.st; valid(b); --row[b.st], --col[b.nd];
                a = b;
            }
            else break;
        }
        else if (a.st + 1 == b.st and b.nd + 1 == a.nd)
        {
            ++a.st; 
            valid(a);
            if (a != b)
                --row[a.st], --col[a.nd];

            ++b.nd; 
            valid(b);
            if (a != b)
                --row[b.st], --col[b.nd];
        }
        else if (a.st + 1 < b.st)
        {
            ++a.st; 
            valid(a);
            if (a != b)
                --row[a.st], --col[a.nd];

        }
        else if (b.nd + 1 < a.nd)
        {
            ++b.nd; 
            valid(b);
            if (a != b)
                --row[b.st], --col[b.nd];
        }
    }
    
    if (a != dne or b != dne)
        panic();

    for (int i = 1; i <= n; ++i)
        if (row[i]) panic();
    for (int i = 1; i <= n; ++i)
        if (col[i]) panic();


    cout << "YES" << '\n';
    cout << res << '\n';
}