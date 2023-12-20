#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <set>

using namespace std;

const char ICE_CELL = '.';
const char PENGUIN_CELL = 'p';
const char PENGUIN_ON_RESCUE_CELL = 'P';
const char FLAMINGO_CELL = 'f';
const char FLAMINGO_ON_RESCUE_CELL = 'F';
const char RESCUE_CELL = 'x';
const char UNKNOWN_CELL = '?';

const set<char> allowedCells = { ICE_CELL, PENGUIN_CELL, PENGUIN_ON_RESCUE_CELL, FLAMINGO_CELL, FLAMINGO_ON_RESCUE_CELL, RESCUE_CELL };
const set<char> moveableCells = { PENGUIN_CELL, PENGUIN_ON_RESCUE_CELL, FLAMINGO_CELL, FLAMINGO_ON_RESCUE_CELL};
// Sets are allowed now :D

enum Action
{
    MoveNorth,
    MoveEast,
    MoveSouth,
    MoveWest,
    SelectFlamingo,
    SelectPenguin,
    Reset,
    Quit,
    Invalid
};

struct Puzzle
{
    vector<vector<char>> board;
    vector<vector<int>> penguinboard;
    int width;
    int height;
    int flamingo_x;
    int flamingo_y;
    int character_x;
    int character_y;
    int selectedchar;
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
    for (vector<char> vec : puzzle.board) {
        for (char i : vec) {
            if (i == 'F' || i == 'f') {
                return true;
            }
        }
    }
    
    return false;
}

ostream& operator<< (ostream& os, const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: `puzzle` has been printed to `os`
*/
    for(vector<char> row : puzzle.board) {
        for(char cell : row) {
            os << cell;
        }
        os << endl;
    } 
 
    return os;
}

