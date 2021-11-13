#ifndef DESKA_H
#define DESKA_H

#include <iostream>

using namespace std;

const int VelPol = 15; //pole 15x15


class Deska
{
    public:
        Deska();
        void clear();
        void print();
    protected:

    private:
        char deska [VelPol][VelPol];
        int count;
        bool prazdne(int, int);
        void Hodnota(int, int, char);


};

#endif // DESKA_H
