#ifndef MC_GRID
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <time.h>

using namespace std;

class Grid
{
    public:
        // Constructor for the Grid object
        // Takes in ints for border type and viewmode, a bool for whether the grid is supposed to be random, and an in for the delay length
        Grid(int border, int view, bool random, int delaylength);
        // Destructor
        ~Grid();

        // Takes in an int for the number of generations and generates that many generations
        void Run(int times);
        // Prints the grid to the console
        void PrintGrid();
        // Overload of PrintGrid that saves to a file. It takes a pointer to an ofstream
        void PrintGrid(ofstream* myStream);

        // For switching these grids back and forth via reference
        char** addresstemp_;
        char** currentgen_;
        char** nextgen_;
        char** checkgen_;

        // The number of the current generation
        int gennumber_;

    private:
        // The default delay time for the grid rendering
        const int kDelayTime = 1000;

        // Checks the contents of the cells surrounding a certain xy point
        int ReturnSurrounding(int row, int column);
        // Checks to make sure that the rows given are valid and won't go outside of the grid
        // Takes in x and y coordinates as ints
        void CheckRCError(int y, int x);
        // Performs classic return. Takes yx coordinates as ints, and a pointer to the number of neighbors
        void ClassicReturn(int x, int y, int* nC);
        // Performs donut return. Takes yx coordinates as ints, and a pointer to the number of neighbors
        void DonutReturn(int x, int y, int* nC);
        // Performs mirror return. Takes yx coordinates as ints, and a pointer to the number of neighbors
        void MirrorReturn(int x, int y, int* nC);
        // Reads the first grid into GameRules and outputs results into second grid
        // Takes two pointers to character grids, one for the source and one for the output
        void CopyContents(char*** source, char*** destination);

        // The x and y sizes of the grid
        int xsize_;
        int ysize_;

        // Game mode
        // (0, classic), (1, donut), (2, mirror)
        int mode_;

        // View Mode
        // (0, user-specified pause), (1, require enter), (2, file output)
        int viewmode_;

        // Wait time in milliseconds
        int waitms_;
        struct timespec ts_;
        // output filestream
        ofstream outputfile_;
        // filepath to export to
        string outputfilepath_;

};
#endif