bool load_puzzle (const vector<vector<char>>& field, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `field` denotes a valid puzzle, in which case `field` has been parsed into `puzzle`
    If `field` is illegal, the program returns why (primarily used for debugging, but could be useful in final product for level designers)
*/
    int rowlength = ssize(field.at(0));
    int amount_of_flamingos = 0;
    int flamx, flamy;
    int penguincount = 1;
    vector<vector<int>> penguinboard(ssize(field), vector<int>(rowlength, 0));
    int x = 0;
    int y = 0;
    for (vector<char> vec : field) {
        if (ssize(vec) != rowlength) {
            cout << "This puzzle is not a rectangle" << endl;
            return false;
        }
        
        bool allowed = false;
        for (char i : vec) {
            allowed = allowedCells.count(i);
            if (!allowed) {
                cout << "This puzzle contains an illegal character, namely "  << i << endl;
                return false;
            }
            if (i == FLAMINGO_CELL || i == FLAMINGO_ON_RESCUE_CELL) {
                amount_of_flamingos ++;
                flamx = x;
                flamy = y;
            }
            if (i == PENGUIN_CELL || i == PENGUIN_ON_RESCUE_CELL) {
                penguinboard.at(y).at(x) = penguincount;
                penguincount ++;
            }
            x++;
        }
        x = 0;
        y++;
    }
    if (amount_of_flamingos != 1) {
        cout <<  "This puzzle contains an illegal amount of flamingos, namely " << amount_of_flamingos << endl;
        return false;
    }

    puzzle.board = field;
    puzzle.penguinboard = penguinboard;
    puzzle.width = rowlength;
    puzzle.height = ssize(field);
    puzzle.flamingo_x = flamx;
    puzzle.flamingo_y = flamy;
    puzzle.character_x = flamx;
    puzzle.character_y = flamy;
    puzzle.selectedchar = 0;

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

bool get_penguin(const Puzzle& puzzle, int penguin, int& x, int& y)
{// Precondition:
    assert(true);
// Postcondition: if there is a penguin with that int, return true and map x and y
// else, return false
    int curx = 0;
    int cury = 0;
    for (vector<int> row : puzzle.penguinboard) {
        for (int peng : row) {
            if (peng == penguin) {
                x = curx;
                y = cury;
                return true;
            }
            curx ++;
        }
        curx = 0;
        cury ++;
    }
    return false;
}

void display_penguins(const Puzzle& puzzle) 
{// Precondtion:
    assert(true);
// Postcondition: prints the board but with numbers instead of penguins
    int x = 0;
    int y = 0;
    for(vector<char> row : puzzle.board) {
        for(char cell : row) {
            if (cell != PENGUIN_CELL && cell != PENGUIN_ON_RESCUE_CELL) {
                cout << cell;
            }
            else {
                cout << puzzle.penguinboard.at(y).at(x);
            }
            x ++;
        }
        cout << endl;
        x = 0;
        y ++;
    } 

}

char get_tile(const Puzzle& puzzle, int x, int y)
{// Precondition:
    assert(x >= 0 && y >= 0 && x < puzzle.width && y < puzzle.height);
// Postcondition: returns the tile at x,y
    return puzzle.board.at(y).at(x);
}

char set_tile(Puzzle& puzzle, int x, int y, char type)
{// Precondition:
    assert(x >= 0 && y >= 0 && x < puzzle.width && y < puzzle.height);
    assert(allowedCells.count(type) == 1);
// Postcondition: sets the tile at x,y to type. Returns the old one
    char old = puzzle.board.at(y).at(x);
    puzzle.board.at(y).at(x) = type;
    return old;
}

bool move_tile (Puzzle& puzzle, int x, int y, Action direction)
{// Precondition (it's a big one):
    assert(x >= 0 && y >= 0 && x < puzzle.width && y < puzzle.height);
    assert(static_cast<int>(direction) < 4);
    assert(moveableCells.count(get_tile(puzzle, x, y)) == 1);
// Postcondition: the tile (which is a flamingo or penguin) has been moved 1 tile (if allowed)
// If it cannot move any further, return false
    char current = get_tile(puzzle, x, y);
    char remain = ICE_CELL;
    if (current == PENGUIN_ON_RESCUE_CELL) {
        current = PENGUIN_CELL;
        remain = RESCUE_CELL;
        // No support for flamingo on rescue cell, since this will end the game
    }
    bool move_flamingo = false;
    if (current == FLAMINGO_CELL) {
        move_flamingo = true;
    }

    switch (direction) {
        case MoveEast:
            if (x == puzzle.width-1) {
                set_tile(puzzle, x, y, ICE_CELL);
                return false;
            }
            else {
                char target = get_tile(puzzle, x+1, y);
                if (target == ICE_CELL || target == RESCUE_CELL) {
                    if (target == RESCUE_CELL && move_flamingo == true) {
                        current = FLAMINGO_ON_RESCUE_CELL;
                    }
                    set_tile(puzzle, x+1, y, current);
                    set_tile(puzzle, x, y, remain);
                    puzzle.character_x ++;
                    if (current == FLAMINGO_ON_RESCUE_CELL) {
                        return false;
                    }
                    return true;
                }
                return false;
            }
            break;
        case MoveWest:
            if (x == 0) {
                set_tile(puzzle, x, y, ICE_CELL);
                return false;
            }
            else {
                char target = get_tile(puzzle, x-1, y);
                if (target == ICE_CELL || target == RESCUE_CELL) {
                    if (target == RESCUE_CELL && move_flamingo == true) {
                        current = FLAMINGO_ON_RESCUE_CELL;
                    }
                    set_tile(puzzle, x-1, y, current);
                    set_tile(puzzle, x, y, remain);
                    puzzle.character_x --;
                    if (current == FLAMINGO_ON_RESCUE_CELL) {
                        return false;
                    }
                    return true;
                }
                return false;
            }
            break;
        case MoveSouth:
            if (y == puzzle.height-1) {
                set_tile(puzzle, x, y, ICE_CELL);
                return false;
            }
            else {
                char target = get_tile(puzzle, x, y+1);
                if (target == ICE_CELL || target == RESCUE_CELL) {
                    if (target == RESCUE_CELL && move_flamingo == true) {
                        current = FLAMINGO_ON_RESCUE_CELL;
                    }
                    set_tile(puzzle, x, y+1, current);
                    set_tile(puzzle, x, y, remain);
                    puzzle.character_y ++;
                    if (current == FLAMINGO_ON_RESCUE_CELL) {
                        return false;
                    }
                    return true;
                }
                return false;
            }
            break;
        case MoveNorth:
            if (y == 0) {
                set_tile(puzzle, x, y, ICE_CELL);
                return false;
            }
            else {
                char target = get_tile(puzzle, x, y-1);
                if (target == ICE_CELL || target == RESCUE_CELL) {
                    if (target == RESCUE_CELL && move_flamingo == true) {
                        current = FLAMINGO_ON_RESCUE_CELL;
                    }
                    set_tile(puzzle, x, y-1, current);
                    set_tile(puzzle, x, y, remain);
                    puzzle.character_y --;
                    if (current == FLAMINGO_ON_RESCUE_CELL) {
                        return false;
                    }
                    return true;
                }
                return false;
            }
            break;
    }
}

void move_character(Puzzle& puzzle, Action direction)
{// Precondition:
    assert(static_cast<int>(direction) < 4);
// Postcondition: move the current selected character until it hits another one
    bool legal;
    do {
        legal = move_tile(puzzle, puzzle.character_x, puzzle.character_y, direction);
    }
    while (legal == true);
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
    cout << "'f': Select flamingo" << endl;
    cout << "'p': Select penguin" << endl;
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
        case 'f': return SelectFlamingo;
        case 'p': return SelectPenguin;
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
    int selectedchar = 0;
    int charx, chary;
    int temp_character;
    string purge;

    cout << "Selected character: flamingo" << endl;

    while((action = get_action()) != Quit) {

        switch(action) {
            case MoveNorth:
            case MoveEast:
            case MoveSouth:
            case MoveWest:
                move_character(puzzle, action);
                steps++;
                break;
            case SelectFlamingo:
                puzzle.selectedchar = 0;
                puzzle.character_x = puzzle.flamingo_x;
                puzzle.character_y = puzzle.flamingo_y;
                break;
            case SelectPenguin:
                display_penguins(puzzle);
                cout << "Select a penguin" << endl;
                cin >> temp_character;
                getline(cin, purge);
                if (!get_penguin(puzzle, temp_character, charx, chary)) {
                    cout << "That is not a valid penguin!" << endl;
                }
                else {
                    puzzle.selectedchar = temp_character;
                    puzzle.character_x = charx;
                    puzzle.character_y = chary;
                }
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
        cout << "Selected character: ";
        if (puzzle.selectedchar == 0) {
            cout << "Flamingo" << endl;
        }
        else {
            cout << "Penguin " << puzzle.selectedchar << endl;
        }

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
