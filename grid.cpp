#include <iostream>
#include <string>
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
    mode = 2;

    grid1 = new char*[ySize];
    grid2 = new char*[ySize];
    officialGrid = grid1;

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

    returnSurrounding(0,xSize-1);
    returnSurrounding(ySize-1,0);
    returnSurrounding(3,3);
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

//In this method X and Y are reversed, you can go in and flip all of them if you like
void grid::returnSurrounding(int ROW, int COLUMN)
{
    checkRCError(ROW, COLUMN);

    // Keep us from having to do the math multiple times for boolean evaluations
    int tempX = 0;
    int tempY = 0;

    // The number of neighbors the given item has
    int neighborCount = 0;

    // Goes from one to the right to one to the left
    for (int XScan = -1; XScan < 2; ++XScan)
    {
        // Goes from one up to one down
        for (int YScan = -1; YScan < 2; ++YScan)
        {
            // Skips the center so it only evaluates the center's surroundings
            if((YScan == 0) && (XScan == 0))
            {
                cout << "E "; // E = the one being evaluated
                continue;
            }

            tempX = ROW + XScan;
            tempY = COLUMN + YScan;

            //Here we switch on the mode for custom behavoir
            switch (mode) {
                //CLASSIC
                case 0: if(((tempX < 0) || (tempY < 0)) ||
                           ((tempX >= xSize) || (tempY >= ySize)))
                        {
                            // Temp border character
                            cout << "B ";
                        }
                        else
                        {
                            cout << officialGrid[tempX][tempY] << ' ';
                            if(officialGrid[tempX][tempY] == 'X') neighborCount++;
                        }

                        break;

                //DONUT
                case 1: cout << officialGrid[(tempX+xSize)%xSize][(tempY+ySize)%ySize] << ' ';
                        if(officialGrid[(tempX+xSize)%xSize][(tempY+ySize)%ySize] == 'X') neighborCount++;

                        break;

                //MIRROR
                case 2:
                        //There has to be a more elegant solution to the issue of overlaps but for now this works
                        if((tempY == -1) || (tempY == ySize))
                        {
                            if((tempX == -1) || (tempX == xSize))
                            {
                                cout << officialGrid[abs(tempX)-1][abs(tempY)-1] << ' ';
                                if(officialGrid[abs(tempX)-1][abs(tempY)-1] == 'X') neighborCount++;
                                break;
                            }
                            else
                            {
                                cout << officialGrid[tempX][abs(tempY)-1] << ' ';
                                if(officialGrid[tempX][abs(tempY)-1] == 'X') neighborCount++;
                                break;
                            }

                        }

                        if((tempX == -1) || (tempX == xSize))
                        {
                            if((tempY == -1) || (tempY == ySize))
                            {
                                cout << officialGrid[abs(tempX)-1][abs(tempY)-1] << ' ';
                                if(officialGrid[abs(tempX)-1][abs(tempY)-1] == 'X') neighborCount++;
                                break;
                            }
                            else
                            {
                                cout << officialGrid[abs(tempX)-1][tempY] << ' ';
                                if(officialGrid[abs(tempX)-1][tempY] == 'X') neighborCount++;
                                break;
                            }

                        }

                        else
                        {
                            cout << officialGrid[tempX][tempY] << ' ';
                            if(officialGrid[tempX][tempY] == 'X') neighborCount++;
                        }
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
