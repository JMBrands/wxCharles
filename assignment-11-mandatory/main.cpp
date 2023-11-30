#include <iostream>
#include <cassert>

using namespace std;

int naive_power (int x, int n)
{
    assert(true);
    /* Post-condition
    returns naive_power of x, n - 1 unless n < 1, then it returns 1
    */
    if (n > 0) {
        return x * naive_power(x, n - 1);
    }
    return 1;
}

int power (int x, int n)
{//precondition
    assert(n >= 0);
/* post-condition:
    returns the power n of x, with O(log n).
*/
    if (n % 2 == 0 && n > 2) {
        return power(power(x, n/2), 2);
    }
    if (n > 0) {
        return x * power(x, n-1);
    }
    return 1;
}

bool palindrome1 (string text, int i, int j)
{
    assert(i >= 0 && (j < ssize(text) || ssize(text)== 0));
    /* Post-condition
    returns true if j - i < 1, 
    not i == j because then it wouldn't reurn true on strings with an even amount of characters.
    returns palindrome(text, i+1, j-1) if the characters at i and j are the same.
    returns false if neither of the
    */
    if (j - i < 1) {
        return true;
    }
    if (text.at(i) == text.at(j)) {
        return palindrome1(text, i+1, j-1);
    }
    return false;
}

char lower(char c) {
    if (c > 64 && c < 91) {
        return c + 32;
    }
    return c;
}

bool palindrome2 (string text, int i, int j)
{
    if (j - i < 1) {
        return true;
    }
    if (lower(text.at(i)) == lower(text.at(j))) {
        return palindrome2(text, i+1, j-1);
    }
    return false;
}

bool palindrome3 (string text, int i, int j)
{
    if (j - i < 1 || i > j) {
        return true;
    }
    cout << i << ": " << text.at(i) << " " << j << ": " << text.at(j) << endl;
    switch (text.at(i)) {
        case ' ':
        case '.':
        case ',':
        case ':':
        case ';':
        case '\'':
        case '!':
        case '?':
        case '-':
            return palindrome3(text, i + 1, j);
    }
    switch (text.at(j)) {
        case ' ':
        case '.':
        case ',':
        case ':':
        case ';':
        case '\'':
        case '!':
        case '?':
        case '-':
            return palindrome3(text, i, j - 1);
    }
    if (lower(text.at(i)) == lower(text.at(j))) {
        return palindrome3(text, i+1, j-1);
    }
    return false;
}

bool match_chars (string chars, int i, string source, int j)
{// pre-condition:
    assert(true);
/* post-condition:
    Returns true if every character in chars is in .
    They have to be in order, but not next to eachother.
*/

    if (i > 0 || j > 0) {
        if (i >= ssize(chars) || j >= ssize(source)) {
            return false;
        }
        match_chars(chars.substr(i), 0, source.substr(j), 0);
    }
    if (ssize(chars) == 0) {
        return true;
    }
    if (ssize(source) == 0 || ssize(chars) > ssize(source)) {
        return false;
    }
    if (chars.at(0)==source.at(0)) {
        return match_chars(chars.substr(1), 0, source.substr(1), 0);
    }
    else {
        return match_chars(chars, 0, source.substr(1), 0);
    }
}

#ifndef TESTING
int main ()
{
    // Pre-condition:
    assert(true);
    // Post-condition: user has entered a line of text, and program has printed
    
    string input;
    cout << "What text do you want to check? " << endl;
    getline(cin, input);

    bool type1 = palindrome1(input, 0, ssize(input)-1);
    bool type2 = palindrome2(input, 0, ssize(input)-1);
    bool type3 = palindrome3(input, 0, ssize(input)-1);

    if (match_chars(" ", 0, input, 0)) {
        input = '"' + input + '"';
    }

    if (type1) {
        cout << input << " is a type 1 palindrome." << endl;
    }
    else {
        cout << input << " is not a type 1 palindrome." << endl;
    }
    if (type2) {
        cout << input << " is a type 2 palindrome." << endl;
    }
    else {
        cout << input << " is not a type 2 palindrome." << endl;
    }
    if (type3) {
        cout << input << " is a type 3 palindrome." << endl;
    }
    else {
        cout << input << " is not a type 3 palindrome." << endl;
    }


    return 0;
}
#endif