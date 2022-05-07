#include <iostream>
#include "DijkstraImplementation.h"
#include <fstream>
#include <list>
#include <algorithm>
#include <set>

#define INF -1

using namespace std;

fstream file;

//==========================================================================================================================================
DijkstraImplementation::DijkstraImplementation(int wF)
{
    // macierz
    whichFile = wF;
    getFileInfo();
    cout<<"Graf z pliku"<<endl;
    printMatrix();
    initTables();
    printDistances();
    dijkstraAlgorithmMatrix(0);
    printDistances();

    // lista
    /*getFileInfo();
    printList();
    initTables();
    dijkstraAlgorithmList(0);
    printDistancesList();*/

}
//==========================================================================================================================================
DijkstraImplementation::~DijkstraImplementation()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] graphMatrix[i];
        graphList[i].clear();
    }

    delete[] distance;
    delete[] distanceList;
    delete[] visited;
    delete[] visitedList;
    delete[] graphMatrix;
    delete[] graphList;
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

void DijkstraImplementation::printDistances()
{   cout<<dijkstraMatrixIterations+1<<". "<<"Odleglosci od wierzcholka 0:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<distance[i]<<" ";
    }
    cout<<endl;
    cout<<dijkstraMatrixIterations+1<<". "<<"Odwiedzone wierzcholki:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<visited[i]<<" ";
    }
    cout<<endl;
}
void DijkstraImplementation::initTables()
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
    dijkstraMatrixIterations = 0;
    dijkstraListIterations = 0;
    distance[0] = 0;
    distanceList[0] = 0;
}
//==========================================================================================================================================

void DijkstraImplementation::addToListVector(int source, int nextE, int edgeV)
{
    ListElement listElement;
    listElement.nextElement = nextE;
    listElement.edgeValue = edgeV;
    graphList[source].push_back(listElement);
}

void DijkstraImplementation::printList()
{
    int i;
    for (i = 0; i < numberOfVertices; i++)
    {
        cout<<i<<" -> ";
        for (const auto& iterate : graphList[i])
        {
            cout<<"("<<iterate.nextElement<<","<<iterate.edgeValue<<")"<<" ";
        }
        cout<<endl;
    }
}
void DijkstraImplementation::printDistancesList()
{   cout<<dijkstraListIterations+1<<". "<<"Odleglosci od wierzcholka 0:"<<endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout<<distanceList[i]<<" ";
    }
    cout<<endl;
}
//==========================================================================================================================================
void DijkstraImplementation::getFileInfo() // odczytywanie wartosci z pliku do nowej tablicy
{

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
        // Inicjalizacja macierzy i listy
        graphMatrix = new int *[numberOfVertices];
        graphList = new list<ListElement>[numberOfVertices];

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
                // macierz
                graphMatrix[i][j] = val;
                graphMatrix[j][i] = val;
                // lista
                addToListVector(i,j,val);
                addToListVector(j,i,val);
            }
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
    if (dijkstraMatrixIterations < numberOfVertices && changes != 0)
    {
        printDistances();
        cout<<"Wykonujemy kolejna petle dla i = "<<smallestAvailableVertex<<endl;
        dijkstraAlgorithmMatrix(smallestAvailableVertex);
    }
    else cout<<"\nKoniec algorytmu Dijkstry dla macierzy\n";
}
//------------------------------------------------------------------------------------------------------------------------------------------
void DijkstraImplementation::dijkstraAlgorithmList(int vertex) // algorytm Dijkstry dla listy
{
    cout<<"Iteracja algorytmu dijkstry"<<endl;
    visitedList[vertex] = true;
    int changes = 0;
    dijkstraListIterations++;
    //printDistancesList();
    set<int> nextVertexSet;
    cout<<"Deklaracja iteratora"<<endl;
    list<ListElement>::iterator ite;
    for (ite = graphList[vertex].begin(); ite != graphList[vertex].end(); ite++)
    {
        nextVertexSet.insert(ite->nextElement);
        cout<<ite->nextElement<<endl;
    }
    ite = graphList[vertex].begin();
    cout<<"Wykonywanie numberOfVertices razy"<<endl;
    //for (int i=0; i<graphList[vertex].size(); i++)
    for (int i=0; i<numberOfVertices; i++)
    //for(it = g.graphList[i].begin(); it != g.adjList[u].end();it++)
    {
        cout<<"Sprawdzenie czy wierzcholek byl odwiedzony"<<endl;  // cout<<"I sprawdzenie czy jest polaczony z wierzcholkiem \"vertex\""<<endl;
        const bool is_in = nextVertexSet.find(i) != nextVertexSet.end();
        if ((visitedList[i]==false) && is_in)
        {
            cout<<"Wierzcholek nie byl odwiedzony wiec sprawdzamy czy mozna relaksowac"<<endl;
            if (((distanceList[vertex]+(ite->edgeValue))<distance[i]) || (distance[i] == INF))
            //for(it = g.graphList[i].begin(); it != g.adjList[u].end();it++)
            {
                cout<<"Relaksacja"<<endl;
                distanceList[i] = distanceList[vertex] + ite->edgeValue;
                changes++;
                ite++;
            }

        }

    }
    cout<<"Wyznaczenie kolejnego wierzcholka do dijkstry"<<endl;
    int smallestAvailableVertex = INF;
    int distSmallestAV = INF;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if ((visitedList[i] == false) && (distanceList[i]>0) && ((distSmallestAV == INF) || (distSmallestAV>distance[i]) ))
        {
            distSmallestAV = distanceList[i];
            smallestAvailableVertex = i;
        }
    }
    if (dijkstraListIterations < numberOfVertices && changes != 0)
    {
        printDistancesList();
        nextVertexSet.clear();
        cout<<"Wykonujemy kolejna petle dla i = "<<smallestAvailableVertex<<endl;
        dijkstraAlgorithmList(smallestAvailableVertex);
    }
    else cout<<"\nKoniec algorytmu Dijkstry dla listy\n";
}
