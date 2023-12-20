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

struct Puzzle
{
    // TODO: design your puzzle data structure
};

ostream& operator<< (ostream& os, const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: `puzzle` has been printed to `os`
*/
    // TODO: implement this function
    return os;
}

vector<vector<char>> read_field (istream& is)
{// Precondition:
    assert (true);
/*  Postcondition: return value is the field that has been read from `is`
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

    return field;
}


/*
 * Breath first search
 */

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
    return 0;
}


/*
 * Depth first search
 */

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
    return 0;
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

    vector<vector<char>> field = read_field(puzzle_file);

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
