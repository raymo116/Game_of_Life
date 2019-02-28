#include <iostream>
#include <string>
#include "grid.h"
#include "fileImporter.h"

using namespace std;

void choiceOutline(int* param, string* in, int options);


int main(int argc, char const *argv[]) {
    string input = "";
    int mode = 3; // Arbitrary value that won't be used
    int viewMode = 3; // Arbitrary value that won't be used
    bool animated = true; // Hard coded
    int random = 3; // Arbitrary value that won't be used
    int delayLength = -1;

    cout << "Choose your map style:\n0) Map\n1) Random:\n";
    choiceOutline(&random, &input, 2);

    cout << "Choose your game mode:\n0) Classic\n1) Donut\n2) Mirror\n";
    choiceOutline(&mode, &input, 3);

    cout << "Choose your viewing mode:\n0) Breif Pause\n1) [Enter]\n2) File Output\n";
    choiceOutline(&viewMode, &input, 3);

    if(viewMode == 0)
        fileImporter::getNumber(&delayLength, "for the delay", true);

    grid myGrid(mode, viewMode, animated, random);

    myGrid.run(1000);

    return 0;
}

void choiceOutline(int* param, string* in, int options) // Options should be either 2 or 3
{
    while((*param)==3)
    {
        getline(cin, (*in));
        if((*in) == "0")
            (*param) = 0;
        else if((*in) == "1")
        {
            (*param) = 1;
        }
        else if((*in) == "2" && (options == 3))
        {
            (*param) = 2;
        }
        else
            cout << "That was not a valid input. Please try again:\n";
    }
}
