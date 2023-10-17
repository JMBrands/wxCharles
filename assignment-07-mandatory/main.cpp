#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

const int MAX_NO_OF_TERMS = 100;         // the maximum number of terms to read for a word sequence
const int MAX_NO_OF_WORDS = 25000;       // the maximum number of words to read from a text file

enum Command {enter = 0, content, stop};

bool read_word (ifstream& infile, string& word)
{// precondition:
    assert (infile.is_open());
/*  postcondition:
    result is true only if a word is read from `infile`, and this word is assigned to `word`.
    result is false otherwise, and the value of `word` should not be used.
*/
    infile >> word;
    return !infile.fail();
}

int enter_command (string filename, string content [MAX_NO_OF_WORDS])
{// precondition:
    assert (true);
/*  postcondition:
    if result is a positive number then the text file with file name `filename` 
    has been successfully opened and closed after reading, and result number of words
    have been read from that file (at most MAX_NO_OF_WORDS) and are stored in that order in `content`.
    if result is zero, then either the text file was empty or has not been opened.
*/

    ifstream infile;
    if (infile.is_open()) {
        cout << "open";
        return 0;
    }
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "couldn't open " << filename << endl;
        return 0;
    }
    int i = 0;
    
    while (i < MAX_NO_OF_WORDS && read_word(infile, content[i])) {
        i++;
    }

    infile.close();

    return i;

}

int count_command (string content [MAX_NO_OF_WORDS], int no_of_words, string terms [MAX_NO_OF_TERMS], int no_of_terms)
{// precondition:
    assert(no_of_terms >= 0 && no_of_terms <= MAX_NO_OF_TERMS);
    assert(no_of_words >= 0 && no_of_words <= MAX_NO_OF_WORDS);
/*  postcondition:
    result is the number of occurrences of the word sequence `terms` (which has `no_of_terms` elements) in
     `content` (which has `no_of_words` elements)
    (the result is obviously zero in case `no_of_words` < `no_of_terms`)
*/
    
    int occurences = 0;
    int no_in_seq = 0;

    for (int i = 0; i < no_of_words; i++) {
        if (content[i] == terms[no_in_seq]) {
            if (no_in_seq + 1 == no_of_terms) {
                occurences ++;
                no_in_seq = 0;
            }
            else {
                no_in_seq ++;
            }
        }
        else {
            no_in_seq = 0;
        }
    }

    return occurences;
}

void enter_filename(ifstream& infile)
{
    // precondition:
    assert(!infile.is_open());

    /* postcondition:
       the user inputs a file name that the 
    */
    

    cout << "Please enter the name of the file: " << endl;
    string path;
    getline(cin, path);

    infile.open(path, ios_base::binary);

}

#ifndef TESTING
int main ()
{// precondition:
    assert(true);
/*  postcondition:
    program has presented interactive interface to user, allowing commands to be entered and executed
*/
    ifstream infile;
    string contents [MAX_NO_OF_WORDS];
    string options [3] = {"enter", "content", "stop"};
    string command;
    string filename;
    int no_of_words;

    while (command != options[stop]) {
        cout << "> ";
        cin >> command;

        

        if (command == options[enter]) {
            getline(cin, filename);
            filename = filename.substr(1, ssize(filename));
            no_of_words = enter_command(filename, contents);
            if (no_of_words > 0) {
                cout << "Succesfully read " << no_of_words << " words." << endl;
            }
            else {
                cout << "Failed to open or read file." << endl;
            }
            cout << endl;
        }
        
        else if (command == options[content]) {
            if (no_of_words > 0) {
                for (int i = 0; i < no_of_words; i++) {
                    cout << contents[i] << endl;
                }
            }
            else {
                cout << "No file read. Use enter <filename> to open a file." << endl;
            }
            

            cout << endl;
        }

        else if (command == options[stop]) {
            continue;
        }

        else {
            cout << "That is not a command" << endl;
        }
        
              
        
    }


    return 0;
}
#endif
