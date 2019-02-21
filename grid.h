#ifndef MC_GRID
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace std {
    class grid
    {
        public:
            const char CELL = 'X';
            const char BLANK = '-';

            // Will switch these grids back and forth via reference,
            // which is why the names are basically the same
            char** grid1;
            char** grid2;

            // This grid is the one that will be referenced by methods, so it
            // always needs to point to the most recent grid
            char** officialGrid;
            void printGrid();

            // Methods
            grid();
            ~grid();

            void flipValue(char* currentBool);
        private:
            // Variables
            int xSize;
            int ySize;

            // 0 = classic
            // 1 = donut
            // 2 = mirror
            int mode;

            void testingSetup();
            int returnSurrounding(int row, int column);

            void checkRCError(int y, int x);

            void classicReturn(int x, int y, int* nC);
            void donutReturn(int x, int y, int* nC);
            void mirrorReturn(int x, int y, int* nC);
    };
}
#endif
