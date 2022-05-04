#include <iostream>
#include "DijkstraImplementation.h"
#include <fstream>
#include <list>

#define INF -1

using namespace std;

fstream file;

//==========================================================================================================================================
DijkstraImplementation::DijkstraImplementation(int wF)
{
    // macierz
    whichFile = wF;
    /*getFileInfo();
    cout<<"Graf z pliku"<<endl;
    printMatrix();
    initTables();
    printDistances();
    dijkstraAlgorithmMatrix(0);
    printDistances();*/

    // lista
    getFileInfo();
    //createGraphList();
    printList();


}
//==========================================================================================================================================
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
//==========================================================================================================================================
void DijkstraImplementation::createGraphMatrix()
{
    int i,j;
    for (i = 0; i < numberOfVertices; i++)
    {

        graphMatrix[i] = new int [numberOfVertices];
        for (j = 0; j < numberOfVertices; j++)
        {
            if (i == j) graphMatrix[i][j] = 0;
            else graphMatrix[i][j] = INF;
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
            else if (graphMatrix[i][j] > 10 || graphMatrix[i][j] == INF) cout<<" ";
            cout<<graphMatrix[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
//==========================================================================================================================================
void DijkstraImplementation::getFileInfo() // odczytywanie wartosci z pliku do nowej tablicy
{
    //if (whichFile == 1) file.open("Graph1.txt", ios::in);
    //else if (whichFile == 2) file.open("GraphRandom.txt", ios::in);

    if (whichFile == 2) file.open("GraphRandom.txt", ios::in);
    else file.open("Graph1.txt", ios::in);

    int val;

    cout<<"Wybrano plik do wczytania"<<endl;
    if(file.is_open())
    {
    file >> numberOfEdges >> numberOfVertices;
    if(file.fail())  cout << "File error - READ SIZE" << endl; // jesli plik jest pusty
    else
    {
        cout<<"Inicjalizacja macierzy i listy"<<endl;
        graphMatrix = new int *[numberOfVertices];
        //vector<vector<ListElement>> graphList;
        //graphList = new ListElement *[numberOfVertices];

        createGraphMatrix();
        createGraphList();

        cout<<"Po inicjalizacji listy"<<endl;

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

                cout<<"Wpisywanie wartosci do listy"<<endl;
                //graphList[i][j].size();
                graphList[i][graphList[i].size()].nextElement = j;
                //graphList[i][m].edgeValue = val;
                cout<<"Po iteracji wpisywania wartosci"<<endl;
            }
        cout<<"Koniec calego wpisywania"<<endl;
        }
    }
    file.close();
    }
    else    cout << "File error - OPEN" << endl; // jesli nie znaleziono pliku o podanej nazwie
}
//==========================================================================================================================================
void DijkstraImplementation::dijkstraAlgorithmMatrix(int vertex) // algorytm Dijkstry dla macierzy
{
    visited[vertex] = true;
    int changes = 0;
    dijkstraMatrixIterations++;

    for (int i=0; i<numberOfVertices; i++)
    {
        if ((visited[i]==false) && (graphMatrix[vertex][i]!=INF))
        {
            if (((distance[vertex]+graphMatrix[vertex][i])<distance[i]) || (distance[i] == INF))
            {
                distance[i] = distance[vertex] + graphMatrix[vertex][i];
                changes++;
            }
        }
    }
    int smallestAvailableVertex = INF;
    int distSmallestAV = INF;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if ((visited[i] == false) && (distance[i]>0) && ((distSmallestAV>distance[i]) || (distSmallestAV == INF)))
        {
            distSmallestAV = distance[i];
            smallestAvailableVertex = i;
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
{   cout<<dijkstraMatrixIterations+1<<". "<<"Odleglosci od wierzcholka 0:"<<endl;
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
        distance[i] = INF;
        visited[i] = false;
    }
    dijkstraMatrixIterations = 0;
    distance[0] = 0;
}
//==========================================================================================================================================
void DijkstraImplementation::dijkstraAlgorithmList() // algorytm Dijkstry dla listy
{

}
void DijkstraImplementation::addToListVector(int i, int j, int nextNode, int edge)
{
    //graphList[i][j].nextElement.push_back(nextNode);
}
void DijkstraImplementation::createGraphList()
{
    cout<<"Poczatek createGraphList"<<endl;
    int i,j;
    for (i = 0; i < numberOfVertices; i++)
    {
        vector<ListElement> graphList[i];
    }
    cout<<"Koniec createGraphList"<<endl;
}
void DijkstraImplementation::printList()
{
    cout<<"Poczatek printList"<<endl;
    int i,j;
    for (i = 0; i < numberOfVertices; i++)
    {
        cout<<i<<" -> ";
        for (j = 0; j < graphList[i].size(); j++)
        {
            cout<<graphList[i][j].nextElement<<","<<graphList[i][j].edgeValue<<" ";
        }
        cout<<endl;
    }
    cout<<"Koniec printList"<<endl;
}
