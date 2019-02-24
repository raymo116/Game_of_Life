#ifndef GAME_RULES
#include <iostream>
#include <string>
#include "gameRules.h"

using namespace std;

// Should return whether the spot is blank or not
char gameRules::evaluate(int neighbors)
{
    if(neighbors <= 1)
    {
        //cout << "empty\n";
        return '-';
    }
    else if(neighbors == 2)
    {
        //cout << "no difference\n";
        return 'X';
    }
    else if(neighbors == 3)
    {
        //cout << "cell exists\n";
        return 'X';
    }
    else if(neighbors >= 4)
    {
        //cout << "empty\n";
        return '-';
    }
}

bool gameRules::checkSimilarities(char*** a1, char*** a2, int ySize, int xSize)
{
    // two so it can skip over big open areas easier
    for (int y = 0; y < ySize; y+=2)
    {
        for (int x = 0; x < xSize; x+=2)
        {
            if((*a1)[y][x] != (*a2)[y][x])
                return false;
        }
    }
    for (int y = 1; y < ySize; y+=2)
    {
        for (int x = 1; x < xSize; x+=2)
        {
            if((*a1)[y][x] != (*a2)[y][x])
                return false;
        }
    }
    return true;
}

#endif
