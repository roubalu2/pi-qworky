#include "Pocitac_ok.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Deska.h"
#include <cstdlib>
#include <ctime>


Pocitac_ok::Pocitac_ok()
{
    //ctor
}

int xx = 7;
int yy = 7;

vector<int> Pocitac_ok::tah(Deska & deska) {

    int i = 0;
    int j = 0;
    vector<int> v(2);
    srand((unsigned) time(NULL));


    do {
        i = rand()%15;
        j = rand()%15;

    } while (!(deska.prazdne(i,j) == true && abs(xx-i)<=1 && abs(yy-j)<=1));

    v[0]=i;
    v[1]=j;
    xx=i;
    yy=j;


    return v;

}
