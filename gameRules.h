#ifndef GAME_RULES
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace std {
    class gameRules
    {
    public:
        static char evaluate(int neighbors, char currentChar);
        static bool checkSimilarities(char*** a1, char*** a2, int y, int x);
    private:
    };
}
#endif
