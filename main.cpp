#include <iostream>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char const *argv[]) {

    //          mode, viewMode, animated
    grid myGrid(1,    0,        true);

    myGrid.run(1000);

    return 0;
}
