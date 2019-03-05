#ifndef GAME_RULES
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class GameRules
{
public:
    // Returns whether the cell should live, die, or stay the same
    // Takes in a number of neighbors and the character of the current cell
    static char Evaluate(int neighbors, char current);
    // Checks two grids to see if they're the same or not
    // Takes in pointers to two grids, and the y and x sizes of the grid
    static bool CheckSimilarities(char*** a1, char*** a2, int y, int x);
};
#endif
