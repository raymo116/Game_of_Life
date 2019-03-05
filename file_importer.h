#ifndef F_IMPORT
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class FileImporter
{
public:
    FileImporter(string fp);
    FileImporter();
    void OpenFile(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize, bool random);
    void Generate(char*** currentGen, char*** nextGen, int* xSize, int* ySize);
    static void GeneralInit(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize, bool random);
    static void GenerateNew(char*** currentGen, char*** nextGen, char*** checkGen, int* xSize, int* ySize);
    static void GetNumber(int* currentNum, string myString, bool isInt);
    static void TestPath(string* path);
    string filepath;
    string outpath;
private:
    char Check(char character);
    int ParseNum(ifstream* currentStream);
};

#endif
