#ifndef HRA_H
#define HRA_H
#include <iostream>
#include <stdio.h>
#include <vector>

#include "Deska.h"
#include "Pocitac_rand.h"
#include "Pocitac_ok.h"
#include "Pocitac_hard.h"

class Hra
{
public:
    Hra();
    void Konzole();
    char nactiSymbol(int);
    void spustit();

protected:

private:
    Deska deska;
};

#endif // HRA_H
