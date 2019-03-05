#ifndef MC_GRID
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <time.h>

using namespace std;

namespace std {
    class Grid
    {
        public:
            const char CELL = 'X';
            const char BLANK = '-';
            const int DELAY_TIME = 1000;

            char ** addressTemp;

            // Will switch these grids back and forth via reference, which is why the names are basically the same
            char** currentGen;
            char** nextGen;
            char** checkGen;

            int genNumber;

            //will run the game specified ammount of times
            void Run(int times);

            void PrintGrid();
            void PrintGrid(ofstream* myStream);

            // Methods
            Grid();
            //Takes in border mode, view mode, animation on/off
            Grid(int border, int view, bool random, int delayLength);
            ~Grid();

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

            int ReturnSurrounding(int row, int column);


            void ClassicReturn(int x, int y, int* nC);
            void DonutReturn(int x, int y, int* nC);
            void MirrorReturn(int x, int y, int* nC);
            ofstream outputFile;
            string outputFilepath;
            void CopyContents(char*** source, char*** destination);
    };
}
#endif
