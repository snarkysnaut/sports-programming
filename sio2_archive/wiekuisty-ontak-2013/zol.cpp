#include <bits/stdc++.h>
using namespace std;

constexpr int nax = 3000, inf = 1e9;

int n, nim[nax + 1];
string s;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    reverse(begin(s), end(s));

    n = s.length();

    for (int i = 1; i <= n; ++i)
    {
        vector< int > mex;

        for (int j = 1; j <= i; ++j)
        {
            int p = 0;
            for (int k = i - j; k >= 0; k -= j)
            {
                p xor_eq nim[k];
                mex.push_back(p);
            }
        }

        sort(begin(mex), end(mex));
        mex.resize(unique(begin(mex), end(mex)) - begin(mex));

        nim[i] = inf;
        for (int j = 0; j < mex.size(); ++j)
            if (mex[j] != j)
            {
                nim[i] = j;
                break;
            }

        if (nim[i] == inf) nim[i] = mex.size();
    }

    //for (int i = 1; i <= n; ++i)
        //cerr << nim[i] << ' ';
    //cerr << '\n';

    int res = 0;

    for (int i = 1; i <= n; ++i)
        if (s[i - 1] == 'N')
            res xor_eq nim[i];

    //cerr << res << '\n';

    if (not res) return cout << "NIE" << '\n', 0;


    for (int i = 1; i <= n; ++i)
        if (s[i - 1] == 'N')
        {
            for (int j = 1; j <= i; ++j)
            {
                int p = 0;
                for (int k = i - j; k >= 0; k -= j)
                {
                    p xor_eq nim[k];
                    if (not (p xor nim[i] xor res))
                    {
                        for (int l = k; l <= i; l += j)
                            if (l > 0)
                                s[l - 1] = (s[l - 1] == 'N'? 'S' : 'N');
                        reverse(begin(s), end(s));
                        cout << s << '\n';
                        return 0;
                    }
                }
            }
        }
}