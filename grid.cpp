#include <iostream>
#include <string>
#include "grid.h"

using namespace std;

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

    grid1 = new bool*[xSize];
    grid2 = new bool*[xSize];
    officialGrid = grid1;

    for (int row = 0; row < xSize; ++row)
    {
        grid1[row] = new bool[ySize];
        grid2[row] = new bool[ySize];

        for (int column = 0; column < ySize; ++column) {
            grid1[row][column] = false;
            grid2[row][column] = false;
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
            switch (officialGrid[row][column])
            {
                case true:
                    cout << 'X';
                    break;
                case false:
                    cout << '-';
                    break;
            }
            //ToDo: this will need to be removed before it gets turned in
            cout << ' ';
            // flipValue(&officialGrid[row][column]);
        }
        cout << '\n';
    }
    cout << "\n\n" << endl;

    returnSurrounding(1, 1);
}

// I don't know what this is going to be used for, but it seems helpfup for later
void grid::flipValue(bool* currentBool)
{
    *currentBool = (*currentBool+1)%2;
}

// This method is ust used for testing purposess
void grid::testingSetup()
{
    for (int i = 0; i < xSize; ++i) {
        grid1[i][i] = true;
    }
}

void grid::returnSurrounding(int row, int column)
{
    // Goes from one to the right to one to the left
    for (int rowScan = -1; rowScan < 2; ++rowScan)
    {
        // Goes from one to the right to one to the left
        for (int columnScan = -1; columnScan < 2; ++columnScan)
        {
            cout << translate(officialGrid[row+rowScan][column+columnScan]) << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

char grid::translate(bool currentCell)
{
    return ((currentCell == false) ? '-' : 'X');
}

bool grid::translate(char currentCell)
{
    return ((currentCell == '-') ? false : true);
}
