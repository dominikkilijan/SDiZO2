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
    initTables();
    printDistances();
    dijkstraAlgorithmMatrix(0);
    printDistances();


}

DijkstraImplementation::~DijkstraImplementation()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] graphMatrix[i];
    }

    delete[] distance;
    delete[] visited;
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
            if (i == j) graphMatrix[i][j] = 0;
            else graphMatrix[i][j] = -1;
            //graphMatrix[i][j] = -1;
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
            if (graphMatrix[i][j] < 10 && graphMatrix[i][j] >= 0) cout<<"  ";
            else if (graphMatrix[i][j] > 10 || graphMatrix[i][j] == -1) cout<<" ";
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
void DijkstraImplementation::dijkstraAlgorithmMatrix(int vertex) // algorytm Dijkstry dla macierzy
{
    visited[vertex] = true;
    int changes = 0;
    dijkstraMatrixIterations++;

    for (int i=0; i<numberOfVertices; i++)
    {
        if ((visited[i]==false) && (graphMatrix[vertex][i]!=-1))
        {
            if (((distance[vertex]+graphMatrix[vertex][i])<distance[i]) || (distance[i] == -1))
            {
                distance[i] = distance[vertex] + graphMatrix[vertex][i];
                changes++;
            }
        }
    }
    int smallestAvailableVertex = -1;
    int distSmallestAV = -1;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if ((visited[i] == false) && (distance[i]>0) && ((distSmallestAV>distance[i]) || (distSmallestAV == -1)))
        {
            distSmallestAV = distance[i];
            smallestAvailableVertex = i;
            //changes++;
        }
    }
    if (dijkstraMatrixIterations < numberOfVertices && changes != 0)
    {
        printDistances();
        dijkstraAlgorithmMatrix(smallestAvailableVertex);
    }
    else cout<<"\nKoniec algorytmu Dijkstry dla macierzy\n";
}
void DijkstraImplementation::printDistances()
{   cout<<"Odleglosci od wierzcholka 0:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<distance[i]<<" ";
    }
    cout<<endl;
}
void DijkstraImplementation::initTables()
{
    distance = new int[numberOfVertices];
    visited = new bool[numberOfVertices];

    for (int i = 0; i < numberOfVertices; i++)
    {
        distance[i] = -1;
        visited[i] = false;
    }
    dijkstraMatrixIterations = 0;
    distance[0] = 0;
}
void DijkstraImplementation::dijkstraAlgorithmList() // algorytm Dijkstry dla listy
{

}
