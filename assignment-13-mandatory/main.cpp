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
};

bool operator== (const Puzzle& lhs, const Puzzle& rhs)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `lhs` and `rhs` have the same puzzle state
*/
    // TODO: implement this function
    return false;
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
    // TODO: implement this function
    return false;
}

bool is_solvable (const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if the flamingo in `puzzle` is alive
*/
    // TODO: implement this function
    return false;
}

ostream& operator<< (ostream& os, const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: `puzzle` has been printed to `os`
*/
    // TODO: implement this function
    return os;
}

bool load_puzzle (const vector<vector<char>>& field, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `field` denotes a valid puzzle, in which case `field` has been parsed into `puzzle`
*/
    // TODO: implement this function
    return false;
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
                // TODO: perform puzzle move
                steps++;
                break;
            case MoveEast:
                // TODO: perform puzzle move
                steps++;
                break;
            case MoveSouth:
                // TODO: perform puzzle move
                steps++;
                break;
            case MoveWest:
                // TODO: perform puzzle move
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
