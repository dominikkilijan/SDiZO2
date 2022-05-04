#ifndef DIJKSTRAIMPLEMENTATION_H
#define DIJKSTRAIMPLEMENTATION_H


class DijkstraImplementation
{
    public:
        DijkstraImplementation(int);
        virtual ~DijkstraImplementation();

        void createGraphMatrix();
        void printMatrix();
        void getFileInfo();
        void dijkstraAlgorithmMatrix(int);
        void dijkstraAlgorithmList();
        void printDistances();
        void initTables();

    protected:

    private:
        int numberOfVertices;
        int numberOfEdges;
        int **graphMatrix;
        int whichFile;
        int *distance;
        bool *visited;
        int dijkstraMatrixIterations;
};

#endif // DIJKSTRAIMPLEMENTATION_H
