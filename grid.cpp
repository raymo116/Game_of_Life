#include <iostream>
#include <string>
#include <cmath>

#include "grid.h"
#include "gameRules.h"


using namespace std;

const char CELL = 'X';
const char BLANK = '-';

//for storing the address when switching between grids
//cant be an int since the grids we are working with are already pointers
char ** addressTemp;

char** currentGen;
char** nextGen;

// Variables
int xSize, ySize;

// 0 = classic
// 1 = donut
// 2 = mirror
int mode;

int genNumber;

// Methods
grid::grid()
{
    xSize = ySize = 5;

    genNumber = 0;

    currentGen = new char*[ySize];
    nextGen = new char*[ySize];

    mode = 0;

    for (int y = 0; y < ySize; ++y)
    {
        currentGen[y] = new char[xSize];
        nextGen[y] = new char[xSize];

        for (int x = 0; x < xSize; ++x) {
            currentGen[y][x] = BLANK;
            nextGen[y][x] = BLANK;
        }
    }

    testingSetup();
}

grid::~grid()
{
    delete[] currentGen;
    delete[] nextGen;
}

//will run the game specified ammount of times
void grid::run(int times)
{
    for (int i = 0; i < times; ++i)
    {
        //Evaluate every position
        for (int y = 0; y < ySize; ++y)
        {
            for (int x = 0; x < xSize; ++x)
            {
                nextGen[x][y] = gameRules::evaluate(returnSurrounding(y,x));
            }
        }

        //make the new grid the current one
        addressTemp = nextGen;
        nextGen = currentGen;
        currentGen = addressTemp;

        genNumber++;

        //print
        printGrid();

    }
}

void grid::printGrid()
{
    cout << "Generation " << genNumber << endl;
    for (int y = 0; y < ySize; ++y)
    {
        for (int x = 0; x < xSize; ++x)
        {
            cout << currentGen[y][x];

            //ToDo: this will need to be removed before it gets turned in
            cout << ' ';
            // For testing purposes
            // flipValue(&officialGrid[y][x]);
        }
        cout << '\n';
    }
    cout << "\n\n" << endl;

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
        currentGen[i][i] = CELL;
    }
    currentGen[0][xSize-1] = CELL;
    currentGen[1][xSize-1] = CELL;
    currentGen[ySize-2][0] = CELL;
    printGrid();
}

// Fixed te reversed X and Y
int grid::returnSurrounding(int x, int y)
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
                //cout << "E "; // E = the one being evaluated
                continue;
            }

            xTemp = x + xScan;
            yTemp = y + yScan;

            //Here we switch on the mode for custom behavoir
            switch (mode) {
                case 0: //CLASSIC
                    classicReturn(yTemp, xTemp, &neighborCount);
                    break;
                case 1: //DONUT
                    donutReturn(yTemp, xTemp, &neighborCount);
                    break;
                case 2: //MIRROR
                    mirrorReturn(yTemp, xTemp, &neighborCount);
                    break;

            }

        }
        //cout << endl;
    }
    return neighborCount;
}

// Checks to make sure that the rows given are valid and won't go outside of the grid
void grid::checkRCError(int x, int y)
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
        //cout << "B ";
    }
    else
    {
        //cout << currentGen[x][y] << ' ';
        if(currentGen[x][y] == 'X') (*nC)++;
    }
}

void grid::donutReturn(int x, int y, int* nC)
{
    x = (x+xSize)%xSize;
    y = (y+ySize)%ySize;

    //cout << currentGen[x][y] << ' ';
    if(currentGen[x][y] == 'X') (*nC)++;
}

void grid::mirrorReturn(int x, int y, int* nC)
{
    x = ((x==-1) || (x==xSize)) ? abs(x)-1 : x;
    y = ((y==-1) || (y==ySize)) ? abs(y)-1 : y;

    //cout << currentGen[x][y] << ' ';
    if(currentGen[x][y] == 'X') (*nC)++;
}
