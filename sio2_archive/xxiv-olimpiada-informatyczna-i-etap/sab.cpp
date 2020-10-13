//Jakub Wasilewski
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double naj_mianownik, naj_licznik;
int ile_pracownikow, bunt;
int p3;
double odp;

struct w
{
    int licznik = 1, mianownik = 1;
    w* ojciec;
    vector <w*> dzieci;

}*drzewo;

void wartosci (w* pracownik)
{
    for (int i = 0; i < pracownik->dzieci.size(); ++i)
    {
        wartosci (pracownik->dzieci[i]);
        pracownik->licznik += pracownik->dzieci[i]->licznik;
    }
}
void ulamki (w* pracownik)
{
    if (pracownik->ojciec)
        pracownik->mianownik = pracownik->ojciec->licznik - 1;
    for (int i = 0; i < pracownik->dzieci.size(); ++i)
        ulamki (pracownik->dzieci[i]);
}
double morale (w* pracownik)
{
    if (pracownik->dzieci.empty())
        return (1 / (double)pracownik->mianownik);
    double p, p2 = 0;
    for (int i = 0; i < pracownik->dzieci.size(); ++i)
    {
        if ((p = morale(pracownik->dzieci[i])) > p2)
            p2 = p;
    }
    if (pracownik->licznik > bunt)
    {
        return p2;
    }
    else
    {
       p = (double)pracownik->licznik / pracownik->mianownik;
       return p < p2? p : p2;
    }


}

int main()
{
    ios_base::sync_with_stdio(0);
    cin >> ile_pracownikow >> bunt;
    drzewo = new w [ile_pracownikow + 1];
    for (int i = 2; i <= ile_pracownikow; ++i)
    {
        cin >> p3;
        drzewo[i].ojciec = &drzewo[p3];
        drzewo[p3].dzieci.push_back(&drzewo[i]);
    }
    wartosci(&drzewo[1]);
    ulamki (&drzewo[1]);
    if (ile_pracownikow <= bunt)
    cout << "0.0000000000";
    else
    cout << fixed <<setprecision(10) << morale(&drzewo[1]);

    delete [] drzewo;
}
