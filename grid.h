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

            char ** addressTemp;

            // Will switch these grids back and forth via reference,
            // which is why the names are basically the same
            char** currentGen;
            char** nextGen;

            int genNumber;

            //will run the game specified ammount of times
            void run(int times);

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
