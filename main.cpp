#include <iostream>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char const *argv[]) {

    //          size, mode, viewMode, animated
    grid myGrid(20,   2,    0,        true);

    myGrid.run(20);

    return 0;
}
