#include "kol.h"
using namespace std;

namespace
{
    constexpr int nax = 544;
}

int main()
{
    init();

    for (int i = 0; i < nax; ++i)
    {
        vector< int > wro;
        for (int j = (i & 1? i - 3 : i - 1); j >= 0; j -= 2)
            wro.push_back(j);
        create(wro);
    }

    vector< int > pok(nax);
    for (int i = 0; i < nax; ++i)
        pok[i] = (i & 1);
    
    answer(pok);
}