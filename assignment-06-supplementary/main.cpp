#include <iostream>
#include <fstream>
#include <cassert>

// Support for the animation framework.
#include "animation.h"

using namespace std;

enum Cell {Dead=0, Live};                         // a cell is either Dead or Live (we use the fact that dead = 0 and live = 1)

const char DEAD             = '.' ;               // the presentation of a dead cell (both on file and screen)
const char LIVE             = '*' ;               // the presentation of a live cell (both on file and screen)
const int NO_OF_ROWS        = 40 ;                // the number of rows (height) of the universe (both on file and screen)
const int NO_OF_COLUMNS     = 60 ;                // the number of columns (width) of the universe (both on file and screen)

#ifndef TESTING
int main ()
{
    // implement an interactive Game of Live application
    return 0;
}
#endif
