#include <iostream>
#include <cassert>

using namespace std;

// int length (const string& s)
// {
//     // Pre-condition:
//     assert(true);
//     // Post-condition: return value is length of `s` as a signed integer
//     return static_cast<int>(s.length());
// }

void simplify_pattern(string& pattern) {
    assert(true);
    int i;
    string new_pattern;
    bool star, simplifying;
    int dots;
    for (i = 0; i < ssize(pattern); i++) {
        if (pattern.at(i) == '.' || pattern.at(i) == '*') {
            if (!star && pattern.at(i) == '*') {
                star = true;
            }
            if (pattern.at(i) == '.')
                new_pattern.push_back('.');
        } else {
            if (star) {
                new_pattern.push_back('*');
            }
            star = false;
            dots = 0;
            new_pattern.push_back(pattern.at(i));
        }
    }
    if (star) {
        new_pattern.push_back('*');
    }
    pattern = new_pattern;
}

void simplify_wildcards(string& pattern, int location) {
    assert(location < ssize(pattern)-1 || ssize(pattern) <= 1);

    if (ssize(pattern) <= 1) {
        return;
    }

    if (pattern.at(location) == '*') {
        if (pattern.at(location + 1) == '.') {
            swap(pattern.at(location), pattern.at(location+1));
            if (location < ssize(pattern)-1) {
                simplify_wildcards(pattern, location);
            }
        }
        else if (pattern.at(location + 1) == '*') {
            pattern.erase(location,1);
            if (location < ssize(pattern)-1) {
                simplify_wildcards(pattern, location);
            }
        }
    }
    else if (location < ssize(pattern)-2) {
        simplify_wildcards(pattern, location+1);
    }
}

bool match_pattern (string pattern, string source)
{
    if (ssize(pattern) == 0 && ssize(source) == 0) {
        return true;
    }
    if (ssize(source) == 0 && ssize(pattern) == 1 && pattern.at(0) == '*') {
        return true;
    }

    if (ssize(pattern) == 0) {
        return false;
    }
    if (ssize(source) == 0) {
        return false;
    }
    
    simplify_wildcards(pattern, 0); // doesn't fail tests
    //simplify_pattern(pattern); // fails desktop and dots test

    if (pattern.at(0) == source.at(0) || pattern.at(0) == '.') {
        return match_pattern(pattern.substr(1), source.substr(1));
    }

    if (pattern.at(0) == '*') {
        if (ssize(pattern) == 1) {
            return true;
        }
        else if (pattern.at(1) == source.at(0)) {
            if (match_pattern(pattern.substr(2), source.substr(1))) {
                return true;
            }
        }
        
        return match_pattern(pattern, source.substr(1));
        
    }

    return false;
}

#ifndef TESTING
int main ()
{
    // Pre-condition:
    assert(true);
    // Post-condition: user has entered a pattern and source, and program has printed whether pattern matches source

    return 0;
}
#endif
