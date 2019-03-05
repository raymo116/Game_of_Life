#include <iostream>
#include <string>
#include "grid.h"
#include "file_importer.h"

using namespace std;

// This acts as an outline for user input
// It takes in a pointer to the parameter you want to change, a pointer to a string to save the
// input to, and an int for the number of options being offered (either 2 or 3)
void ChoiceOutline(int* param, string* in, int options);

// This program will run the game of life in one of three modes (classic, donut, or mirror) and
// will either write to the screen or export to a file. It takes no commandline parameters
int main() {
    string input = "";
    int mode = 3; // Arbitrary value that won't be used
    int viewmode = 3; // Arbitrary value that won't be used
    int random = 3; // Arbitrary value that won't be used
    int delaylength = -1; // Arbitrary value that won't be used

    // Choose whether to use a map or create a new
    cout << "Choose your map style:\n0) Map\n1) Random:\n";
    ChoiceOutline(&random, &input, 2);

    // Choose what mode you want to play the game in
    cout << "Choose your game mode:\n0) Classic\n1) Donut\n2) Mirror\n";
    ChoiceOutline(&mode, &input, 3);

    // Choose how you want to view the results
    cout << "Choose your viewing mode:\n0) Brief Pause\n1) [Enter]\n2) File Output\n";
    ChoiceOutline(&viewmode, &input, 3);

    // Ask for the delay time
    if(viewmode == 0)
        FileImporter::GetNumber(&delaylength, "n integer for the delay time in ms", true);

    // Create Grid obect and run it
    Grid myGrid(mode, viewmode, random, delaylength);
    myGrid.Run(1000);

    cout << "Please press enter to exit." << endl;
    cin.get();
    return 0;
}

// This acts as an outline for user input
// It takes in a pointer to the parameter you want to change, a pointer to a string to save the
// input to, and an int for the number of options being offered (either 2 or 3)
void ChoiceOutline(int* param, string* in, int options) {
    while((*param) == 3){
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
