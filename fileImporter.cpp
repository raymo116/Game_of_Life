#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "fileImporter.h"
#include "grid.h"

using namespace std;

fileImporter::fileImporter(string fP){
    filepath = fP;
}

fileImporter::fileImporter(){
    filepath = "";
    outpath = "";
}

void fileImporter::openFile(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize, bool random){
    while(true){
        ifstream inStream;
        try{
            testPath(&filepath);
            inStream.open(filepath);

            *ySize = parseNum(&inStream);
            *xSize = parseNum(&inStream);

            generalInit(currentGen, nextGen, checkGen, xSize, ySize, false);

            char character;
            for (int y = 0; y < (*ySize); ++y){
                for (int x = 0; x < (*xSize); ++x){
                    inStream.get(character);
                    (*currentGen)[y][x] = (*nextGen)[y][x] = check(character);
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

void fileImporter::generateNew(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize){
    generalInit(currentGen, nextGen, checkGen, xSize, ySize, true);

    int density = 0;
    getNumber(&density, " float between 0 and 1 for the density of the grid", false);

    for (int y = 0; y < (*ySize); ++y)
        for (int x = 0; x < (*xSize); ++x)
            (*currentGen)[y][x] = ((rand()%100)<density)?'X':'-';
}

char fileImporter::check(char character){
    character = toupper(character);

    if((character != '-')&&(character != 'X')&& character != '\n')
        throw invalid_argument("There was an unacceptable character entered: " + character);
}

int fileImporter::parseNum(ifstream* currentStream){
    string numString;
    getline(*currentStream, numString);
    return stoi(numString);
}

void fileImporter::generalInit(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize, bool random){
    if(random){
        getNumber(xSize, "n integer for the X size", true);
        getNumber(ySize, "n integer for the Y size", true);
    }

    *currentGen = new char*[*ySize];
    *nextGen = new char*[*ySize];
    *checkGen = new char*[*ySize];

    for (int y = 0; y < (*ySize); ++y){
        (*currentGen)[y] = new char[*xSize];
        (*nextGen)[y] = new char[*xSize];
        (*checkGen)[y] = new char[*xSize];
    }
}

void fileImporter::getNumber(int* currentNum, string myParam, bool isInt){
    bool running = true;
    string tempString = "";
    cout << "Please enter a" << myParam << "."<< endl;
    while(running){
        try{
            getline(cin, tempString);
            for (int i = 0; i < tempString.length(); i++)
                if(((tempString[i] > 57) || (tempString[i] < 48)) && (isInt || (!isInt && (tempString[i] != '.'))))
                    throw invalid_argument("");

            (*currentNum) = (isInt) ? stoi(tempString) : round(100*stof(tempString));

            if((!isInt)&&((*currentNum >= 100) || (*currentNum == 0)))
                throw invalid_argument("");

            running=false;
        }
        catch (const invalid_argument){
            cout << '\"' << tempString << "\" was not a valid input.\nPlease try again:" << endl;
        }
    }
}

void fileImporter::testPath(string* path){
    cout << "Please enter an import filepath:\n";
    while(true){
        getline(cin, (*path));
        ifstream myStream(*path);
        if(myStream.good()) break;
        cout << "That was an invalid filepath. Please try again." << endl;
    }
}
