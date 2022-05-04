#include <iostream>
#include "DijkstraImplementation.h"
#include <fstream>

using namespace std;

fstream file;

DijkstraImplementation::DijkstraImplementation(int wF)
{

    whichFile = wF;
    getFileInfo();
    cout<<"Graf z pliku"<<endl;
    printMatrix();

}

DijkstraImplementation::~DijkstraImplementation()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] graphMatrix[i];
    }

    delete[] graphMatrix;
}

void DijkstraImplementation::createGraphMatrix()
{
    int i,j;
    for (i = 0; i < numberOfVertices; i++)
    {

        graphMatrix[i] = new int [numberOfVertices];
        for (j = 0; j < numberOfVertices; j++)
        {
            graphMatrix[i][j] = 0;
        }
    }
}
void DijkstraImplementation::printMatrix()
{
    int i,j;
    for (i = 0; i < numberOfVertices; i++)
    {
        for (j = 0; j < numberOfVertices; j++)
        {
            if (graphMatrix[i][j] < 10) cout<<"  ";
            else if (graphMatrix[i][j] > 10) cout<<" ";
            cout<<graphMatrix[i][j];
        }
        cout<<endl;
    }
}
void DijkstraImplementation::getFileInfo() // odczytywanie wartosci z pliku do nowej tablicy
{
    if (whichFile == 1) file.open("Graph1.txt", ios::in);
    else if (whichFile == 2) file.open("GraphRandom.txt", ios::in);

    int val;


    if(file.is_open())
    {
    file >> numberOfEdges >> numberOfVertices;
    if(file.fail())  cout << "File error - READ SIZE" << endl; // jesli plik jest pusty
    else
    {
        graphMatrix = new int *[numberOfVertices];
        createGraphMatrix();

        int i,j,k;
        for(k = 0; k < numberOfEdges; k++)
        //while (!file.eof())
        {
            file >> i >> j >> val;

            if(file.fail())
            {
                cout << "File error - READ DATA" << endl; // jesli w pliku jest tylko rozmiar>0
                break;
            }
            else
            {
                graphMatrix[i][j] = val;
                graphMatrix[j][i] = val;
            }

        }
    }
    file.close();
    }
    else    cout << "File error - OPEN" << endl; // jesli nie znaleziono pliku o podanej nazwie
}
void DijkstraImplementation::dijkstraAlgorithmMatrix() // algorytm Dijkstry dla macierzy
{

}
void DijkstraImplementation::dijkstraAlgorithmList() // algorytm Dijkstry dla listy
{

}
