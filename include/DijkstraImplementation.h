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
        void dijkstraAlgorithmMatrix();
        void dijkstraAlgorithmList();

    protected:

    private:
        int numberOfVertices;
        int numberOfEdges;
        int **graphMatrix;
        int whichFile;
};

#endif // DIJKSTRAIMPLEMENTATION_H
