#include<iostream>
#include<fstream>
#include<math.h>
#include<time.h>
#include<bits/stdc++.h>

#include "Menu.h"
#include "ShortestPathMenu.h"
#include "MSTMenu.h"
#include "DijkstraImplementation.h"


using namespace std;

int work;
fstream fileWrite;

struct EdgeOptions
{
    int v1;
    int v2;
};

Menu::Menu()
{
        work = 0;

        while(work == 0) // ciagle wyswietlaj menu
        {
        int choice=0; // wybor struktury
        cout << endl<<"MENU GLOWNE:"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "1. Najkrotsza sciezka "<<endl;
        cout << "2. MST "<<endl;
        cout << "3. Koniec programu "<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "Wybor: ";
        cin >> choice;
        //system("cls"); // czyszczenie konsoli

        if (choice == 1 || choice == 2)
        {
        cout<<"Wczytac graf:"<<endl;
        cout<<"1. Z pliku"<<endl;
        cout<<"2. Wygenerowac losowo"<<endl;
        cin>>fileChoice;

        if (fileChoice == 2)
        {
            cout<<"Ile wierzcholkow"<<endl;
            cin>>numVert;
            cout<<"Jaka gestosc?"<<endl;
            cout<<"1. 25%"<<endl;
            cout<<"2. 50%"<<endl;
            cout<<"3. 75%"<<endl;
            cout<<"4. 99%"<<endl;
            cin>>edgeDensity;
            srand(time(NULL));
            generateRandomGraph();
        }
        }

        switch (choice)
        {
        case 1:
            {
            cout<<"fileChoice = "<<fileChoice<<endl;
            DijkstraImplementation dijkstra(fileChoice);
            ShortestPathMenu shortMenu;
            //delete this;
            }
            break;

        case 2:
            {
            MSTMenu mstMenu;
            delete this;
            }
            break;

        case 3:
            work=1;
            exit(0);

            break;
        default:
            cout<<"Nieprawidlowy numer polecenia. Sprobuj jeszcze raz"<<endl;
        }

    }
}

Menu::~Menu()
{

}

void Menu::generateRandomGraph()
{
    cout<<"Generowanie losowego grafu"<<endl;
    int numEdgesMax;
    //numEdgesMax = binomialCoefficients(numVert, 2);
    numEdgesMax = numVert*(numVert-1)/2;

    switch (edgeDensity)
    {
    case 1:
            {
            numEdges = ceil(0.25 * numEdgesMax);
            }
            break;
    case 2:
            {
            numEdges = ceil(0.5 * numEdgesMax);
            }
            break;
    case 3:
            {
            numEdges = ceil(0.75 * numEdgesMax);
            }
            break;
    case 4:
            {
            numEdges = ceil(0.99 * numEdgesMax);
            }
            break;
    default:
            cout<<"Nieprawidlowy numer polecenia!"<<endl;
    }

    cout<<numEdges<<" "<<numVert<<endl;
    cout<<endl;
    int edge;
    edgeOptionsTable = new EdgeOptions[numEdgesMax];
    int i,j,k;
    for (i = 0; i < numEdgesMax; i++)
    {

        for (j = i+1; j < numVert; j++)
        {
            edgeOptionsTable[k].v1 = i;
            edgeOptionsTable[k].v2 = j;
            k++;
        }
    }
    for (int i = 0; i < numEdgesMax; i++)
    {

   for (int m = numEdges; m>0; m--)
    {
        //get swap index
        int n = rand()%m;
        //swap p[i] with p[j]
        EdgeOptions temp;
        temp = edgeOptionsTable[m];
        edgeOptionsTable[m] = edgeOptionsTable[n];
        edgeOptionsTable[n] = temp;
    }


        //edge = rand()%100+1;

    }
    for (int i = 0; i < numEdgesMax; i++)
    {
        cout<<edgeOptionsTable[i].v1<<" "<<edgeOptionsTable[i].v2<<endl;
    }




    delete[] edgeOptionsTable;
}
/*int Menu::binomialCoefficients(int n, int k) {
   if (k == 0 || k == n) return 1;
   return (binomialCoefficients(n - 1, k - 1) + binomialCoefficients(n - 1, k));
}*/

