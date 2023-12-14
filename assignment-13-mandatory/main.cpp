#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

const char ICE_CELL = '.';
const char ROCK_CELL = 'r';
const char FLAMINGO_CELL = 'f';
const char FLAMINGO_ON_RESCUE_CELL = 'F';
const char RESCUE_CELL = 'x';
const char UNKNOWN_CELL = '?';

const vector<char> allowedCells{ ICE_CELL, ROCK_CELL, FLAMINGO_CELL, FLAMINGO_ON_RESCUE_CELL, RESCUE_CELL};

const string ICE_CELL_PRINT = "\033[46m ";
const string ROCK_CELL_PRINT = "\033[47m ";
const string FLAMINGO_CELL_PRINT = "\033[45m ";
const string FLAMINGO_ON_RESCUE_CELL_PRINT = "\033[42m ";
const string RESCUE_CELL_PRINT = "\033[41m ";
const string RESET_PRINT = "\033[49m";

enum Action
{
    MoveNorth,
    MoveEast,
    MoveSouth,
    MoveWest,
    Reset,
    Quit,
    Invalid
};

struct Puzzle
{
    // TODO: design your puzzle data structure
    vector<vector<char>> board; // probably temporary
    int width;
    int height;
    int flamingo_x;
    int flamingo_y;
};

bool operator== (const Puzzle& lhs, const Puzzle& rhs)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `lhs` and `rhs` have the same puzzle state
*/
    if (lhs.board != rhs.board) 
        return false;
    
    if (!(lhs.width == rhs.width && lhs.height == rhs.height))
        return false;

    return true;
}

bool operator!= (const Puzzle& lhs, const Puzzle& rhs)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `!(lhs == rhs)`
*/
    return !(lhs == rhs);
}

bool is_solved (const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if the flamingo is at the rescue position in `puzzle`
*/
    for (vector<char> vec : puzzle.board) {
        for (char i : vec) {
            if (i == 'F') {
                return true;
            }
        }
    }
    return false;
}

bool is_solvable (const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if the flamingo in `puzzle` is alive
*/
    bool allowed = false; 
    for (vector<char> vec : puzzle.board) {
        for (char i : vec) {
            if (i == 'F') {
                return false;
            }
            else if (i == 'f') {
                return true; 
                //TODO: check for legal moves
            }
        }
    }
    
    return false;
}

void print_cell(ostream& os, char cell) {
    switch (cell) {
        case ICE_CELL:
            os << ICE_CELL_PRINT;
            break;
        case ROCK_CELL:
            os << ROCK_CELL_PRINT;
            break;
        case FLAMINGO_CELL:
            os << FLAMINGO_CELL_PRINT;
            break;
        case FLAMINGO_ON_RESCUE_CELL:
            os << FLAMINGO_ON_RESCUE_CELL_PRINT;
            break;
        case RESCUE_CELL:
            os << RESCUE_CELL_PRINT;
            break;
    }
}

ostream& operator<< (ostream& os, const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: `puzzle` has been printed to `os`
*/
    for(vector<char> row : puzzle.board) {
        for(char cell : row) {
            print_cell(os, cell);
        }
        os << RESET_PRINT;
        os << endl;
    } 
 
    return os;
}

bool load_puzzle (const vector<vector<char>>& field, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `field` denotes a valid puzzle, in which case `field` has been parsed into `puzzle`
*/
    int rowlength = ssize(field.at(0));
    int amount_of_flamingos = 0;
    int flamx, flamy;
    int x = 0;
    int y = 0;
    for (vector<char> vec : field) {
        if (ssize(vec) != rowlength) {
            cout << "This puzzle is not a rectangle" << endl;
            return false;
        }
        
        bool allowed = false;
        for (char i : vec) {
            allowed = false;
            for (char comparison : allowedCells) {
                if (i == comparison) {
                    allowed = true;
                }
            }
            if (!allowed) {
                cout << "This puzzle contains an illegal character, namely "  << i << endl;
                return false;
            }
            if (i == FLAMINGO_CELL || i == FLAMINGO_ON_RESCUE_CELL) {
                amount_of_flamingos ++;
                flamx = x;
                flamy = y;
            }
            x++;
        }
        y++;
    }
    if (amount_of_flamingos != 1) {
        cout <<  "This puzzle contains an illegal amount of flamingos, namely " << amount_of_flamingos << endl;
        return false;
    }

    puzzle.board = field;
    puzzle.width = rowlength;
    puzzle.height = ssize(field);
    puzzle.flamingo_x = flamx;
    puzzle.flamingo_y = flamy;

    return true;
}

bool read_puzzle (istream& is, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if a valid puzzle has been read from `is`, in which case it is stored in `puzzle`
*/
    vector<vector<char>> field;
    vector<char> line;
    char c;

    // Convert `is` to a 2d array of chars.
    while(is.get(c)) {
        if(c == '\n') {
            field.push_back(line);
            line = {};
        } else {
            line.push_back(c);
        }
    }

    if(!line.empty()) {
        field.push_back(line);
    }

    // Attempt to parse the 2d arrays of chars into a proper puzzle.
    return load_puzzle(field, puzzle);
}

