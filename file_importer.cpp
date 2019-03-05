#include "file_importer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "grid.h"

using namespace std;

FileImporter::FileImporter(){
    filepath_ = "";
    outpath_ = "";
}

FileImporter::FileImporter(string filepath){
    filepath_ = filepath;
}

//Create a grid from a file
void FileImporter::OpenFile(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random){
    while(true){
        //Create a new stream
        ifstream inStream;
        try{
            //Test and open file
            TestPath(&filepath_);
            inStream.open(filepath_);

            //Get size of grid from file
            *ysize = ParseNum(&inStream);
            *xsize = ParseNum(&inStream);

            //Initialize grids
            GeneralInit(currentgen, nextgen, checkgen, xsize, ysize, false);

            //Read characters into grid
            char character;
            for (int y = 0; y < (*ysize); ++y){
                for (int x = 0; x < (*xsize); ++x){
                    inStream.get(character);
                    //Use the check function for inline error checking
                    (*currentgen)[y][x] = (*nextgen)[y][x] = Check(character);
                    if(character == '\n') x--;
                }
                inStream.get(character);
            }
            break;
        }
        catch (const invalid_argument){
            cout << "It appears like that file is corrupted. Please try another.\n";
        }
        inStream.close();
    }
}

//Create a random grid
void FileImporter::GenerateNew(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize){
    GeneralInit(currentgen, nextgen, checkgen, xsize, ysize, true);

    int density = 0;
    GetNumber(&density, " float between 0 and 1 for the density of the grid", false);

    for (int y = 0; y < (*ysize); ++y)
        for (int x = 0; x < (*xsize); ++x)
            (*currentgen)[y][x] = ((rand() % 100) < density) ? 'X' : '-';
}

//Error checking for characters read from file
char FileImporter::Check(char character){
    character = toupper(character);

    if((character != '-') && (character != 'X') && character != '\n')
        throw invalid_argument("There was an unacceptable character entered: " + character);
}

int FileImporter::ParseNum(ifstream* currentStream){
    string numstring;
    getline(*currentStream, numstring);
    return stoi(numstring);
}

//Initialize grids
void FileImporter::GeneralInit(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random){
    if(random){
        GetNumber(xsize, "n integer for the X size", true);
        GetNumber(ysize, "n integer for the Y size", true);
    }

    *currentgen = new char*[*ysize];
    *nextgen = new char*[*ysize];
    *checkgen = new char*[*ysize];

    for (int y = 0; y < (*ysize); ++y){
        (*currentgen)[y] = new char[*xsize];
        (*nextgen)[y] = new char[*xsize];
        (*checkgen)[y] = new char[*xsize];
    }
}

//Function for getting user inputed numbers
void FileImporter::GetNumber(int* currentnum, string myparam, bool isint){
    bool running = true;
    string tempstring = "";
    cout << "Please enter a" << myparam << "."<< endl;
    while(running){
        try{
            getline(cin, tempstring);
            for (int i = 0; i < tempstring.length(); i++)
                if(((tempstring[i] > 57) || (tempstring[i] < 48)) && (isint || (!isint && (tempstring[i] != '.'))))
                    throw invalid_argument("");

            (*currentnum) = (isint) ? stoi(tempstring) : round(100 * stof(tempstring));

            if((!isint)&&((*currentnum >= 100) || (*currentnum == 0)))
                throw invalid_argument("");

            running = false;
        }
        catch (const invalid_argument){
            cout << '\"' << tempstring << "\" was not a valid input.\nPlease try again:" << endl;
        }
    }
}

//Simple function for error checking a filepath
void FileImporter::TestPath(string* path){
    cout << "Please enter an import filepath:\n";
    while(true){
        getline(cin, (*path));
        ifstream myStream(*path);
        if(myStream.good()) break;
        cout << "That was an invalid filepath. Please try again." << endl;
    }
}
