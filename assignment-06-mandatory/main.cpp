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
    // TODO: Pre-/Post-conditions

    ifstream infile(filename, ios_base::binary); // ios_base::binary to prevent converting LF to CRLF on windows

    if (infile.fail()) {
        return false;
    }

    int row, col;
    char c;
    for (row = 0; row < NO_OF_ROWS; row++) {
        for (col = 0; col < NO_OF_COLUMNS; col++) {
            do {
                c = infile.get();
                if (c != '.' && c != '*' && c != '\n') {
                    return false;
                }
            } while (c != '.' && c != '*');
            switch (c) {
                case '.':
                    universe[row][col] = Dead;
                    break;
                case '*':
                    universe[row][col] = Live;
                    break;
                default:
                    return false;
            }
        }
    }
    infile.close();
    return true;
}

void show_universe (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // TODO: Pre-/Post-conditions

    int row, col;
    for (row = 0; row < NO_OF_ROWS; row++) {
        for (col = 0; col < NO_OF_COLUMNS; col++) {
            switch (universe[row][col]) {
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
    // TODO: Post-condition

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
    // TODO: Pre-/Post-conditions
    
    int row, col, neighbours;
    Cell current;
    for (row = 0; row < NO_OF_ROWS; row++) {
        for (col = 0; col < NO_OF_COLUMNS; col++) {
            current = cell_at(now, row, col);
            neighbours = check_neighbours(now, row, col);
            if (!current && neighbours == 3) {
                next[row][col] = Live;
            } else if (!current && neighbours != 3) {
                next[row][col] = Dead;
            }
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
        }
    }
    show_universe(next);
}

#ifndef TESTING
int main ()
{
    return 0;
}
#endif
