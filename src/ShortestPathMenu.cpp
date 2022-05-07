#include <iostream>
#include "ShortestPathMenu.h"
#include "Menu.h"

using namespace std;

ShortestPathMenu::ShortestPathMenu()
{
        work = 0;

        while(work == 0) // ciagle wyswietlaj menu
        {
        int choice=0; // wybor struktury
        cout << endl<<"SHORTEST PATH MENU:"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "1. Algorytm Dijkstry "<<endl;
        cout << "2. Algorytm Bellmana-Forda "<<endl;
        cout << "3. Powrot do menu glownego "<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "Wybor: ";
        cin >> choice;
        //system("cls"); // czyszczenie konsoli

        switch (choice)
        {
        case 1:
            {
            cout<<"Algorytm Dijkstry"<<endl;
            //delete this;
            }
            break;

        case 2:
            {
            cout<<"Algorytm Bellmana-Forda"<<endl;
            system("cls"); // czyszczenie konsoli
            //delete this;
            }
            break;

        case 3:
            {
            Menu menu; // powrot do menu glownego
            delete this;
            }
            break;
        default:
            cout<<"Nieprawidlowy numer polecenia. Sprobuj jeszcze raz"<<endl;
        }

    }
}

ShortestPathMenu::~ShortestPathMenu()
{
    //dtor
}
