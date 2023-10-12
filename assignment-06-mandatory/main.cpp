#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

enum Cell {Dead=0, Live};                         // a cell is either Dead or Live (we use the fact that dead = 0 and live = 1)

const char DEAD             = '.' ;               // the presentation of a dead cell (both on file and screen)
const char LIVE             = '*' ;               // the presentation of a live cell (both on file and screen)
const int NO_OF_ROWS        = 40 ;                // the number of rows (height) of the universe (both on file and screen)
const int NO_OF_COLUMNS     = 60 ;                // the number of columns (width) of the universe (both on file and screen)

// Part 1: get cell in bounded universe
Cell cell_at (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS], int row, int column)
{
    // Pre-condition
    assert(true);
    // Post-condition
    // This function checks if the given row and column are in bounds and returns the cell at those coordinates,
    // If either row or column is out of bounds, the function will return Dead

    if (row < NO_OF_ROWS && row >= 0 && column < NO_OF_COLUMNS && column >= 0) {
        return universe[row][column];
    }
    return Dead;
}

// Part 2: setting the scene
bool read_universe_file (string filename, Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // Pre-condition
    assert(true);
    // Post-condition
    // The functions opens the file at filename, reads its contents and puts them into an array, 
    // If the file isn't properly formatted or couldn't be opened, it will return false,
    // It will return true when the contents of the file have been analysed and the corresponding values have been written to the array

    ifstream infile(filename, ios_base::binary); // ios_base::binary to prevent converting LF to CRLF on windows

    if (infile.fail()) {
        return false; // Returns false if the file couldn't be opened
    }

    int row, col;
    char c;
    for (row = 0; row < NO_OF_ROWS; row++) {
        for (col = 0; col < NO_OF_COLUMNS; col++) {
            do {
                c = infile.get();
                if (c != DEAD && c != LIVE && c != '\n' && c != 13) { // c != 13 sot it doesn't error when it encounters a CR
                    return false; // Returns false if the character isn't a valid character.
                }
            } while (c != DEAD && c != LIVE);
            switch (c) {
                case DEAD:
                    universe[row][col] = Dead;
                    break;
                case LIVE:
                    universe[row][col] = Live;
                    break;
                default:
                    return false; // Returns false if c somehow still isn't a valid character, this is redundant.
            }
        }
    }
    infile.close();
    return true; // Returns true only if the loop has ran without returning
}

void show_universe (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // Pre-condition
    assert(true);
    // Post-condition
    // Runs two loops, one to loop through the outer array, and another to loop through the inner arrays,
    // It then checks the value and prints the corresponding character, 
    // It also prints an endl after every inner array

    int row, col;
    for (row = 0; row < NO_OF_ROWS; row++) {
        for (col = 0; col < NO_OF_COLUMNS; col++) {
            switch (cell_at(universe, row, col)) {
                case Dead:
                    cout << DEAD;
                    break;
                case Live:
                    cout << LIVE;
                    break;
                default:
                    break;
            }
        }
        cout << endl;
    }
}

int check_neighbours(Cell universe [NO_OF_ROWS][NO_OF_COLUMNS], int row, int col) {
    // Pre-condition
    assert(row >= 0 && row < NO_OF_ROWS && col >= 0 && col < NO_OF_COLUMNS);
    // Post-condition
    // Initialises a variable neighbours, 
    // Adds the value of every cell in a 3x3 area around the cell at (row, col) and adds them to neighbours,
    // Then it subtracts the value of the center cell because that cell isn't excluded.
    // The function makes use of the fact that a dead cell has value 0 and a live cell has value 1


    Cell current = cell_at(universe, row,col);
    int neighbours, row_offset, col_offset;
    neighbours = 0;
    for (row_offset = -1; row_offset <= 1; row_offset++) {
        for (col_offset = -1; col_offset <= 1; col_offset++) {
            neighbours += cell_at(universe, row + row_offset, col + col_offset);
        }
    }
    neighbours -= current;
    return neighbours;
}

// Part 3: the next generation
void next_generation (Cell now [NO_OF_ROWS][NO_OF_COLUMNS], Cell next [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // Pre-condition
    assert(true);
    // Post-condition
    /* The function checks every cell in the array now and counts its live neighbours,
    it then applies the rules: 
    1. A live cell dies if it has less than 2 live neighbours
    2. A live cell stays alive if it has 2 or 3 live neighbours
    3. A live cell dies if it has more than 3 live neighbours
    4. A dead cell comes to life if it has exactly 3 live neighbours
    and writes the new value of the cell to the array next*/
    
    int row, col, neighbours;
    Cell current;
    for (row = 0; row < NO_OF_ROWS; row++) {
        for (col = 0; col < NO_OF_COLUMNS; col++) {
            current = cell_at(now, row, col);
            neighbours = check_neighbours(now, row, col);
            if (current) {
                switch (neighbours) {
                    case 2:
                    case 3:
                        next[row][col] = Live;    
                        break;
                    default:
                        next[row][col] = Dead;
                        break;
                }
            }
            else {
                switch (neighbours) {
                    case 3:
                        next[row][col] = Live;
                        break;
                    default:
                        next[row][col] = Dead;
                        break;
                }
            }
        }
    }
}

#ifndef TESTING
int main ()
{
    return 0;
}
#endif
