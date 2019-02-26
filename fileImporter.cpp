#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "fileImporter.h"

using namespace std;

fileImporter::fileImporter(string fP)
{
    filepath = fP;
}
fileImporter::fileImporter()
{}

void fileImporter::openFile(string fP, char*** currentGen, char*** nextGen, int* xSize, int* ySize)
{
    filepath = fP;

    ifstream myStream;
    myStream.open(filepath);

    *ySize = parseNum(&myStream);
    *xSize = parseNum(&myStream);

    *currentGen = new char*[*ySize];
    *nextGen = new char*[*ySize];

    for (int y = 0; y < (*ySize); ++y)
    {
        (*currentGen)[y] = new char[*xSize];
        (*nextGen)[y] = new char[*xSize];
    }

    char character;
    for (int y = 0; y < (*ySize); ++y)
    {
        for (int x = 0; x < (*xSize); ++x)
        {
            // cout << y << "," << x << endl;
            myStream.get(character);
            (*currentGen)[y][x] = (*nextGen)[y][x] = check(character);
            if(character == '\n') x--;
        }
        myStream.get(character);
    }

    myStream.close();
}

char fileImporter::check(char character)
{
    character = toupper(character);

    if((character != '-')&&(character != 'X'))
    {
        throw invalid_argument("There was an unacceptable character entered: " + character);
    }
}

int fileImporter::parseNum(ifstream* currentStream)
{
    string numString;
    getline(*currentStream, numString);
    return stoi(numString);
}
