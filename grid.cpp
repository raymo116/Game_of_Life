#include <iostream>
#include <string>
#include <cmath>
#include "grid.h"

// ToDo: We have three grids (grid1, grid2, and officialGrid).
// grid1 and grid two are just so that we have two grids to compare
// officialGrid is so that we can look at that grid while updating grid1 or grid2
// behind the scenes without changing official grid

//Grids are referenced Y,X or ROW,COLUMN

using namespace std;

const char CELL = 'X';
const char BLANK = '-';

bool **grid1;
// Variables
int xSize, ySize;

// 0 = classic
// 1 = donut
// 2 = mirror
int mode;

// Methods
grid::grid()
{
    xSize = ySize = 5;

    grid1 = new char*[ySize];
    grid2 = new char*[ySize];
    officialGrid = grid1;

    mode = 2;

    for (int y = 0; y < ySize; ++y)
    {
        grid1[y] = new char[xSize];
        grid2[y] = new char[xSize];

        for (int x = 0; x < xSize; ++x) {
            grid1[y][x] = BLANK;
            grid2[y][x] = BLANK;
        }
    }
    testingSetup();
}

void grid::printGrid()
{
    for (int y = 0; y < ySize; ++y)
    {
        for (int x = 0; x < xSize; ++x)
        {
            cout << officialGrid[y][x];

            //ToDo: this will need to be removed before it gets turned in
            cout << ' ';
            // For testing purposes
            // flipValue(&officialGrid[y][x]);
        }
        cout << '\n';
    }
    cout << "\n\n" << endl;

    returnSurrounding(xSize-1,0);
}

// I don't know what this is going to be used for, but it seems helpfup for later
void grid::flipValue(char* currentBool)
{
    *currentBool = (*currentBool == CELL) ? BLANK : CELL;
}

// This method is ust used for testing purposess
void grid::testingSetup()
{
    for (int i = 0; i < xSize; ++i) {
        grid1[i][i] = CELL;
    }
    grid1[0][xSize-1] = CELL;
    grid1[1][xSize-1] = CELL;
    grid1[ySize-2][0] = CELL;
}

// Fixed te reversed X and Y
void grid::returnSurrounding(int x, int y)
{
    checkRCError(x, y);

    // Keep us from having to do the math multiple times for boolean evaluations
    int xTemp = 0;
    int yTemp = 0;

    // The number of neighbors the given item has
    int neighborCount = 0;

    // Goes from one to the right to one to the left
    for (int yScan = -1; yScan < 2; ++yScan)
    {
        // Goes from one up to one down
        for (int xScan = -1; xScan < 2; ++xScan)
        {
            // Skips the center so it only evaluates the center's surroundings
            if((xScan == 0) && (yScan == 0))
            {
                cout << "E "; // E = the one being evaluated
                continue;
            }

            xTemp = x + xScan;
            yTemp = y + yScan;

            //Here we switch on the mode for custom behavoir
            switch (mode) {
                //CLASSIC
                case 0:
                    classicReturn(yTemp, xTemp, &neighborCount);
                    break;

                //DONUT
                case 1:
                    donutReturn(yTemp, xTemp, &neighborCount);
                    break;

                //MIRROR
                case 2:
                    mirrorReturn(yTemp, xTemp, &neighborCount);
                    break;

            }

        }
        cout << endl;
    }
    cout << endl << neighborCount << endl;
}

// Checks to make sure that the rows given are valid and won't go outside of the grid
void grid::checkRCError(int y, int x)
{
    if(((x >= xSize) || (x < 0)) || (y >= ySize) || (y < 0))
    {
        throw invalid_argument(("recieved a index outside of the grid: index "+to_string(y)+","+to_string(x)));
    }
}

void grid::classicReturn(int x, int y, int* nC)
{
    if(((x < 0) || (y < 0)) || ((x >= ySize) || (y >= xSize)))
    {
        // Temp border character
        cout << "B ";
    }
    else
    {
        cout << officialGrid[x][y] << ' ';
        if(officialGrid[x][y] == 'X') (*nC)++;
    }
}

void grid::donutReturn(int x, int y, int* nC)
{
    x = (x+xSize)%xSize;
    y = (y+ySize)%ySize;

    cout << officialGrid[x][y] << ' ';
    if(officialGrid[x][y] == 'X') (*nC)++;
}

void grid::mirrorReturn(int x, int y, int* nC)
{
    if((x==-1) || (x==xSize))
    {
        x = abs(x)-1;
    }
    if((y==-1) || (y==ySize))
    {
        y = abs(y)-1;
    }

    cout << officialGrid[x][y] << ' ';
    if(officialGrid[x][y] == 'X') (*nC)++;
}
