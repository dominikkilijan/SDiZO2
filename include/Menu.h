#ifndef MENU_H
#define MENU_H


class Menu
{
    public:
        Menu();
        virtual ~Menu();

        struct EdgeOptions
        {
            public:
                int v1;
                int v2;
        };

        void generateRandomGraph();
        int binomialCoefficients(int,int);


    protected:

    private:
        int choice;
        int work;
        int fileChoice;
        int numVert;
        int numEdges;
        int edgeDensity;
        EdgeOptions* edgeOptionsTable;
};

#endif // MENU_H
