#ifndef DESKA_H
#define DESKA_H

#include <iostream>

using namespace std;

const int VelPol = 15; //pole 15x15
const int VelVyh = 5;

class Deska
{
public:
    Deska();
    void clear();
    void print();
    bool prazdne(int, int);
    void hodnota(int, int, char);
    char nacti (int, int);
    bool vyhra(int, int);
    int pocitej();
    bool radek(int, int);
    bool sloupec(int, int);
    bool diagonala1(int, int);
    bool diagonala2(int, int);
string toString();
protected:

private:
    char deska [VelPol][VelPol];
    int count;



};

#endif // DESKA_H
