#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "fileImporter.h"
#include "grid.h"

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

    generalInit(currentGen, nextGen, xSize, ySize);

    char character;

    for (int y = 0; y < (*ySize); ++y)
    {
        for (int x = 0; x < (*xSize); ++x)
        {
            myStream.get(character);
            (*currentGen)[y][x] = (*nextGen)[y][x] = check(character);
            if(character == '\n') x--;
        }
        myStream.get(character);
    }

    myStream.close();
}

void fileImporter::generateNew(char*** currentGen, char*** nextGen, int* xSize, int* ySize)
{

    generalInit(currentGen, nextGen, xSize, ySize);

    int density = 0;
    getNumber(&density, "between 0 and 1 for the density of the grid", false);
    cout << density << endl;

    for (int y = 0; y < (*ySize); ++y)
    {
        for (int x = 0; x < (*xSize); ++x)
        {
            // This doesn't seem to work properly when you only give it a 0.01
            (*currentGen)[y][x] = ((rand()%100)<density)?'X':'-';
        }
    }
}

void fileImporter::generate(char*** currentGen, char*** nextGen, int* xSize, int* ySize)
{

}

char fileImporter::check(char character)
{
    character = toupper(character);

    if((character != '-')&&(character != 'X')&& character != '\n')
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

void fileImporter::generalInit(char*** currentGen, char*** nextGen, int* xSize, int* ySize)
{
    getNumber(xSize, "for the X size", true);
    getNumber(ySize, "for the Y size", true);

    *currentGen = new char*[*ySize];
    *nextGen = new char*[*ySize];

    for (int y = 0; y < (*ySize); ++y)
    {
        (*currentGen)[y] = new char[*xSize];
        (*nextGen)[y] = new char[*xSize];
    }
}

void fileImporter::getNumber(int* currentNum, string myParam, bool isInt)
{
    bool running = true;
    string tempString = "";
    cout << "Please enter an integer " << myParam << ".\n"
    << "If you enter negative number, the absolute value will be taken:" << endl;
    while(running)
    {
        try
        {
            getline(cin, tempString);
            for (int i = 0; i < tempString.length(); i++)
            {
                if(((tempString[i] > 57) || (tempString[i] < 48)) && (tempString[i] != '.'))
                    throw invalid_argument("");
            }

            (*currentNum) = abs((isInt) ? stoi(tempString) : round(100*stof(tempString)));

            if((!isInt)&&((*currentNum >= 100) || (*currentNum == 0)))
                throw invalid_argument("");

            running=false;
        }
        catch (const invalid_argument)
        {
            cout << '\"' << tempString << "\" was not a valid input.\nPlease try again:" << endl;
        }
    }
}
