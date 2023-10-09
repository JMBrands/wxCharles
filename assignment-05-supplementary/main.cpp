#include <iostream>
#include <fstream>          // for file I/O
#include <sstream>
#include <cassert>          // for assertion checking
#include <set>

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;
set <string> dictionary;

void initialize_words (set<string>& dictionary)
{
    assert(true);
    // Source for words:
    // https://www.ef.com/wwen/english-resources/english-vocabulary/top-3000-words/
    
    ifstream infile("words.txt", ios_base::binary); // ios_base::binary so it doesn't convert LF to CRLF on windows
    string line;
    while (getline(infile, line)) {
        dictionary.insert(line);
    }
}

bool word_exists(string word, set<string> dictionary) {
    
    assert(!dictionary.empty());
    /* post-condition:
        returns whether the word exists in the dictionary
    */
    return dictionary.contains(word);

}

bool file_valid(string file, set<string> dictionary, double precision = 0.5) {

    assert(precision >= 0 && precision <= 1 && file.length() != 0 && !dictionary.empty());
    // post-condition
    // This will return true if a certain part of the words in a file are in a list of words,
    // It returns false when it finds any characters that shouldn't be in the final file or not enough of the words are in the word list.
    // This is the word list we used: https://www.mit.edu/~ecprice/wordlist.10000

    int words, correct = 0;
    int num = 0;
    char c;
    string word;
    while (file.length() > 0) 
    {
        num = 0;

        do {
            c = file[num];
            num ++;
            if (c == 127 || (c < 32 && c != 0 && c != 9 && c != 10 && c != 13)) // makes it a bit faster as these characters will not be in the good file 
                return false;
        }
        while ((c > 64 && c < 91) || (c > 96 && c < 123));
        // cout << file.substr(0,num -1) << ": ";
        if (num > 1) {
            words ++;
            word = file.substr(0, num -1);
            file.erase(0, num);
            // cout << (word_exists(word, dictionary)) << endl;

            if (word_exists(word, dictionary)) {
                correct ++;
            }
        } else {
            file.erase(0, num);
        }
    }
    // cout << (static_cast<double> (correct) / static_cast<double> (words)) << endl; 
    if (static_cast<double> (correct) / static_cast<double> (words)  <= precision) {
        return true;
    }
    else {
        return false;
    }
}

void initialise_pseudo_random (int r)
{
//  pre-condition:
    assert (r > 0 && r <= 65536) ;
/*  post-condition:
    seed has value r.
*/
    seed = r ;
}

int next_pseudo_random_number ()
{
//  pre-condition:
    assert (seed > 0 && seed <= 65536) ;
/*  post-condition:
    result value > 0 and result value <= 65536 and result value != seed at entry of function
*/
    const int seed75 = seed * 75 ;
    int next = (seed75 & 65535) - (seed75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

char rotate_char (char a, int r)
{
    //  Pre-condition:
    assert(r >= 0) ;

    //  Post-condition:
    // a gets decrypted using the number r

    char b;
    if (a < 32) {
        return a;
    }
    else {
        // I am 70% certain that the inverse of the encryption function is the function itself
        // Do not hesitate to check that though
        b = (((a - 32) - (r % (128 - 32))) + 128 - 32) % (128 - 32) + 32;
        return b;
    }

    return '?';
}

void decrypt(ifstream& infile, ostringstream& outstr, int initial_value) {
    //  Pre-condition:
    assert(infile.is_open());
    //  Post-condition:

    initialise_pseudo_random(initial_value);
    int r;
    char c;
    do {
        c = infile.get();
        if (!c == infile.eof()) {
            r = next_pseudo_random_number();
            outstr << rotate_char(c, r);
        }
    } while(!infile.fail());
}

int brute_force_decrypt(string infilename, string outfilename) {
    assert(true);
    // Post-condition
    // This function brute-forces the decryption by trying decryptig with every random seed 
    // And checking with a 10000 word database if the resulting file is a proper english text,
    // When it thinks it's a proper text, it writes the text to a file and returns the seed r

    for (int r = 1; r <= 655535; r++) { // This is the range the random seed is supposed to be in
        cout << r << ": ";
        ifstream infile(infilename, ios_base::binary);
        ostringstream out("", ios_base::binary);
        decrypt(infile, out, r); // Decrypts with seed r
        infile.close();

        if (file_valid(out.str(), dictionary, 0.8)) { // Checks if at least 20% of the word are in word list  
            cout << "valid" << endl;
            ofstream outf("source.txt", ios_base::binary); // Opens output file if the decryption is valid
            outf << out.str();
            outf.close();
            return r;
        } else {
            cout << "invalid" << endl;
        }
    }
}

#ifndef TESTING
int main (int argc, char* argv[])
{
    initialize_words(dictionary);
    for (int r = 1; r < 65536; r += 1) {
        initialise_pseudo_random(r);
        if ((next_pseudo_random_number() - next_pseudo_random_number())%128 == -11100%128) {
            cout << r;
        }
    }
    return 0;
}
#endif
