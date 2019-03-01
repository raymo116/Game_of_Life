#ifndef MC_GRID
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
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
            char** checkGen;

            int genNumber;

            //will run the game specified ammount of times
            void run(int times);

            void printGrid();
            void printGrid(ofstream* myStream);

            // Methods
            grid();
            //Takes in border mode, view mode, animation on/off
            grid(int border, int view, bool random, int delayLength);
            ~grid();

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

            const string BLANK_SPACE = "            ";

            //wait time in milliseconds
            int waitMs;
            struct timespec ts;

            int returnSurrounding(int row, int column);

            void checkRCError(int y, int x);

            void classicReturn(int x, int y, int* nC);
            void donutReturn(int x, int y, int* nC);
            void mirrorReturn(int x, int y, int* nC);
            ofstream outputFile;
            string outputFilepath;
            void copyContents(char*** source, char*** destination);
    };
}
#endif
