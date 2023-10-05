#include <iostream>
#include <fstream>          // for file I/O
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
        }
        while ((c > 64 && c < 91) || (c > 96 && c < 123));

        if (num > 1) {
            words ++;
            word = file.substr(0, num);
            file.erase(0, num);
            if (word_exists(word, dictionary)) {
                correct ++;
            }
        }
    }
    if (static_cast<double> (correct) / static_cast<double> (words)  >= precision) {
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

bool open_input_and_output_file (ifstream& infile, ofstream& outfile, string infilename, string outfilename)
{
//  Pre-condition:  
    assert(!infile.is_open() && !outfile.is_open());
//  Post-condition:

    if (infilename == outfilename) {
        cout << "The files are identical, couldn't open the files." << endl;
        return false;
    }
    infile.open(infilename, ios_base::binary);
    outfile.open(outfilename, ios_base::binary);
    if (infile.fail()) {
        cout << "The input file failed to open." << endl;
        return false;
    }
    if (outfile.fail()) {
        cout << "The output file failed to open." << endl;
    }
    cout << "Opened the files." << endl;
    return true;
}

void decrypt(ifstream& infile, ofstream& outfile, int initial_value) {
    //  Pre-condition:
    assert(infile.is_open() && outfile.is_open());
    //  Post-condition:

    initialise_pseudo_random(initial_value);
    int r;
    char c;
    do {
        c = infile.get();
        if (!c == infile.eof()) {
            r = next_pseudo_random_number();
            outfile << rotate_char(c, r);
        }
    } while(!infile.fail());
}

#ifndef TESTING
int main ()
{
    initialize_words(dictionary);
    ifstream infile("secret.txt", ios_base::binary);
    ofstream outfile("sources.txt", ios_base::binary);
    
    for (int r = 1; r < 65536; r++) {
        outfile << "r = " << r << endl << endl;
        decrypt(infile, outfile, r);
        outfile << endl;
    }
    return 0;
}
#endif
