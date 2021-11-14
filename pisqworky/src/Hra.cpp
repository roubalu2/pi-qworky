#include "Hra.h"
#include "Deska.h"
#include "Pocitac_rand.h"
#include <vector>
#include <iostream>

using namespace std;

Hra::Hra()
{
    deska.clear();
}

void Hra::Konzole ()
{
    deska.clear ();
    Pocitac_rand pocitac_rand;
    bool flag = true;
    int hod = 1;
    int x = -1, y = -1;
    vector<int> v;

    //deska.hracSymbol ('X');
    //deska.pocitacSymbol ('O');

    cout << "Vas symbol je X./nPrejete si hrat jako prvni? ano/ne" << endl;
    string poradi;
    cin >> poradi;

    if (poradi == "ano")
    {
        hod = 1;
        cout << "Hrajes jako prvni." << endl;

    }
    else
    {
        cout << "Hrajes jako druhy." << endl;
        hod = 2;
    }
    deska.print();
    while (flag)
    {
        cout << endl;
        if (hod == 1)
        {
            cout << "Jste na tahu./nZadejte souradnice vaseho tahu." << endl;
            string souradnice;
            cin >> souradnice;
            if (souradnice.find("A") || souradnice.find ("a") )
            {
                x=0;
            }
            else if (souradnice.find("B") || souradnice.find ("b"))
            {
                x=1;
            }
            else if (souradnice.find("C") || souradnice.find ("c"))
            {
                x=2;
            }
            else if (souradnice.find("D") || souradnice.find ("d"))
            {
                x=3;
            }
            else if (souradnice.find("E") || souradnice.find ("e"))
            {
                x=4;
            }
            else if (souradnice.find("F") || souradnice.find ("f"))
            {
                x=5;
            }
            else if (souradnice.find("G") || souradnice.find ("g"))
            {
                x=6;
            }
            else if (souradnice.find("H") || souradnice.find ("h"))
            {
                x=7;
            }
            else if (souradnice.find("I") || souradnice.find ("i"))
            {
                x=8;
            }
            else if (souradnice.find("J") || souradnice.find ("j"))
            {
                x=9;
            }
            else if (souradnice.find("K") || souradnice.find ("k"))
            {
                x=10;
            }
            else if  (souradnice.find("L") || souradnice.find ("l"))
            {
                x=11;
            }
            else if (souradnice.find("M") || souradnice.find ("m"))
            {
                x=12;
            }
            else if (souradnice.find("N") || souradnice.find ("n"))
            {
                x=13;
            }
            else (souradnice.find("O") || souradnice.find ("o"));
            {
                x=14;
            }
            if(souradnice.find("14"))
            {
                y=14;
            }
            else if (souradnice.find("13"))
            {
                y=13;
            }
            else if (souradnice.find("12"))
            {
                y=12;
            }
            else if (souradnice.find("11"))
            {
                y=11;
            }
            else if (souradnice.find("10"))
            {
                y=10;
            }
            else if (souradnice.find("9"))
            {
                y=9;
            }
            else if (souradnice.find("8"))
            {
                y=8;
            }
            else if (souradnice.find("7"))
            {
                y=7;
            }
            else if (souradnice.find("6"))
            {
                y=6;
            }
            else if (souradnice.find("5"))
            {
                y=5;
            }
            else if (souradnice.find("4"))
            {
                y=4;
            }
            else if (souradnice.find("3"))
            {
                y=3;
            }
            else if (souradnice.find("2"))
            {
                y=2;
            }
            else if (souradnice.find("1"))
            {
                y=1;
            }
            else if (souradnice.find("0"))
            {
                y=0;
            }
        }
        else
        {

            v = pocitac_rand.tah(deska);
            x = v[0];
            y =v[1];

        }

        //overeni spravnosti tahu
        if (!deska.prazdne( x, y))
        {
            cout << endl << "Tah je neplatny. Zadejte jine souradnice tahu." << endl;
            continue;

        }
        else
        {
            deska.hodnota(x,y,nactiSymbol(hod));
            deska.print();
            if (hod == 1)
            {
                cout << "Souradnice vaseho tahu jsou: ("<<x<<", "<<y<<") "<<endl;

            }
            else
            {
                cout << "Souradnice tahu pocitace jsou: ("<<x<<", "<<y<<") "<<endl;
            }
        }
    }




}

char Hra::nactiSymbol(int hod)
{
    if (hod == 1)
    {
        char X;
        X = 'X';
        return X;
    }
    else
    {
        char O;
        O = 'O';
        return O;
    }
}
void Hra::spustit(){
	bool flag = true;
	char x;
	while (flag){
		Konzole();
		cout << "Prejete si hrat dalsi hru? ano/ne"<<endl;
		cin >> x;
		if (x == 'N' || x == 'n'){
			flag = false;
		}else{
			cout << "------------------------------------------------------"<<endl;
		}
	}
}







