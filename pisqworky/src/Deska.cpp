#include <iostream>
#include "Deska.h"

using namespace std;


void Deska::clear()
{
    for (int i=0; i<VelPol; i++)
    {
        for (int j=0; j<VelPol; j++)
        {
            deska[i][j]='-';
        }
    }
    count=0;
}



Deska::Deska()
{
    clear();
}

void Deska::print()
{
    cout <<"   A  B  C  D  E  F  G  H  I  J  K  L  M  N  O";

    cout <<endl;
    for (int i=0; i<VelPol; i++)
    {
        string s=i < 10?"  ":" ";
        cout << i << s;
        for (int j=0; j<VelPol; j++)
        {
            cout << deska[i][j]<<"  ";
        }
        cout << i;
        cout << endl << endl;
    }
    cout <<"   A  B  C  D  E  F  G  H  I  J  K  L  M  N  O";

    cout<<endl;
}
bool Deska::prazdne(int x, int y)
{
    if (x>=0 && x<=VelPol-1 && y>=0 && y<=VelPol-1 && deska[x][y]=='-')
    {
        return true;
    }
    return false;
}


void Deska::hodnota(int x, int y, char z)
{
    deska[x][y]=z;
    if (z== '-')
    {
        count--;
    }
    else
    {
        count++;
    }
    return;
}

bool Deska::vyhra(int x, int y)
{
    return radek(x,y) || sloupec(x,y) || diagonala1(x,y) || diagonala2(x,y);
}

bool Deska::radek(int x, int y)
{
    int i=1;
    int j=1;
    while (y-i>=0 && deska[x][y-i]==deska[x][y])
    {
        j++;
        i++;
    }
    i=1;
    while (y+i<=VelPol-1 && deska[x][y+i]==deska[x][y])
    {
        j++;
        i++;
    }
    return (j>=VelVyh);
}

bool Deska::sloupec(int x, int y)
{

    int i=1;
    int j=1;

    while (x-i>=0 && deska[x-i][y]==deska[x][y])
    {
        j++;
        i++;
    }
    i=1;
    while (x+i<=VelPol-1 && deska[x+i][y]==deska[x][y])
    {
        j++;
        i++;
    }
    return (j>=VelVyh);
}

bool Deska::diagonala1(int x, int y)
{

    int i=1;
    int j=1;
    while (x-i>=0 && y-i>=0 && deska[x-i][y-i]==deska[x][y])
    {
        j++;
        i++;
    }
    i=1;
    while (x+i<=VelPol-1 && y+i <= VelPol-1 && deska[x+i][y+i]==deska[x][y])
    {
        j++;
        i++;
    }
    return (j>=VelVyh);
}

bool Deska::diagonala2(int x, int y)
{
    int i=1;
    int j=1;
    while (x-i>=0 && y+i<=VelPol-1 && deska[x-i][y+i]==deska[x][y])
    {
        j++;
        i++;
    }
    i = 1;
    while (x+i<=VelPol-1 && y-i>=0 && deska[x+i][y-i]==deska[x][y])
    {
        j++;
        i++;
    }
    return (j>=VelVyh);
}


char Deska::nacti(int i, int j){
	return deska[i][j];
}


bool Deska::remiza(){
    if(count==VelPol*VelPol) {
        return true;
    }
        return false;
    }


int Deska::pocitej(){
	return count;
}

string Deska::toString(){
	string s="";
	for (int i=0; i<VelPol; i++){
		for (int j=0 ; j<VelPol; j++){
			s+= nacti(i, j);
		}
	}
	return s;
}
