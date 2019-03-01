#ifndef GAME_RULES
#include <iostream>
#include <string>
#include <cmath>

#include "gameRules.h"

using namespace std;

// Returns whether the cell should live, die, or stay the same
char gameRules::evaluate(int neighbors, char currentChar){
    // Any live cell with fewer than two live neighbors dies, as if by underpopulation.
    if(neighbors < 2)
        return '-';
    // Any live cell with two or three live neighbors lives on to the next generation.
    else if(neighbors == 2)
        return currentChar;
    // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
    else if(neighbors == 3)
        return 'X';
    // Any live cell with more than three live neighbors dies, as if by overpopulation.
    else if(neighbors > 3)
        return '-';
}

bool gameRules::checkSimilarities(char*** a1, char*** a2, int ySize, int xSize){
    for (int y = 0; y < ySize; ++y)
        for (int x = 0; x < xSize; ++x)
            if((*a1)[y][x] != (*a2)[y][x])
                return false;

    return true;
}

#endif
