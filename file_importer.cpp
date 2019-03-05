#include "file_importer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "grid.h"

using namespace std;

// Default construtor
FileImporter::FileImporter(){
    filepath_ = "";
    outpath_ = "";
}

// Constuctor to set filepath. Takes in a string for a filepath
FileImporter::FileImporter(string filepath){
    filepath_ = filepath;
}

//Create a grid from a file.
// Takes in a three array pointers (the grid containing the current generation, the grid containing the last generation,
// and the grid containing the generation from two generations ago), pointers to the size of the grid (x and y), and a
// bool for whether the grid is randomly generated or not
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
                // Skips a character
                inStream.get(character);
            }
            break; // out of the loop
        }
        catch (const invalid_argument){
            cout << "It appears like that file is corrupted. Please try another.\n";
        }
        inStream.close();
    }
}

//Create a random grid
// Takes in a three array pointers (the grid containing the current generation, the grid containing the last generation,
// and the grid containing the generation from two generations ago), and pointers to the size of the grid (x and y)
void FileImporter::GenerateNew(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize){
    //Initialize grids
    GeneralInit(currentgen, nextgen, checkgen, xsize, ysize, true);

    int density = 0;
    // Asks the user for a number and saves an int to density
    GetNumber(&density, " float between 0 and 1 for the density of the grid", false);

    // Generates the first array contents based on the density
    for (int y = 0; y < (*ysize); ++y)
        for (int x = 0; x < (*xsize); ++x)
            (*currentgen)[y][x] = ((rand()%100) < density) ? 'X' : '-';
}

// Takes a character and make sure that the character is valid
char FileImporter::Check(char character){
    character = toupper(character);

    if((character != '-') && (character != 'X') && character != '\n')
        throw invalid_argument("There was an unacceptable character: " + character);
}

// Takes a pointer to an ifstream and reads the next line as a number
int FileImporter::ParseNum(ifstream* currentStream){
    string numstring;
    getline(*currentStream, numstring);
    return stoi(numstring);
}

//Initialize grids
// Takes in a three array pointers (the grid containing the current generation, the grid containing the last generation,
// and the grid containing the generation from two generations ago), and pointers to the size of the grid (x and y), and
// a bool for whether the grid is random or not
void FileImporter::GeneralInit(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random){
    // If it's a random, user-defined map
    if(random){
        GetNumber(xsize, "n integer for the X size", true);
        GetNumber(ysize, "n integer for the Y size", true);
    }

    // Initialize the Y axises of the grids
    *currentgen = new char*[*ysize];
    *nextgen = new char*[*ysize];
    *checkgen = new char*[*ysize];

    // Initialize the X axises of the grids
    for (int y = 0; y < (*ysize); ++y){
        (*currentgen)[y] = new char[*xsize];
        (*nextgen)[y] = new char[*xsize];
        (*checkgen)[y] = new char[*xsize];
    }
}

// Function for getting user inputed numbers
// Takes the pointer to an int for the current number of neighbors, a string to tell what the input is for, and a bool
// determining whether the number to be saved should be an int or not
void FileImporter::GetNumber(int* currentnum, string myparam, bool isint){
    bool running = true;
    string tempstring = "";
    cout << "Please enter a" << myparam << "."<< endl;
    while(running){
        try{
            getline(cin, tempstring);
            // Make sure that each character is either a number or a period
            for (int i = 0; i < tempstring.length(); i++)
                if(((tempstring[i] > 57) || (tempstring[i] < 48)) && (isint || (!isint && (tempstring[i] != '.'))))
                    throw invalid_argument("");

            // Save to int if it should be an int, or turns a float (0<x<1) into an int (0<x<100)
            (*currentnum) = (isint) ? stoi(tempstring) : round(100 * stof(tempstring));

            // Makes sure the number is a percentage
            if((!isint)&&((*currentnum >= 100) || (*currentnum == 0)))
                throw invalid_argument("");

            running = false;
        }
        catch (const invalid_argument){
            cout << '\"' << tempstring << "\" was not a valid input.\nPlease try again:" << endl;
        }
    }
}

// Simple function for error checking a filepath
// Takes in a pointer to a filepath variable
void FileImporter::TestPath(string* path){
    cout << "Please enter an import filepath:\n";
    while(true){
        getline(cin, (*path));
        ifstream myStream(*path); // Create a new filestream
        if(myStream.good()) break; // If it's a real file, then you can break out of the loop
        cout << "That was an invalid filepath. Please try again." << endl;
    }
}
