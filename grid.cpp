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

Grid::Grid(){
    //default is a random grid
    FileImporter::GenerateNew(&currentgen_, &nextgen_, &checkgen_, &xsize_, &ysize_);

    int delaylength = 100;
    gennumber_ = mode_ = viewmode_ = 0;

    waitms_ = (delaylength >= 0) ? delaylength:0;

    ts_.tv_sec = waitms_ / kDelayTime;
    ts_.tv_nsec = (waitms_ % kDelayTime) * pow(kDelayTime, 2);
}

Grid::Grid(int border, int view, bool random, int delaylength){
    if(!random){
        FileImporter myImporter;
        myImporter.OpenFile(&currentgen_, &nextgen_, &checkgen_, &xsize_, &ysize_, random);
    }
    else
        FileImporter::GenerateNew(&currentgen_, &nextgen_, &checkgen_, &xsize_, &ysize_);

    gennumber_ = 0;
    mode_ = border;
    viewmode_ = view;
    waitms_ = (delaylength >= 0) ? delaylength:0;

    ts_.tv_sec = waitms_ / kDelayTime;
    ts_.tv_nsec = (waitms_ % kDelayTime) * pow(kDelayTime, 2);

    if(view == 2) outputfile_.open("mRaymond_cValencia.out");
}

Grid::~Grid(){
    if(currentgen_){
        /*for(int y = 0; y < ysize_; ++y)
            for(int x = 0; x < xsize_; ++x)
                delete[] &(currentgen_[y][x]);*/
        delete[] currentgen_;
    }
    if(nextgen_){
        /*for(int y = 0; y < ysize_; ++y)
            for(int x = 0; x < xsize_; ++x)
                delete[] &(nextgen_[y][x]);*/
        delete[] nextgen_;
    }
    if(checkgen_){
        /*for(int y = 0; y < ysize_; ++y)
            for(int x = 0; x < xsize_; ++x)
                delete[] &(checkgen_[y][x]);*/
        delete[] checkgen_;
    }
    if(outputfile_)
        outputfile_.close();
}

//will run the game specified ammount of times
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

        //Copy every other grid into the checking spot
        if(i % 2 == 0) CopyContents(&currentgen_, &checkgen_);

        //Swap the grids
        addresstemp_ = nextgen_;
        nextgen_ = currentgen_;
        currentgen_ = addresstemp_;

        gennumber_++;
    }

}

void Grid::PrintGrid(){ // Send to console
    if (viewmode_ == 0 || viewmode_ == 1){
        //Dont jump back the first time
        if (gennumber_ > 0){
            for (int y = 0; y < ysize_ + 1 + viewmode_; ++y){
                cout << "\033[F";
            }
        }
        else
            cout << endl;
    }

    cout << "Generation " << gennumber_ << kBlankSpace << endl;
    for (int y = 0; y < ysize_; ++y){
        for (int x = 0; x < xsize_; ++x){
            cout << currentgen_[y][x] << ' ';
        }
        cout << '\n';
    }
}

void Grid::PrintGrid(ofstream* mystream){ // Send to filestream
    (*mystream) << "Generation " << gennumber_ << kBlankSpace << endl;
    for (int y = 0; y < ysize_; ++y){
        for (int x = 0; x < xsize_; ++x){
            (*mystream) << currentgen_[y][x];
        }
        (*mystream) << '\n';
    }
}

int Grid::ReturnSurrounding(int x, int y){
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

            xtemp = x + xscan;
            ytemp = y + yscan;

            //Here we switch on the mode for custom behavoir
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
void Grid::CheckRCError(int x, int y){
    if(((x >= xsize_) || (x < 0)) || (y >= ysize_) || (y < 0))
        throw invalid_argument(("recieved a index outside of the grid: index "+to_string(y)+","+to_string(x)));
}

void Grid::ClassicReturn(int y, int x, int* count){
    if(!(((x < 0) || (y < 0)) || ((x >= xsize_) || (y >= ysize_))))
        if(currentgen_[y][x] == 'X') (*count)++;
}

void Grid::DonutReturn(int y, int x, int* count){
    x = (x+xsize_)%xsize_;
    y = (y+ysize_)%ysize_;
    if(currentgen_[y][x] == 'X') (*count)++;
}

void Grid::MirrorReturn(int y, int x, int* count){
    x = ((x==-1) || (x==xsize_)) ? abs(x)-1 : x;
    y = ((y==-1) || (y==ysize_)) ? abs(y)-1 : y;
    if(currentgen_[y][x] == 'X') (*count)++;
}

//Reads the first grid into GameRules and outputs results into second grid
void Grid::CopyContents(char*** source, char*** destination){
    for (int y = 0; y < ysize_; ++y)
        for (int x = 0; x < xsize_; ++x)
            (*destination)[y][x] = GameRules::Evaluate(ReturnSurrounding(x,y), (*source)[y][x]);
}
