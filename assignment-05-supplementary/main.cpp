#include <iostream>
#include <fstream>          // for file I/O
#include <sstream>
#include <cassert>          // for assertion checking
#include <set>
#include <cctype>

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;
set <string> dictionary;

// Decryption algorithm on line 150

void initialize_words (set<string>& dictionary)
{
    assert(true);
    // Source for words:
    // https://www.ef.com/wwen/english-resources/english-vocabulary/top-3000-words/
    
    ifstream infile("words.txt", ios_base::binary); // ios_base::binary so it doesn't convert LF to CRLF on windows
    string line;
    char lastchar = line.back();
    while (getline(infile, line)) {
        if (!isalpha(lastchar)) {
            line.pop_back();
        }
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

bool file_valid(string file, set<string> dictionary, double precision = 0.5, double cancelthreshold = 0.2) {

    assert(precision >= 0 && precision <= 1 && cancelthreshold > 0 && cancelthreshold <= 1 && file.length() > 0 && !dictionary.empty());
    // post-condition
    // This will return true if a certain part of the words in a file are in a list of words,
    // It returns false when it finds any characters that shouldn't be in the final file or not enough of the words are in the word list.
    // This is the word list we used: https://www.mit.edu/~ecprice/wordlist.10000

    int words = 0;
    int correct = 0;
    int num = 0;
    char c;
    string word;
    int totallength = file.length();
    while (file.length() > 0) 
    {
        num = 0;

        do {
            c = file[num];
            num ++;
            if (c == 127 || (c < 32 && c != 0 && c != 9 && c != 10 && c != 13)) // makes it a bit faster as these characters will not be in the good file 
                return false;
        }
        while (isalnum(c));

        if (num > 1) {
            words ++;
            word = file.substr(0, num);

            if (!isalnum(word[num-1])) { // removes a potential non-alphanumeric character after a word
                word = word.substr(0, num-1);
            }
            

            if (word_exists(word, dictionary)) {
                correct ++;
            }
        }
        file.erase(0, num);

        // Below code assumes that if a certain portion of the file is nonsense, the whole file will be
        // This speeds up the decryption a bit, since it only checks part of wrong solutions
        if (static_cast<double> (file.length()) / static_cast<double> (totallength) < 1 - cancelthreshold) {
            if (static_cast<double> (correct) / static_cast<double> (words)  < precision) {
                return false;
            }
        }
    }

        if (static_cast<double> (correct) / static_cast<double> (words)  > precision) {
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
        // No encryption algorithm since not necessary
        /* Decryption algorithm
          _    _ ______ _____  ______ 
        | |  | |  ____|  __ \|  ____|
        | |__| | |__  | |__) | |__   
        |  __  |  __| |  _  /|  __|  
        | |  | | |____| | \ \| |____ 
        |_|  |_|______|_|  \_\______|
        unless you are looking for the full loop, which is on line 176
        */
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
    string output;
    do {
        c = infile.get();
        if (!c == infile.eof()) {
            r = next_pseudo_random_number();
            outstr << rotate_char(c, r);
        }
    } while(!infile.fail());
    
}

int brute_force_decrypt(string infilename) {
    assert(true);
    // Post-condition
    // This function brute-forces the decryption by trying decryptig with every random seed 
    // And checking with a 10000 word database if the resulting file is a proper english text,
    // When it thinks it's a proper text, it writes the text to a file and returns the seed r

    for (int r = 1; r <= 655535; r++) { // This is the range the random seed is supposed to be in
        ifstream infile(infilename, ios_base::binary);
        ostringstream out("", ios_base::binary);
        decrypt(infile, out, r); // Decrypts with seed r
        infile.close();

        if (file_valid(out.str(), dictionary, 0.5, 0.5)) { // Checks if at least 50% of the word are in word list  
            cout << r << ": valid" << endl;
            cout << out.str() << endl;
            ofstream outf("source.txt", ios_base::binary); // Opens output file if the decryption is valid
            outf << out.str();
            outf.close();
            return r;
        } else {
            if (r % 100 == 0) {
                cout << "Checked " << r << " options." << endl;
            }
        }
    }
}


#ifndef TESTING
int main (int argc, char* argv[])
{
    initialize_words(dictionary);
    
    brute_force_decrypt("secret.txt");

    return 0;
}
#endif
