#ifndef GAME_RULES

#include "game_rules.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Returns whether the cell should live, die, or stay the same
// Takes in a number of neighbors and the character of the current cell
char GameRules::Evaluate(int neighbors, char current){
    // Any live cell with fewer than two live neighbors dies, as if by underpopulation.
    if(neighbors < 2)
        return '-';
    // Any live cell with two or three live neighbors lives on to the next generation.
    else if(neighbors == 2)
        return current;
    // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
    else if(neighbors == 3)
        return 'X';
    // Any live cell with more than three live neighbors dies, as if by overpopulation.
    else if(neighbors > 3)
        return '-';
}

// Checks two grids to see if they're the same or not
// Takes in pointers to two grids, and the y and x sizes of the grid
bool GameRules::CheckSimilarities(char*** a1, char*** a2, int ySize, int xSize){
    //For every x and y position
    for (int y = 0; y < ySize; ++y)
        for (int x = 0; x < xSize; ++x)
            //Check if they are the same
            if((*a1)[y][x] != (*a2)[y][x])
                return false;

    return true;
}

#endif
