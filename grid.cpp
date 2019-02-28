#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <time.h>

#include "grid.h"
#include "gameRules.h"
#include "fileImporter.h"

//Having X and Y of different sizes does not work right now

using namespace std;

const char CELL = 'X';
const char BLANK = '-';
const int DELAY_TIME = 1000;

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

// 0 = brief pause - user can specify how long
// 1 = require enter
// 2 = file output
int viewMode;

//true will update the console and erase previous
//  false will print them one after another
bool animated;

int genNumber;

//wait time in milliseconds
int waitMs;
struct timespec ts;

// Methods
grid::grid()
{
    xSize = ySize = 5;

    genNumber = 0;

    currentGen = new char*[ySize];
    nextGen = new char*[ySize];
    checkGen = new char*[ySize];

    mode = 0;
    viewMode = 1;

    animated = false;

    waitMs = 2000;

    //set our timespec for use in nanosleep
    ts.tv_sec = waitMs / 1000;
    ts.tv_nsec = (waitMs % 1000) * 1000000;

    for (int y = 0; y < ySize; ++y)
    {
        currentGen[y] = new char[xSize];
        nextGen[y] = new char[xSize];
        checkGen[y] = new char[xSize];

        for (int x = 0; x < xSize; ++x) {
            currentGen[y][x] = nextGen[y][x] = checkGen[y][x] = BLANK;
        }
    }

    testingSetup();
}

//Takes in size of grid, border mode, view mode, animation on/off
grid::grid(int border, int view, bool animate, bool random, int delayLength)
{
    if(!random)
    {
        fileImporter myImporter;
        myImporter.openFile(&currentGen, &nextGen, &checkGen, &xSize, &ySize, random);
    }
    else
        fileImporter::generateNew(&currentGen, &nextGen, &checkGen, &xSize, &ySize);

    genNumber = 0;
    mode = border;
    viewMode = view;
    animated = animate;

    waitMs = (delayLength>=0)?delayLength:0;

    ts.tv_sec = waitMs / DELAY_TIME;
    ts.tv_nsec = (waitMs % DELAY_TIME) * pow(DELAY_TIME, 2);

    if(view == 2)
        outputFile.open("mRaymond_cValencia.out");
}

grid::~grid()
{
    if(currentGen)
        delete[] currentGen;
    if(nextGen)
        delete[] nextGen;
    if(checkGen)
        delete[] checkGen;
    if(outputFile)
        outputFile.close();
}

//will run the game specified ammount of times
void grid::run(int times)
{
    for (int i = 0; i < times; ++i)
    {
        switch (viewMode) {
            case 0: //BRIEF PAUSE
                nanosleep(&ts, NULL);
                printGrid();
                break;
            case 1: //ENTER
                printGrid();
                //This is the unicode for the opposite of \n
                cout << "\033[F";

                cout << "Press enter to advance to the next generation." << endl;
                cin.get();
                break;
            case 2: //FILE
                printGrid(&outputFile);
                break;
        }

        copyContents(&currentGen, &nextGen);

        if((i%2==0)&&(gameRules::checkSimilarities(&checkGen, &nextGen, ySize, xSize) || gameRules::checkSimilarities(&currentGen, &nextGen, ySize, xSize)))
        {
            cout << "This grid is now stable." << endl;
            break;
        }

        //Evaluate every position
        if(i%2==0)
            copyContents(&currentGen, &checkGen);

        //make the new grid the current one
        addressTemp = nextGen;
        nextGen = currentGen;
        currentGen = addressTemp;

        genNumber++;
    }
}

void grid::printGrid()
{
    // ToDo: change this to viewmode 0
    if (animated)
    {
        //Dont jump back the frist time
        if (genNumber > 0)
        {
            //The plus 4 is for the extra newlines. add the viewmode for
            //  when the user hits enter
            for (int y = 0; y < ySize + 4 + viewMode; ++y)
            {
                cout << "\033[F";
            }
        }
        else
        {
            cout << endl;
        }
    }

    cout << "Generation " << genNumber << BLANK_SPACE << endl;
    for (int y = 0; y < ySize; ++y)
    {
        for (int x = 0; x < xSize; ++x)
        {
            cout << currentGen[y][x];

            //ToDo: this will need to be removed before it gets turned in
            cout << ' ';
        }
        cout << '\n';
    }
    cout << "\n\n" << endl;

}

void grid::printGrid(ofstream* myStream)
{
    (*myStream) << "Generation " << genNumber << BLANK_SPACE << endl;
    for (int y = 0; y < ySize; ++y)
    {
        for (int x = 0; x < xSize; ++x)
        {
            (*myStream) << currentGen[y][x];
        }
        (*myStream) << '\n';
    }
    (*myStream) << "\n\n" << endl;
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
                continue;

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

void grid::classicReturn(int y, int x, int* nC)
{
    if(!(((x < 0) || (y < 0)) || ((x >= xSize) || (y >= ySize))))
    {
        if(currentGen[y][x] == 'X') (*nC)++;
    }
}

void grid::donutReturn(int y, int x, int* nC)
{
    x = (x+xSize)%xSize;
    y = (y+ySize)%ySize;

    if(currentGen[y][x] == 'X') (*nC)++;
}

void grid::mirrorReturn(int y, int x, int* nC)
{
    x = ((x==-1) || (x==xSize)) ? abs(x)-1 : x;
    y = ((y==-1) || (y==ySize)) ? abs(y)-1 : y;

    if(currentGen[y][x] == 'X') (*nC)++;
}

void grid::copyContents(char*** source, char*** destination)
{
    for (int y = 0; y < ySize; ++y)
    {
        for (int x = 0; x < xSize; ++x)
        {
            (*destination)[y][x] = gameRules::evaluate(returnSurrounding(x,y), (*source)[y][x]);
        }
    }
}
