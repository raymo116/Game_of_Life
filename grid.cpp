#include <iostream>
#include <string>
#include "grid.h"

// ToDo: We have three grids (grid1, grid2, and officialGrid).
// grid1 and grid two are just so that we have two grids to compare
// officialGrid is so that we can look at that grid while updating grid1 or grid2
// behind the scenes without changing official grid

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
    xSize=ySize = 5;

    grid1 = new char*[xSize];
    grid2 = new char*[xSize];
    officialGrid = grid1;

    for (int row = 0; row < xSize; ++row)
    {
        grid1[row] = new char[ySize];
        grid2[row] = new char[ySize];

        for (int column = 0; column < ySize; ++column) {
            grid1[row][column] = BLANK;
            grid2[row][column] = BLANK;
        }
    }
    testingSetup();
}

void grid::printGrid()
{
    for (int row = 0; row < xSize; ++row)
    {
        for (int column = 0; column < ySize; ++column)
        {
            cout << officialGrid[row][column];

            //ToDo: this will need to be removed before it gets turned in
            cout << ' ';
            // For testing purposes
            // flipValue(&officialGrid[row][column]);
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
}

void grid::returnSurrounding(int row, int column)
{
    checkRCError(row, column);

    // Keep us from having to do the math multiple times for boolean evaluations
    int tempRow=0;
    int tempColumn = 0;

    // The number of neighbors the given item has
    int neighborCount = 0;

    // Goes from one to the right to one to the left
    for (int rowScan = -1; rowScan < 2; ++rowScan)
    {
        // Goes from one to the right to one to the left
        for (int columnScan = -1; columnScan < 2; ++columnScan)
        {
            // Skips the center so it only evaluates the center's surroundings
            if((columnScan == 0) && (rowScan == 0))
            {
                cout << "E "; // E = the one being evaluated
                continue;
            }

            tempRow = row+rowScan;
            tempColumn = column+columnScan;

            if(((tempRow < 0) || (tempColumn < 0)) ||
               ((tempRow >= xSize) || (tempColumn >= ySize)))
            {
                // Temp border character
                cout << "B ";
            }
            else
            {
                cout << officialGrid[tempRow][tempColumn] << ' ';
                if(officialGrid[tempRow][tempColumn] == 'X') neighborCount++;

            }

        }
        cout << endl;
    }
    cout << endl << neighborCount << endl;
}

// Checks to make sure that the rows given are valid and won't go outside of the grid
void grid::checkRCError(int row, int column)
{
    if(((row >= xSize) || (row < 0)) || (column >= ySize) || (column < 0))
    {
        throw invalid_argument(("recieved a index outside of the grid: index "+to_string(row)+","+to_string(column)));
    }
}
