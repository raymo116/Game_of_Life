#ifndef MC_GRID
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <time.h>

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
            //Takes in border mode, view mode, animation on/off
            grid(int border, int view, bool animate);
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

            // 0 = brief pause - user can specify how long
            // 1 = require enter
            // 2 = file output
            int viewMode;

            //true will update the console and erase previous
            //  false will print them one after another
            bool animated;

            const string BLANK_SPACE = "            ";

            //wait time in milliseconds
            int waitMs;
            struct timespec ts;

            void testingSetup();
            int returnSurrounding(int row, int column);

            void checkRCError(int y, int x);

            void classicReturn(int x, int y, int* nC);
            void donutReturn(int x, int y, int* nC);
            void mirrorReturn(int x, int y, int* nC);
    };
}
#endif
