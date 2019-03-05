#include "grid.h"

#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <time.h>

#include "game_rules.h"
#include "file_importer.h"

using namespace std;

// Constructor for the Grid object
// Takes in ints for border type and viewmode, a bool for whether the grid is supposed to be random, and an in for the delay length
Grid::Grid(int border, int view, bool random, int delaylength){
    if(!random){
        // Open from file
        FileImporter myImporter;
        myImporter.OpenFile(&currentgen_, &nextgen_, &checkgen_, &xsize_, &ysize_, false);
    }
    else // generate a new map
        FileImporter::GenerateNew(&currentgen_, &nextgen_, &checkgen_, &xsize_, &ysize_);

    gennumber_ = 0;
    mode_ = border;
    viewmode_ = view;
    waitms_ = (delaylength >= 0) ? delaylength:0;

    ts_.tv_sec = waitms_ / kDelayTime;
    ts_.tv_nsec = (waitms_ % kDelayTime) * pow(kDelayTime, 2);

    if(view == 2) outputfile_.open("mRaymond_cValencia.out");
}

// Destructor
Grid::~Grid(){
    // Delete all of the grids
    if(currentgen_){
        for(int y = 0; y < ysize_; ++y)
            delete[] currentgen_[y];
        delete[] currentgen_;
    }
    if(nextgen_){
        for(int y = 0; y < ysize_; ++y)
            delete[] nextgen_[y];
        delete[] nextgen_;
    }
    if(checkgen_){
        for(int y = 0; y < ysize_; ++y)
            delete[] checkgen_[y];
        delete[] checkgen_;
    }
    // Close the output filestream
    if(outputfile_)
        outputfile_.close();
}

// Takes in an int for the number of generations and generates that many generations
void Grid::Run(int times){
    for (int i = 0; i < times; ++i){
        //Print grid based on view mode
        switch (viewmode_){
            case 0: //BRIEF PAUSE
                nanosleep(&ts_, NULL);
                PrintGrid();
                break;
            case 1: //ENTER
                PrintGrid();
                // \033[F is the unicode for the opposite of \n
                cout << "\033[FPress enter to advance to the next generation." << endl;
                cin.get();
                break;
            case 2: //FILE
                PrintGrid(&outputfile_);
                break;
        }

        //Evauluates each position from current and outputs to next
        CopyContents(&currentgen_, &nextgen_);

        //Check similarites between grids
        if((i % 2 == 0) && (GameRules::CheckSimilarities(&checkgen_, &nextgen_, ysize_, xsize_)
                        ||  GameRules::CheckSimilarities(&currentgen_, &nextgen_, ysize_, xsize_))){
            cout << "This grid is now stable." << endl;
            break;
        }

        // Copy every other generation into che checkgen_ grid to check for periods of 2 (blinkers)
        if(i % 2 == 0) CopyContents(&currentgen_, &checkgen_);

        //Swap the grids
        addresstemp_ = nextgen_;
        nextgen_ = currentgen_;
        currentgen_ = addresstemp_;

        gennumber_++;
    }

}

// Prints the grid to the console
void Grid::PrintGrid(){
    if (viewmode_ < 2){
        //Dont jump back the first time
        if (gennumber_ > 0){
            // Deletes the previous grid from the screen
            for (int y = 0; y < ysize_ + 1 + viewmode_; ++y){
                cout << "\033[F";
            }
        }
        else
            cout << endl;
    }

    // Prints the new contents to the screen
    cout << "Generation " << gennumber_ << endl;
    for (int y = 0; y < ysize_; ++y){
        for (int x = 0; x < xsize_; ++x){
            cout << currentgen_[y][x] << ' ';
        }
        cout << '\n';
    }
}

// Overload of PrintGrid that saves to a file. It takes a pointer to an ofstream
void Grid::PrintGrid(ofstream* mystream){
    (*mystream) << "Generation " << gennumber_ << endl;
    for (int y = 0; y < ysize_; ++y){
        for (int x = 0; x < xsize_; ++x){
            (*mystream) << currentgen_[y][x];
        }
        (*mystream) << '\n';
    }
}

// Checks the contents of the cells surrounding a certain xy point
int Grid::ReturnSurrounding(int x, int y){
    // Prevents segfault
    CheckRCError(x, y);

    // Keep us from having to do the math multiple times for boolean evaluations
    int xtemp = 0;
    int ytemp = 0;

    // The number of neighbors the given item has
    int count = 0;

    // Goes from one to the right to one to the left
    for (int yscan = -1; yscan < 2; ++yscan){
        // Goes from one up to one down
        for (int xscan = -1; xscan < 2; ++xscan){
            // Skips the center so it only evaluates the center's surroundings
            if((xscan == 0) && (yscan == 0))
                continue;

            // The current index to look at
            xtemp = x + xscan;
            ytemp = y + yscan;

            // Here we switch on the mode for custom behavoir
            switch (mode_) {
                case 0: //CLASSIC
                    ClassicReturn(ytemp, xtemp, &count);
                    break;
                case 1: //DONUT
                    DonutReturn(ytemp, xtemp, &count);
                    break;
                case 2: //MIRROR
                    MirrorReturn(ytemp, xtemp, &count);
                    break;
            }
        }
    }
    return count;
}

// Checks to make sure that the rows given are valid and won't go outside of the grid
// Takes in x and y coordinates as ints
void Grid::CheckRCError(int x, int y){
    if(((x >= xsize_) || (x < 0)) || (y >= ysize_) || (y < 0))
        throw invalid_argument(("recieved a index outside of the grid: index "+to_string(y)+","+to_string(x)));
}

// Performs classic return. Takes yx coordinates as ints, and a pointer to the number of neighbors
void Grid::ClassicReturn(int y, int x, int* count){
    // If the coordinates are contained in the grid
    if(!(((x < 0) || (y < 0)) || ((x >= xsize_) || (y >= ysize_))))
        // If the character is an X
        if(currentgen_[y][x] == 'X') (*count)++;
}

// Performs donut return. Takes yx coordinates as ints, and a pointer to the number of neighbors
void Grid::DonutReturn(int y, int x, int* count){
    x = (x+xsize_)%xsize_; // e.g. if grid.length=5 and x=5, x=(5+5)%5 = 10%5 = 0, or the other side of the grid
    y = (y+ysize_)%ysize_;
    if(currentgen_[y][x] == 'X') (*count)++;
}

// Performs mirror return. Takes yx coordinates as ints, and a pointer to the number of neighbors
void Grid::MirrorReturn(int y, int x, int* count){
    x = ((x==-1) || (x==xsize_)) ? abs(x)-1 : x; // e.g. if grid.length=5 and x=-1, x=abs(-1)-1 = 1-1 = 0
    y = ((y==-1) || (y==ysize_)) ? abs(y)-1 : y; // if grid.length=5 and x=6, x=abs(6)-1 = 6-1 = 5
    if(currentgen_[y][x] == 'X') (*count)++;
}

// Reads the first grid into GameRules and outputs results into second grid
// Takes two pointers to character grids, one for the source and one for the output
void Grid::CopyContents(char*** source, char*** destination){
    for (int y = 0; y < ysize_; ++y)
        for (int x = 0; x < xsize_; ++x)
            // return the number of neighbors for each yx coordinate, checks the game rules to see if it's alive or not,
            // and then saves the result to the destination grid
            (*destination)[y][x] = GameRules::Evaluate(ReturnSurrounding(x,y), (*source)[y][x]);
}
