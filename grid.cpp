#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <time.h>

#include "grid.h"
#include "game_rules.h"
#include "file_importer.h"

using namespace std;

// Methods
Grid::Grid(){
    //default is a random grid
    FileImporter::GenerateNew(&currentGen, &nextGen, &checkGen, &xSize, &ySize);

    int delayLength = 100;
    genNumber = mode = viewMode = 0;

    waitMs = (delayLength>=0)?delayLength:0;

    ts.tv_sec = waitMs / DELAY_TIME;
    ts.tv_nsec = (waitMs % DELAY_TIME) * pow(DELAY_TIME, 2);
}

//Takes in size of grid, border mode, view mode, animation on/off
Grid::Grid(int border, int view, bool random, int delayLength){
    if(!random){
        FileImporter myImporter;
        myImporter.OpenFile(&currentGen, &nextGen, &checkGen, &xSize, &ySize, random);
    }
    else
        FileImporter::GenerateNew(&currentGen, &nextGen, &checkGen, &xSize, &ySize);

    genNumber = 0;
    mode = border;
    viewMode = view;
    waitMs = (delayLength>=0)?delayLength:0;

    ts.tv_sec = waitMs / DELAY_TIME;
    ts.tv_nsec = (waitMs % DELAY_TIME) * pow(DELAY_TIME, 2);

    if(view == 2) outputFile.open("mRaymond_cValencia.out");
}

Grid::~Grid(){
    if(currentGen){
        for(int y=0; y < ySize; ++y)
            for(int x=0; x < xSize; ++x)
                delete[] &(currentGen[y][x]);
        delete[] currentGen;
    }
    if(nextGen){
        for(int y=0; y < ySize; ++y)
            for(int x=0; x < xSize; ++x)
                delete[] &(nextGen[y][x]);
        delete[] nextGen;
    }
    if(checkGen){
        for(int y=0; y < ySize; ++y)
            for(int x=0; x < xSize; ++x)
                delete[] &(checkGen[y][x]);
        delete[] checkGen;
    }
    if(outputFile)
        outputFile.close();
}

//will run the game specified ammount of times
void Grid::Run(int times){
    for (int i = 0; i < times; ++i){
        switch (viewMode) {
            case 0: //BRIEF PAUSE
                nanosleep(&ts, NULL);
                PrintGrid();
                break;
            case 1: //ENTER
                PrintGrid();
                // \033[F is the unicode for the opposite of \n
                cout << "\033[FPress enter to advance to the next generation." << endl;
                cin.get();
                break;
            case 2: //FILE
                PrintGrid(&outputFile);
                break;
        }

        CopyContents(&currentGen, &nextGen);

        if((i%2==0) && (GameRules::CheckSimilarities(&checkGen, &nextGen, ySize, xSize) || GameRules::CheckSimilarities(&currentGen, &nextGen, ySize, xSize))){
            cout << "This grid is now stable." << endl;
            break;
        }

        //Copy every other grid into the checking spot
        if(i%2==0) CopyContents(&currentGen, &checkGen);

        //make the new grid the current one
        addressTemp = nextGen;
        nextGen = currentGen;
        currentGen = addressTemp;
        genNumber++;
    }
}

void Grid::PrintGrid(){ // Send to console
    if (viewMode == 0 || viewMode == 1){
        //Dont jump back the first time
        if (genNumber > 0){
            for (int y = 0; y < ySize + 1 + viewMode; ++y){
                cout << "\033[F";
            }
        }
        else
            cout << endl;
    }

    cout << "Generation " << genNumber << BLANK_SPACE << endl;
    for (int y = 0; y < ySize; ++y){
        for (int x = 0; x < xSize; ++x){
            cout << currentGen[y][x] << ' ';
        }
        cout << '\n';
    }
}

void Grid::PrintGrid(ofstream* myStream){ // Send to filestream
    (*myStream) << "Generation " << genNumber << BLANK_SPACE << endl;
    for (int y = 0; y < ySize; ++y){
        for (int x = 0; x < xSize; ++x){
            (*myStream) << currentGen[y][x];
        }
        (*myStream) << '\n';
    }
}

// Fixed te reversed X and Y
int Grid::ReturnSurrounding(int x, int y){
    CheckRCError(x, y);

    // Keep us from having to do the math multiple times for boolean evaluations
    int xTemp = 0;
    int yTemp = 0;

    // The number of neighbors the given item has
    int neighborCount = 0;

    // Goes from one to the right to one to the left
    for (int yScan = -1; yScan < 2; ++yScan){
        // Goes from one up to one down
        for (int xScan = -1; xScan < 2; ++xScan){
            // Skips the center so it only evaluates the center's surroundings
            if((xScan == 0) && (yScan == 0))
                continue;

            xTemp = x + xScan;
            yTemp = y + yScan;

            //Here we switch on the mode for custom behavoir
            switch (mode) {
                case 0: //CLASSIC
                    ClassicReturn(yTemp, xTemp, &neighborCount);
                    break;
                case 1: //DONUT
                    DonutReturn(yTemp, xTemp, &neighborCount);
                    break;
                case 2: //MIRROR
                    MirrorReturn(yTemp, xTemp, &neighborCount);
                    break;
            }
        }
    }
    return neighborCount;
}

// Checks to make sure that the rows given are valid and won't go outside of the grid
void Grid::CheckRCError(int x, int y){
    if(((x >= xSize) || (x < 0)) || (y >= ySize) || (y < 0))
        throw invalid_argument(("recieved a index outside of the grid: index "+to_string(y)+","+to_string(x)));
}

void Grid::ClassicReturn(int y, int x, int* nC){
    if(!(((x < 0) || (y < 0)) || ((x >= xSize) || (y >= ySize))))
        if(currentGen[y][x] == 'X') (*nC)++;
}

void Grid::DonutReturn(int y, int x, int* nC){
    x = (x+xSize)%xSize;
    y = (y+ySize)%ySize;
    if(currentGen[y][x] == 'X') (*nC)++;
}

void Grid::MirrorReturn(int y, int x, int* nC){
    x = ((x==-1) || (x==xSize)) ? abs(x)-1 : x;
    y = ((y==-1) || (y==ySize)) ? abs(y)-1 : y;
    if(currentGen[y][x] == 'X') (*nC)++;
}

void Grid::CopyContents(char*** source, char*** destination){
    for (int y = 0; y < ySize; ++y)
        for (int x = 0; x < xSize; ++x)
            (*destination)[y][x] = GameRules::Evaluate(ReturnSurrounding(x,y), (*source)[y][x]);
}
