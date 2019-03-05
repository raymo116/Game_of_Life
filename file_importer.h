#ifndef F_IMPORT
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class FileImporter
{
    public:
        // Default construtor
        FileImporter();
        // Constuctor to set filepath. Takes in a string for a filepath
        FileImporter(string filepath);
        //Create a grid from a file.
        // Takes in a three array pointers (the grid containing the current generation, the grid containing the last generation,
        // and the grid containing the generation from two generations ago), pointers to the size of the grid (x and y), and a
        // bool for whether the grid is randomly generated or not
        void OpenFile(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random);
        //Create a random grid
        // Takes in a three array pointers (the grid containing the current generation, the grid containing the last generation,
        // and the grid containing the generation from two generations ago), and pointers to the size of the grid (x and y)
        static void GenerateNew(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize);
        //Initialize grids
        // Takes in a three array pointers (the grid containing the current generation, the grid containing the last generation,
        // and the grid containing the generation from two generations ago), and pointers to the size of the grid (x and y), and
        // a bool for whether the grid is random or not
        static void GeneralInit(char*** currentgen, char*** nextgen, char*** checkgen, int* xsize, int* ysize, bool random);
        // Function for getting user inputed numbers
        // Takes the pointer to an int for the current number of neighbors, a string to tell what the input is for, and a bool
        // determining whether the number to be saved should be an int or not
        static void GetNumber(int* currentnum, string myparam, bool isint);
        // Simple function for error checking a filepath
        // Takes in a pointer to a filepath variable
        static void TestPath(string* path);

        string filepath_;
        string outpath_;
    private:
        // Takes a character and make sure that the character is valid
        char Check(char character);
        // Takes a pointer to an ifstream and reads the next line as a number
        int ParseNum(ifstream* currentstream);
};

#endif
