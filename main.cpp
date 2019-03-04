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
    int random = 3; // Arbitrary value that won't be used
    int delayLength = -1;

    cout << "Choose your map style:\n0) Map\n1) Random:\n";
    choiceOutline(&random, &input, 2);

    cout << "Choose your game mode:\n0) Classic\n1) Donut\n2) Mirror\n";
    choiceOutline(&mode, &input, 3);

    cout << "Choose your viewing mode:\n0) Brief Pause\n1) [Enter]\n2) File Output\n";
    choiceOutline(&viewMode, &input, 3);

    if(viewMode == 0)
        fileImporter::getNumber(&delayLength, "n integer for the delay time in ms", true);

    grid myGrid(mode, viewMode, random, delayLength);
    myGrid.run(1000);

    cout << "Please press enter to exit." << endl;
    cin.get();
    return 0;
}

// There should be only 2 or 3 options
void choiceOutline(int* param, string* in, int options) {
    // Arbitrary value that will never be used
    while((*param)==3){
        getline(cin, (*in));
        if((*in) == "0")
            (*param) = 0;
        else if((*in) == "1")
            (*param) = 1;
        else if((*in) == "2" && (options == 3))
            (*param) = 2;
        else
            cout << "That was not a valid input. Please try again:\n";
    }
}
