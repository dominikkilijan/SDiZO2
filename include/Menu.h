#ifndef MENU_H
#define MENU_H


class Menu
{
    public:
        Menu();
        virtual ~Menu();

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
};

#endif // MENU_H
