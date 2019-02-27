#include <iostream>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char const *argv[]) {


    grid myGrid(1,     // mode
                1,     // viewMode
                true,  // animated
                true); // random

    myGrid.run(1000);

    return 0;
}
