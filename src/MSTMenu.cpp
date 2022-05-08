#include <iostream>
#include "MSTMenu.h"
#include "Menu.h"
#include "PrimsImplementation.h"

using namespace std;

MSTMenu::MSTMenu(int fileChoice)
{
        work = 0;

        while(work == 0) // ciagle wyswietlaj menu
        {
        int choice=0; // wybor struktury
        cout << endl<<"MST MENU:"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "1. Algorytm Prima "<<endl;
        cout << "2. Algorytm Kruskala "<<endl;
        cout << "3. Powrot do menu glownego "<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "Wybor: ";
        cin >> choice;
        system("cls"); // czyszczenie konsoli

        switch (choice)
        {
        case 1:
            {
            cout<<"Algorytm Prima"<<endl;
            PrimsImplementation prim(fileChoice);
            //delete this;
            }
            break;

        case 2:
            {
            cout<<"Algorytm Kruskala"<<endl;
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

MSTMenu::~MSTMenu()
{
    //dtor
}
