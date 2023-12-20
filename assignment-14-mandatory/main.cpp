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

const int NO_SOLUTION = -1;     // Puzzle has no solution
const int BAD_FORMAT = -2;      // Puzzle field has an invalid format
const int NO_PARENT = -1;       // Index of the parent of the root candidate
const int NO_DEPTH_LIMIT = -1;  // Do not use a depth limit in depth first search

const vector<char> allowedCells{ ICE_CELL, ROCK_CELL, FLAMINGO_CELL, FLAMINGO_ON_RESCUE_CELL, RESCUE_CELL};
// Sets aren't allowed, but definitely the better option, since this is only used for content checking

// We added coloured tiles for linux terminals, and a fallback set for windows
#ifndef _WIN32 // The first set of values makes the strings colored using CSI codes
const string ICE_CELL_PRINT = "\033[46m ";
const string ROCK_CELL_PRINT = "\033[47m ";
const string FLAMINGO_CELL_PRINT = "\033[45m ";
const string FLAMINGO_ON_RESCUE_CELL_PRINT = "\033[42m ";
const string RESCUE_CELL_PRINT = "\033[41m ";
const string RESET_PRINT = "\033[49m";
#else // Fallback for windows, since we had some weird issues there
const string ICE_CELL_PRINT = " ";
const string ROCK_CELL_PRINT = "#";
const string FLAMINGO_CELL_PRINT = "*";
const string FLAMINGO_ON_RESCUE_CELL_PRINT = "%";
const string RESCUE_CELL_PRINT = "@";
const string RESET_PRINT = "";
#endif

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
    vector<vector<char>> board;
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
    for (vector<char> vec : puzzle.board) {
        for (char i : vec) {
            if (i == 'F' || i == 'f') {
                return true;
            }
        }
    }
    
    return false;
}

void print_cell(ostream& os, char cell) 
{// Precondition:
    assert(true);
// Postcondition: the print cell corresponding to the cell has been outputted
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
        default:
            os << '?';
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
        os << RESET_PRINT; // This resets the color on linux.
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
        x = 0;
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
    cout << "width: " << puzzle.width << ", height: " << puzzle.height << endl;
    cout << "x1: " << x1 << ", x2:" << x2 << ", y1: " << y1 << ", y2: "<< y2 << endl;
    assert(x1 < puzzle.width && x2 < puzzle.width && y1 < puzzle.height && y2 < puzzle.height);
/* Postcondition:
    Swaps the tiles at x1,y1 and x2,y2 on the board.
*/

    swap(puzzle.board.at(y1).at(x1),puzzle.board.at(y2).at(x2));

}

void remove_flamingo(Puzzle& puzzle)
{// Precondition:
    //assert(puzzle.flamingo_x == 0 || puzzle.flamingo_x == puzzle.width-1 || puzzle.flamingo_y == 0 || puzzle.flamingo_y == puzzle.height-1);
    // We decided on not using edge detection, because we also use it to delete the flamingo before finishing the level
    assert(true);
// Postcondition: the tile the flamingo is on has been replaced by an ice tile
    puzzle.board.at(puzzle.flamingo_y).at(puzzle.flamingo_x) = ICE_CELL;
}

void move_flamingo_once(Puzzle& puzzle, Action action) 
{// Precondition:
    assert(static_cast<int>(action) < 4);
    // Makes sure the only allowed actions are those where the flamingo moves
    // Also means the switch statement doesn't need a default, since all possibilities are covered

/* Postcondition: the flamingo has moved once in the correct direction and
    the tile it is moving to has been swapped with it (yes, this can swap anything, logic is implemented in move_flamingo).
    If the flamingo would move over the edge, remove it instead (not really useful
    since the logic for that is implemented in move_flamingo as well, but it's a good
    safety mechanism to prevent errors)
*/

    int flamx = puzzle.flamingo_x;
    int flamy = puzzle.flamingo_y;

    switch (action) {
        case MoveEast:
            if (flamx == puzzle.width-1) {
                remove_flamingo(puzzle);
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx+1, flamy);
                puzzle.flamingo_x ++;
            }
            break;
        case MoveWest:
            if (flamx == 0) {
                remove_flamingo(puzzle);
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx-1, flamy);
                puzzle.flamingo_x --;
            }
            break;
        case MoveSouth:
            if (flamy == puzzle.height-1) {
                remove_flamingo(puzzle);
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx, flamy+1);
                puzzle.flamingo_y ++;
            }
            break;
        case MoveNorth:
            if (flamy == 0) {
                remove_flamingo(puzzle);
            }
            else {
                swap_coordinates(puzzle, flamx, flamy, flamx, flamy-1);
                puzzle.flamingo_y --;
            }
            break;
    }
}

