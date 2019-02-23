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

#endif
