#ifndef GAME_RULES
#include <iostream>
#include <string>

using namespace std;

namespace std {
    class gameRules
    {
    public:
        static char evaluate(int neighbors);
        bool checkSimilarities(char*** a1, char*** a2, int y, int x);
    private:
    };
}
#endif