void move_flamingo(Puzzle& puzzle, Action action)
{// Precondition:
    assert(static_cast<int>(action) < 4);
    //Makes sure the only available actions are the four moves
    // Also means the switch statement doesn't need a default, since all possibilities are covered

/* Postcondition:
    The flamingo has moved in the direction specified by action until it hits a rock and stops,
    hits the rescue tile and gets on it, removing the flamingo tile and converting the rescue tile,
    or the flamingo goes off the edge, removing it.
*/

    int& flamx = puzzle.flamingo_x;
    int& flamy = puzzle.flamingo_y;
    int dirx, diry;
    switch(action) {
        case MoveEast:
            dirx = 1;
            diry = 0;
            break;
        case MoveWest:
            dirx = -1;
            diry = 0;
            break;
        case MoveSouth:
            dirx = 0;
            diry = 1;
            break;
        case MoveNorth:
            dirx = 0;
            diry = -1;
            break;
    }
    while(flamx+dirx >= 0 && flamx+dirx < puzzle.width && flamy+diry >= 0 && flamy+diry < puzzle.height)
    {
        if (puzzle.board.at(flamy+diry).at(flamx+dirx) == ICE_CELL) {
            move_flamingo_once(puzzle, action);
        }
        else if (puzzle.board.at(flamy+diry).at(flamx+dirx) == RESCUE_CELL) {
            remove_flamingo(puzzle);
            flamx += dirx;
            flamy += diry;
            puzzle.board.at(flamy).at(flamx) = FLAMINGO_ON_RESCUE_CELL;
            return ;
        }
        else if (puzzle.board.at(flamy+diry).at(flamx+dirx) == ROCK_CELL) {
            return ;
        }
    }
    
    if (flamx+dirx < 0 || flamx + dirx >= puzzle.width || flamy+diry < 0 || flamy+diry >= puzzle.width) {
        remove_flamingo(puzzle);
    }
    
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
/*
vector<vector<char>> read_field (istream& is)
{// Precondition:
    assert (true);
/*  Postcondition: return value is the field that has been read from `is`
* /
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

    return field;
}
*/

/*
 * Breath first search
 */

bool try_move(Puzzle& puzzle, Action direction)
{// Precondition:
    assert(static_cast<int>(direction) < 4);
// Postcondition: Returns true if the move will not kill the flamingo.
// Also sets puzzle to the new position. If the flamingo dies, return false and
// keep puzzle the same as it was
    Puzzle attempt = puzzle;
    move_flamingo(attempt, direction);
    if (is_solvable(attempt)) {
        puzzle = attempt;
        return true;
    }
    else {
        return false;
    }
}

void load_queue(vector<vector<Action>>& queue, int level)
{// Precondition:
    assert(level > 0);
    assert(level > 1 || ssize(queue) == 0); // Queue should be empty at level 1
// Postcondition:
// queue is filled with each possible permutation of north,south,east and west of length level
    if (level > 1) {
        vector<vector<Action>> basis;
        load_queue(basis, level-1);
        for (vector<Action> path : basis) {
            for (int i = 0; i < 4; i ++) {
                if (static_cast<int>(path.at(ssize(path)-1)) % 2 == i % 2) {
                    continue;
                    // Instantly prunes any path where the flamingo goes straight back or straight ahead
                }
                path.push_back(static_cast<Action>(i));
                queue.push_back(path);
                path.pop_back();
            }
        }
    }
    else {
        for (int i = 0; i < 4; i ++) {
            vector<Action> path = {static_cast<Action>(i)};
            queue.push_back(path);
        }
    }
}

int breadth_first (const vector<vector<char>>& field, vector<Puzzle>& solution_path)
{// Precondition:
    assert (true);
/*  Postcondition: return value is the minimal number of steps needed to solve the puzzle represented by `field` in which case `solution_path`
    will contain the solution path, or `BAD_FORMAT` if `field` does not represent a valid puzzle, or `NO_SOLUTION` if the puzzle has no solutions
*/
    // TODO: Implement this function.
    // Remember to first validate and convert `field` into your own Puzzle data structure before starting your search.
    // You are encouraged to implement and use a helper function to perform the actual breadth first search, which given at least the initial Puzzle state produces a solution path.
    // That way you are free to choose your own parameters and their types.

    // As we want to extract the solution path, rather than show it as demonstrated in the lecture, we need to use a slightly different approach:
    /*
        extract_path(C, i):
            if i == NO_PARENT: return {} // empty vector
            else:
                i' = C.at(i).parent_candidate;
                path = extract_path(C, i');
                path.push_back(C.at(i).candidate);
                return path;
    */
   Puzzle puzzle;
   bool successfully_loaded = load_puzzle(field, puzzle);
   if (!successfully_loaded) {
        return BAD_FORMAT;
   }
   vector<vector<Action>> queue;
   
   
    return 0;
}


/*
 * Depth first search
 */

int smallest_index(const vector<int>& vec) {
    int ind = 0;
    for (int i = 0; i < ssize(vec); i++) {
        if (vec.at(i) < vec.at(ind)) {
            ind = i;
        }
    }
    return ind;
}

int dfs(const Puzzle& puzzle, vector<Puzzle>& path, int depth, int depth_limit, int& STATUS) {
    assert(true);

    if (depth == depth_limit) {
        STATUS = NO_SOLUTION;
    }
    vector<Puzzle> directions = {puzzle, puzzle, puzzle, puzzle};
    vector<bool> stati;
    vector<int> depths;
    for (int i = 0; i < 4; i++) {
        stati.push_back(try_move(directions.at(i), static_cast<Action>(i)));
    }
    for (int i = 0; i < 4; i++) {
        if (stati.at(i)) {
            depths.push_back(dfs(directions.at(i), path, depth + 1, depth_limit, STATUS));
        } else {
            
        }
    }
    int smol = smallest_index(depths);
    
}

int depth_first (const vector<vector<char>>& field, vector<Puzzle>& solution_path, int depth_limit)
{// Precondition:
    assert (true);
/*  Postcondition: return value is the minimal number of steps needed to solve the puzzle represented by `field` in which case `solution_path`
    will contain the solution path, or `BAD_FORMAT` if `field` does not represent a valid puzzle, or `NO_SOLUTION` if the puzzle has no solutions
*/
    // TODO: Implement this function.
    // Remember to first validate and convert `field` into your own Puzzle data structure before starting your search.
    // You are encouraged to implement and use a recursive helper function to perform the actual depth first search, which given at least the initial Puzzle state and a depth limit produces a solution path.
    // That way you are free to choose your own parameters and their types.
    Puzzle puzzle;
    if (!load_puzzle(field, puzzle))
        return BAD_FORMAT;
    int _success;
    return dfs(puzzle, solution_path, 0, depth_limit, _success);
}


/*
 * Main
 */

#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the user chosen puzzle file has been read and a solution path printed to `cout` if one exists
*/
    string filename, algorithm;
    int depth_limit, steps;
    vector<Puzzle> solution_path;

    cout << "Enter file to open: ";
    getline(cin, filename);

    ifstream puzzle_file(filename);

    if(!puzzle_file.is_open()) {
        cout << "Failed to open file" << endl;
        return 1;
    }
    Puzzle puzzle;
    read_puzzle(puzzle_file, puzzle);
    vector<vector<char>> field = puzzle.board;

    cout << "Enter algorithm (dfs/bfs): ";
    getline(cin, algorithm);

    if(algorithm == "dfs") {
        cout << "Enter depth limit (" << NO_DEPTH_LIMIT << " = no limit): ";
        cin >> depth_limit;

        steps = depth_first(field, solution_path, depth_limit);
    } else if(algorithm == "bfs") {
        steps = breadth_first(field, solution_path);
    } else {
        cout << "Unknown algorithm" << endl;
        return 2;
    }

    if(steps == BAD_FORMAT) {
        cout << "Puzzle configuration is not valid" << endl;
    } else if(steps == NO_SOLUTION) {
        cout << "No solution found" << endl;
    } else {
        for(int i = 0; i < ssize(solution_path); i++) {
            cout << solution_path.at(i) << endl;
        }

        cout << "Found solution in " << steps << " step(s)" << endl;
    }

    return 0;
}
#endif
