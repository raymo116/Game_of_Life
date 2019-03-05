#ifndef F_IMPORT
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class FileImporter
{
    public:
        FileImporter();
        FileImporter(string filepath);

        void OpenFile(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random);
        void Generate(char*** currentgen, char*** nextgen, int* xsize, int* ysize);
        static void GeneralInit(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random);
        static void GenerateNew(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize);
        static void GetNumber(int* currentnum, string myparam, bool isint);
        static void TestPath(string* path);

        string filepath_;
        string outpath_;
    private:
        char Check(char character);
        int ParseNum(ifstream* currentstream);
};

#endif
