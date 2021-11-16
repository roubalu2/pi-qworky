#include "Hra.h"
#include "Deska.h"
#include "Pocitac_rand.h"
#include "Pocitac_ok.h"
#include "Pocitac_hard.h"
#include <vector>
#include <iostream>


#include <regex>

using namespace std;

Hra::Hra()
{
    deska.clear();
}

void Hra::Konzole ()
{
    deska.clear ();
    int ob = 1;
    cout<<"Tak na co si veris? ty srabe = 1, easy = 2, hard (konecne slusna obtiznost) = cokoliv ostatniho" << endl;
    cin>> ob;

    Pocitac_ok pocitac_ok;
    Pocitac_rand pocitac_rand;
    Pocitac_hard pocitac_hard;
    bool flag = true;
    int hod = 1;
    int x = -1, y = -1;
    vector<int> v;

    //deska.hracSymbol ('X');
    //deska.pocitacSymbol ('O');

    cout << "Hrajes s X-em tak nebrec.\nChces hrat prvni? ano/ne" << endl;
    string poradi;
    cin >> poradi;

    if (poradi == "ano")
    {
        hod = 1;
        cout << "Se bojis vid? :D Proto sis vybral hrat prvni." << endl;

    }
    else
    {
        cout << "Ty se toho nebojis co? Jen pockej..." << endl;
        hod = 2;
    }
    deska.print();
    while (flag)
    {
        cout << endl;

        if (hod == 1)
        {
            cout << "Tak se ukaz.\nPrvni zadej pismeno a pak cislo. To snad jeste zvladnes ne?" << endl;
            string souradnice;
            cin >> souradnice;
            string data2= souradnice;

            string xreg;
            string yreg;

            std::regex tah("^\\d+\\w$|^\\w\\d+$");
            if(std::regex_match(souradnice, tah)==1)
            {
                std::regex cislo("\\d+");
                std::regex pismeno("\\w");
                smatch cislomatch;
                smatch pismenomatch;
                regex_search(souradnice,cislomatch,cislo);
                regex_search(souradnice,pismenomatch,pismeno);
                for(auto i:cislomatch)
                    xreg=i;
                for(auto i:pismenomatch)
                    yreg = i;


                x= atoi(xreg.c_str());
                char ychar =tolower(yreg.c_str()[0]);
                y=ychar-97;

            }

            /*
                        if(souradnice.find("14")==true)
                        {
                            x=14;
                        }
                        else if (souradnice.find("13")==true)
                        {
                            x=13;
                        }
                        else if (souradnice.find("12")==true)
                        {
                            x=12;
                        }
                        else if (souradnice.find("11")==true)
                        {
                            x=11;
                        }
                        else if (souradnice.find("10")==true)
                        {
                            x=10;
                        }
                        else if (souradnice.find("9")==true)
                        {
                            x=9;
                        }
                        else if (souradnice.find("8")==true)
                        {
                            x=8;
                        }
                        else if (souradnice.find("7")==true)
                        {
                            x=7;
                        }
                        else if (souradnice.find("6")==true)
                        {
                            x=6;
                        }
                        else if (souradnice.find("5")==true)
                        {
                            x=5;
                        }
                        else if (souradnice.find("4")==true)
                        {
                            x=4;
                        }
                        else if (souradnice.find("3")==true)
                        {
                            x=3;
                        }
                        else if (souradnice.find("2")==true)
                        {
                            x=2;
                        }
                        else if (souradnice.find("1")==true)
                        {
                            x=1;
                        }
                        else if (souradnice.find("0")==true)
                        {
                            x=0;
                        }

                         if (souradnice.find("A") != std::string::npos || souradnice.find ("a") != std::string::npos)
                        {
                            y=0;
                        }
                        else if (souradnice.find("B") ==true || souradnice.find ("b")==true)
                        {
                            y=1;
                        }
                        else if (souradnice.find("C") ==true|| souradnice.find ("c")==true)
                        {
                            y=2;
                        }
                        else if (souradnice.find("D")==true || souradnice.find ("d")==true)
                        {
                            y=3;
                        }
                        else if (souradnice.find("E") ==true || souradnice.find ("e")==true)
                        {
                            y=4;
                        }
                        else if (souradnice.find("F")==true || souradnice.find ("f")==true)
                        {
                            y=5;
                        }
                        else if (souradnice.find("G")==true || souradnice.find ("g")==true)
                        {
                            y=6;
                        }
                        else if (souradnice.find("H") ==true || souradnice.find ("h")==true)
                        {
                            y=7;
                        }
                        else if (souradnice.find("I")==true || souradnice.find ("i")==true)
                        {
                            y=8;
                        }
                        else if (souradnice.find("J")==true || souradnice.find ("j")==true)
                        {
                            y=9;
                        }
                        else if (souradnice.find("K") ==true|| souradnice.find ("k")==true)
                        {
                            y=10;
                        }
                        else if  (souradnice.find("L")==true || souradnice.find ("l")==true)
                        {
                            y=11;
                        }
                        else if (souradnice.find("M")==true || souradnice.find ("m")==true)
                        {
                            y=12;
                        }
                        else if (souradnice.find("N") ==true|| souradnice.find ("n")==true)
                        {
                            y=13;
                        }
                        else if (souradnice.find("O")==true || souradnice.find ("o")==true);
                        {
                            y=14;
                        }

                        cout << souradnice << "   wtf ?" << endl;
            */

        }
        else
        {
            if (ob == 1)
            {
                v = pocitac_rand.tah(deska);

                x = v[0];
                y = v[1];
            }
            else if (ob ==2)
            {
                v = pocitac_ok.tah(deska);

                x = v[0];
                y = v[1];

            }
            else {
                v = pocitac_hard.tah(deska);

                x = v[0];
                y = v[1];

            }

        }

        //overeni spravnosti tahu
        if (!deska.prazdne( x, y))
        {
            cout << endl << "Pokus dobrej, ale neplati. Budu hodnej a dam ti jeste sanci." << endl;
            continue;

        }
        else
        {
            deska.hodnota(x,y,nactiSymbol(hod));
            deska.print();
            if (hod == 1)
            {
                cout << "Tvuj tah je: ("<<x<<", "<<y<<") Bud v klidu, stejne nakonec prohrajes."<<endl;

            }
            else
            {
                cout << "Muj tah je: ("<<x<<", "<<y<<")  Dobry co?"<<endl;
            }
        }
//kontrola vyhry
        if (deska.vyhra(x,y))
        {
            deska.print();
            if (hod == 1)
            {
                cout<<"Fajn priznam to no... Proste si vyhral, ale nebudem to moc okecavat."<<endl;

            }
            else
            {
                cout<< "JSEEEM LEEEPSIII A VYHRAAAAL JSEEEEM!!!!!"<<endl;
            }
            break;
        }
        else
        {
            hod= 3 - hod;
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
void Hra::spustit()
{
    bool flag = true;
    string x;
    while (flag)
    {
        Konzole();
        cout << "Tak co? Dame dalsi hru? ano/ne"<<endl;
        cin >> x;
        if (x == "ano")
        {
            flag = true;
        }
        else
        {
            flag = false;
            cout << "------------------------------------------------------"<<endl;
        }
    }
}







