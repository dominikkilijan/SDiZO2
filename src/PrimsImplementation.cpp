#include <iostream>
#include "PrimsImplementation.h"
#include <fstream>
#include <list>
#include <algorithm>

#include "ListElement.h"

#define INF -1

using namespace std;

fstream primsFile;

//==========================================================================================================================================
PrimsImplementation::PrimsImplementation(int wF)
{
    // macierz
    whichFile = wF;
    getFileInfo();
    cout<<"Graf z pliku"<<endl;
    printMatrix();
    initTables();
    printDistances();
    primsAlgorithmMatrix(0);
    printDistances();
    printVisited();
    cout<<"===================================================================================================================="<<endl;
    // lista
    getFileInfo();
    printList();
    initTables();
    printDistancesList();
    primsAlgorithmList(0);
    printDistancesList();
    printVisitedList();

}
//==========================================================================================================================================
PrimsImplementation::~PrimsImplementation()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] graphMatrix[i];
        primsGraphList[i].clear();
    }

    delete[] distance;
    delete[] distanceList;
    delete[] visited;
    delete[] visitedList;
    delete[] graphMatrix;
    delete[] primsGraphList;
}
//==========================================================================================================================================
void PrimsImplementation::createGraphMatrix()
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

void PrimsImplementation::printMatrix()
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

void PrimsImplementation::printDistances()
{   cout<<primsMatrixIterations+1<<". "<<"Odleglosci od wierzcholka 0:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<distance[i]<<" ";
    }
    cout<<endl;
}
void PrimsImplementation::printVisited()
{
    cout<<primsMatrixIterations+1<<". "<<"Odwiedzone wierzcholki:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<visited[i]<<" ";
    }
    cout<<endl;
}
void PrimsImplementation::initTables()
{
    distance = new int[numberOfVertices];
    distanceList = new int[numberOfVertices];
    visited = new bool[numberOfVertices];
    visitedList = new bool[numberOfVertices];

    for (int i = 0; i < numberOfVertices; i++)
    {
        distance[i] = INF;
        distanceList[i] = INF;
        visited[i] = false;
        visitedList[i] = false;
    }
    primsMatrixIterations = 0;
    primsListIterations = 0;
    distance[0] = 0;
    distanceList[0] = 0;
}
//==========================================================================================================================================
void PrimsImplementation::addToListVector(int source, int nextE, int edgeV)
{
    ListElement listElement;
    listElement.nextElement = nextE;
    listElement.edgeValue = edgeV;
    primsGraphList[source].push_back(listElement);
}

void PrimsImplementation::printList()
{
    int i;
    for (i = 0; i < numberOfVertices; i++)
    {
        cout<<i<<" -> ";
        for (const auto& iterate : primsGraphList[i])
        {
            cout<<"("<<iterate.nextElement<<","<<iterate.edgeValue<<")"<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void PrimsImplementation::printDistancesList()
{   cout<<primsListIterations+1<<". "<<"Odleglosci od wierzcholka 0:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<distanceList[i]<<" ";
    }
    cout<<endl;
}
void PrimsImplementation::printVisitedList()
{
    cout<<primsListIterations+1<<". "<<"Odwiedzone wierzcholki:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<visitedList[i]<<" ";
    }
    cout<<endl;
}
//==========================================================================================================================================
void PrimsImplementation::getFileInfo() // odczytywanie wartosci z pliku do nowej tablicy
{

    if (whichFile == 2) primsFile.open("GraphRandom.txt", ios::in);
    else primsFile.open("Graph1.txt", ios::in);

    int val;

    cout<<"Wybrano plik do wczytania"<<endl;
    if(primsFile.is_open())
    {
    primsFile >> numberOfEdges >> numberOfVertices;
    if(primsFile.fail())  cout << "File error - READ SIZE" << endl; // jesli plik jest pusty
    else
    {
        // Inicjalizacja macierzy i listy
        graphMatrix = new int *[numberOfVertices];
        primsGraphList = new list<ListElement>[numberOfVertices];

        createGraphMatrix();

        int i,j,k;
        for(k = 0; k < numberOfEdges; k++)
        {
            primsFile >> i >> j >> val;

            if(primsFile.fail())
            {
                cout << "File error - READ DATA" << endl; // jesli w pliku jest tylko rozmiar>0
                break;
            }
            else
            {
                // macierz
                graphMatrix[i][j] = val;
                graphMatrix[j][i] = val;
                // lista
                addToListVector(i,j,val);
                addToListVector(j,i,val);
            }
        }
    }
    primsFile.close();
    }
    else    cout << "File error - OPEN" << endl; // jesli nie znaleziono pliku o podanej nazwie
}
//==========================================================================================================================================
void PrimsImplementation::primsAlgorithmMatrix(int vertex) // algorytm Primy dla macierzy
{
    visited[vertex] = true;
    int changes = 0;
    primsMatrixIterations++;

    for (int i=0; i<numberOfVertices; i++)
    {
        //cout<<i<<endl;
        if ((visited[i]==false) && (graphMatrix[vertex][i]!=INF))
        {
            if (distance[i] == INF || ((distance[vertex]+graphMatrix[vertex][i])<distance[i]))
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
    if (primsMatrixIterations < numberOfVertices && changes != 0)
    {
        printDistances();
        primsAlgorithmMatrix(smallestAvailableVertex);
    }
    else cout<<"\nKoniec algorytmu Primy dla macierzy\n";
}
//------------------------------------------------------------------------------------------------------------------------------------------
void PrimsImplementation::primsAlgorithmList(int vertex) // algorytm Primy dla listy
{
    visitedList[vertex] = true;
    int changes = 0;
    primsListIterations++;
    vector<int> nextVertexSet;
    // Deklaracja iteratora
    list<ListElement>::iterator ite;
    for (ite = primsGraphList[vertex].begin(); ite != primsGraphList[vertex].end(); ite++)
    {
        nextVertexSet.push_back(ite->nextElement);
    }

    for (int i=0; i<numberOfVertices; i++)
    {
        // Sprawdzenie czy wierzcholek byl odwiedzony i sprawdzenie czy jest polaczony z wierzcholkiem "vertex\"
        bool isIn;
        if (find(nextVertexSet.begin(), nextVertexSet.end(), i) != nextVertexSet.end()) isIn = true;
        else isIn = false;

        if (isIn)
        {
            if ((visitedList[i]==false))
            {
                ite = primsGraphList[vertex].begin();
                while (ite->nextElement != i)
                {
                    ite++;
                }

                if (((distanceList[vertex]+(ite->edgeValue))<distanceList[i]) || (distanceList[i] == INF))
                {
                    distanceList[i] = distanceList[vertex] + ite->edgeValue;
                    changes++;
                }
            }
        }
    }
    // Wyznaczenie kolejnego wierzcholka w algorytmie
    int smallestAvailableVertex = INF;
    int distSmallestAV = INF;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if ((visitedList[i] == false) && (distanceList[i]>0) && ((distSmallestAV == INF) || (distSmallestAV>distanceList[i]) ))
        {
            distSmallestAV = distanceList[i];
            smallestAvailableVertex = i;
        }
    }
    if (primsListIterations < numberOfVertices && changes != 0)
    {
        printDistancesList();
        nextVertexSet.clear();
        primsAlgorithmList(smallestAvailableVertex);
    }
    else cout<<"\nKoniec algorytmu Primy dla listy\n";
}
