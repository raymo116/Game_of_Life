#ifndef F_IMPORT
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class fileImporter
{
public:
    fileImporter(string fp);
    fileImporter();
    void openFile(string filepath, char*** currentGen, char*** nextGen, int* xSize, int* ySize);
    string filepath;
private:
    char check(char character);
    int parseNum(ifstream* currentStream);
};

#endif
