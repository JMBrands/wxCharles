#include <iostream>
#include <cassert>

using namespace std;

int naive_power (int x, int n)
{
    if (n > 0) {
        return x * naive_power(x, n - 1);
    }
    return 1;
}

int power (int x, int n)
{
    // part 1.2: implement this function and analyze runtime complexity
    return 0;
}

bool palindrome1 (string text, int i, int j)
{
    // implement this function
    return false;
}

bool palindrome2 (string text, int i, int j)
{
    // implement this function
    return false;
}

bool palindrome3 (string text, int i, int j)
{
    // implement this function
    return false;
}

bool match_chars (string chars, int i, string source, int j)
{
    // implement this function
    return false;
}

#ifndef TESTING
int main ()
{
    // Pre-condition:
    assert(true);
    // Post-condition: user has entered a line of text, and program has printed
    // return value of all palindrome functions on that line of text
    return 0;
}
#endif
