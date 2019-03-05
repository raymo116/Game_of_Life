#ifndef GAME_RULES
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace std {
    class GameRules
    {
    public:
        static char Evaluate(int neighbors, char current);
        static bool CheckSimilarities(char*** a1, char*** a2, int y, int x);
    private:
    };
}
#endif
