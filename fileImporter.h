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
    void openFile(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize, bool random);
    void generate(char*** currentGen, char*** nextGen, int* xSize, int* ySize);
    static void generalInit(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize, bool random);
    static void generateNew(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize);
    static void getNumber(int* currentNum, string myString, bool isInt);
    static void testPath(string* path);
    string filepath;
    string outpath;
private:
    char check(char character);
    int parseNum(ifstream* currentStream);
};

#endif