bool open_puzzle (string file, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if a puzzle has been successfully read from filename `file` into `puzzle`
*/
    ifstream fs(file);

    if(!fs.is_open()) {
        cout << "Failed to open file" << endl;
        return false;
    } else if(!read_puzzle(fs, puzzle)) {
        cout << "Failed to read puzzle" << endl;
        return false;
    }

    cout << "Loaded the puzzle shown below:\n";
    cout << puzzle << endl;

    return true;
}

void swap_coordinates(Puzzle& puzzle, int x1, int y1, int x2, int y2)
{// Precondition:
    assert(x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0);
    assert(x1 < puzzle.width && x2 < puzzle.width && y1 < puzzle.height && y2 < puzzle.height);
/* Postcondition:
    swaps the tiles at x1,y1 and x2,y2 */

    swap(puzzle.board.at(y1).at(x1),puzzle.board.at(y2).at(x2));

}

void remove_flamingo(Puzzle& puzzle)
{// Precondition:
    assert(puzzle.flamingo_x == 0 || puzzle.flamingo_x == puzzle.width-1 || puzzle.flamingo_y == 0 || puzzle.flamingo_y == puzzle.height-1);
    //assert(true);
// Postcondition: the tile the flamingo is on has been replaced by an ice tile
    puzzle.board.at(puzzle.flamingo_y).at(puzzle.flamingo_x) = ICE_CELL;
}

bool move_flaming0_once(Puzzle& puzzle, Action action) 
{// Precondition:
    assert(static_cast(action) < 4);

    int flamx = puzzle.flamingo_x;
    int flamy = puzzle.flamingo_y;

    switch (action) {
        case MoveEast:
            if (flamx == puzzle.width-1) {
                remove_flamingo(puzzle);
                return false;
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx+1, flamy);
                puzzle.flamingo_x ++;
            }
            break;
        case MoveWest:
            if (flamx == 0) {
                remove_flamingo(puzzle);
                return false;
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx-1, flamy);
                puzzle.flamingo_x --
            }
            break;
        case MoveSouth:
            if (flamy == puzzle.height-1) {
                remove_flamingo(puzzle);
                return false;
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx, flamy+1);
                puzzle.flamingo_y ++;
            }
            break;
        case MoveNorth:
            if (flamy == 0) {
                remove_flamingo(puzzle);
                return false;
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx, flamy)-1;
                puzzle.flamingo_x --
            }
            break;
    }
    return true;
}

void move_flamingo(Puzzle& puzzle, Action action)
{// Precondition:
    assert(static_cast(action) < 4);

    

}

Action get_action ()
{// Precondition:
    assert (true);
/*  Postcondition: return value is action chosen by user.
*/
    cout << "Pick an action: " << endl;
    cout << "'n': Move north" << endl;
    cout << "'e': Move east" << endl;
    cout << "'s': Move south" << endl;
    cout << "'w': Move west" << endl;
    cout << "'r': Reset" << endl;
    cout << "'q': Quit" << endl;
    cout << "> ";

    char c;
    cin >> c;

    switch(c) {
        case 'n': return MoveNorth;
        case 'e': return MoveEast;
        case 's': return MoveSouth;
        case 'w': return MoveWest;
        case 'r': return Reset;
        case 'q': return Quit;
        default:  return Invalid;
    }
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the user chosen puzzle file has been read and played.
*/
    string file;
    Puzzle puzzle;
    puzzle = {
        {
            {'.','.','.'},
            {'f','F','x'},           
            {'r','r','r'},
        }
    };
    //ct << puzzle << endl;
    cout << "Enter file to open: ";
    getline(cin, file);

    if(!open_puzzle(file, puzzle)) {
        return 1;
    } else if(is_solved(puzzle)) {
        cout << "This puzzle is already solved!" << endl;
        return 0;
    }

    Puzzle initial_puzzle = puzzle;
    int steps = 0;
    Action action;

    while((action = get_action()) != Quit) {
        switch(action) {
            case MoveNorth:
            case MoveEast:
            case MoveSouth:
            case MoveWest:
                
                steps++;
                break;
            case Reset:
                puzzle = initial_puzzle;
                steps = 0;
                break;
            case Invalid:
            case Quit: // dummy case to suppress compiler warning
                cout << "Invalid action" << endl;
                break;
        }

        cout << puzzle << endl;

        if(is_solved(puzzle)) {
            cout << "Congratulations, you have completed the puzzle in " << steps << " steps!" << endl;
            return 0;
        } else if(!is_solvable(puzzle)) {
            cout << "Oh no, the flamingo has drowned!" << endl;
            puzzle = initial_puzzle;
            steps = 0;
            cout << puzzle << endl;
        }
    }

    return 0;
}
#endif
