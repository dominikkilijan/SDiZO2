#ifndef DIJKSTRAIMPLEMENTATION_H
#define DIJKSTRAIMPLEMENTATION_H

#include <list>
#include <vector>
#include "ListElement.h"

using namespace std;


class DijkstraImplementation
{
    public:

        DijkstraImplementation(int);
        virtual ~DijkstraImplementation();

        void createGraphMatrix();
        void createGraphList();

        void printMatrix();
        void printList();
        void getFileInfo();
        void dijkstraAlgorithmMatrix(int);
        void dijkstraAlgorithmList(int);
        void printDistances();
        void printDistancesList();
        void printPrevious();
        void printPreviousList();
        void printVisited();
        void printVisitedList();
        void initTables();
        void addToListVector(int,int,int);
        //int

    protected:

    private:
        int numberOfVertices;
        int numberOfEdges;
        int **graphMatrix;
        int whichFile;
        int *distance;
        int *distanceList;
        int *previousVertex;
        int *previousVertexList;
        bool *visited;
        bool *visitedList;
        int dijkstraMatrixIterations;
        int dijkstraListIterations;

        list<ListElement> *graphList;


};

#endif // DIJKSTRAIMPLEMENTATION_H
