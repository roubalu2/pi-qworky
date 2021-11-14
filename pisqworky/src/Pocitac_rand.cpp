#include "Pocitac_rand.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Deska.h"
#include <cstdlib>
#include <ctime>

Pocitac_rand::Pocitac_rand()
{

}

vector<int> Pocitac_rand::tah(Deska & deska) {
    int i = 0;
    int j = 0;
    vector<int> v(2);
    srand((unsigned) time(NULL));

    do {
        i = rand()%15;
        j = rand()%15;
    } while (deska.prazdne(i,j) == false);

    v[0]=i;
    v[1]=j;

    return v;

}


