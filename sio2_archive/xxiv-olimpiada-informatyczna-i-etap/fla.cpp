// Jakub Wasilewski
#include <iostream>

using namespace std;

int ile_przeszkod, X, MIN, MAX;

struct Tprzeszkoda
{
    int dol;
    int gora;
    int x;
    bool parzyste;
};

istream& operator>> (istream& s, Tprzeszkoda& p)
{
    s >> p.x;
    s >> p.dol;
    s >> p.gora;
    p.parzyste = !(p.x % 2);

    if (p.parzyste)
    {
        if (p.dol % 2)
            --p.dol;
        if (p.gora % 2)
            ++p.gora;
    }
    else
    {
        if (!(p.dol % 2))
            --p.dol;
        if (!(p.gora % 2))
            ++p.gora;
    }

    p.gora -= 2;
    p.dol += 2;
    return s;
}

Tprzeszkoda przeszkoda;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> ile_przeszkod >> X;
    X = 0;
    MIN = 0;
    MAX = 0;

    while (ile_przeszkod--)
    {
        cin >> przeszkoda;
        MIN = MIN - (przeszkoda.x - X);
        MAX = MAX + (przeszkoda.x - X);

        if (MAX < przeszkoda.dol || MIN > przeszkoda.gora || przeszkoda.gora < przeszkoda.dol)
        {
            cout << "NIE";
            return 0;
        }

        X = przeszkoda.x;

        if (MIN < przeszkoda.dol)
        {
            MIN = przeszkoda.dol;
        }
        if (MAX > przeszkoda.gora)
        {
            MAX = przeszkoda.gora;
        }
    }
    cout << ((przeszkoda.x + MIN) / 2);
    return 0;
}

