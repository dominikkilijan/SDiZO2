#ifndef DIJKSTRAIMPLEMENTATION_H
#define DIJKSTRAIMPLEMENTATION_H

#include <list>
#include <vector>

using namespace std;


class DijkstraImplementation
{
    public:
        struct ListElement
        {
            int nextElement;
            int edgeValue;
        };

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
        bool *visited;
        bool *visitedList;
        int dijkstraMatrixIterations;
        int dijkstraListIterations;

        list<ListElement> *graphList;


};

#endif // DIJKSTRAIMPLEMENTATION_H
