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
            Grid();
            Grid(int border, int view, bool random, int delaylength);
            ~Grid();

            // Will run the game specified ammount of times
            void Run(int times);

            void PrintGrid();
            void PrintGrid(ofstream* myStream);

            // For switching these grids back and forth via reference
            char** addresstemp_;
            char** currentgen_;
            char** nextgen_;
            char** checkgen_;

            int gennumber_;

        private:
            const int kDelayTime = 1000;
            const string kBlankSpace = "            ";

            int ReturnSurrounding(int row, int column);

            void CheckRCError(int y, int x);

            void ClassicReturn(int x, int y, int* nC);
            void DonutReturn(int x, int y, int* nC);
            void MirrorReturn(int x, int y, int* nC);

            void CopyContents(char*** source, char*** destination);

            int xsize_;
            int ysize_;

            // 0 = classic
            // 1 = donut
            // 2 = mirror
            int mode_;

            // 0 = brief pause - user can specify how long
            // 1 = require enter
            // 2 = file output
            int viewmode_;

            // Wait time in milliseconds
            int waitms_;
            struct timespec ts_;

            ofstream outputfile_;
            string outputfilepath_;

    };
}
#endif
