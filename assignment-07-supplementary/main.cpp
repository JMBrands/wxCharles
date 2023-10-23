#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <set>

using namespace std;

const int MAX_NO_OF_TERMS = 100;         // the maximum number of terms to read for a word sequence
const int MAX_NO_OF_WORDS = 25000;       // the maximum number of words to read from a text file
const int MAX_NO_OF_CHARS = 1000;         // the maximum number of characters to use as parameter for some commands
const char CHAR_CONNECTOR = '-';
const set<char> ALPHABET {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\''};
// We're gonna use a constant set, due to it being very easy to search in
// (and also faster than an array)

enum Command {Enter = 0, Content, Stop, Count, Where, Context};

bool read_word (ifstream& infile, string& word)
{// precondition:
    assert (infile.is_open());
/*  postcondition:
    result is true only if a word is read from `infile`, and this word is assigned to `word`.
    result is false otherwise, and the value of `word` should not be used.
*/
    
    string word_constructor;

    int word_length = 0;
    bool connector_seen = false;


    // The first loop goes until it finds a letter
    while (!ALPHABET.contains(infile.peek())) {
            infile.ignore(1);

            if (infile.fail()) {
                return false;
            }
    }

    // Then, it goes until it cannot 
    while ( ALPHABET.contains(infile.peek()) ||
        (infile.peek() == CHAR_CONNECTOR && connector_seen == false) ) {
            connector_seen = infile.peek() == CHAR_CONNECTOR;
            
            word_constructor += infile.get();
            word_length ++;

            if (infile.fail()) {
                break;
            }
    }

    if (connector_seen == true) { // Removes a trailing connector
        word_constructor = word_constructor.substr(0, ssize(word_constructor) - 1);
    }

    while (!ALPHABET.contains(infile.peek())) {
            infile.ignore();

            if (infile.fail()) {
                break;
            }
    }

    word = word_constructor;
    return ssize(word_constructor) > 0;
}

int find_in_array(char source [MAX_NO_OF_CHARS], char target, int start = 0, int stop = MAX_NO_OF_CHARS - 1)
{// precondition:
    assert (start >= 0 && stop < MAX_NO_OF_CHARS);
/*  postcondition:
    result is the first index the target character is found
    else, return -1
*/
    if (start > stop) {
        return -1;
    }

    int i;
    for(i = start; i <= stop; i++) {
        if (source[i] == target) {
            return i;
        }
    }
    
    return -1;
}

int process_terms(istream& input, string terms [MAX_NO_OF_TERMS])
{// precondition:
    assert (true);
/*  postcondition:
        returns the amount of terms, and fills the array terms with the correct amount
*/

    int next_delim = 0;
    int start_position = 1; // the first character is always a space
    int no_of_terms = 0;
    int input_length;
    char sequence [MAX_NO_OF_CHARS];
    string cpp_sequence;

    input.getline(sequence, MAX_NO_OF_CHARS, '\n');

    cpp_sequence = static_cast<string>(sequence);
    input_length = ssize(cpp_sequence) + 1;

    while (next_delim != -1 && start_position != input_length) {
        next_delim = find_in_array(sequence, ' ', start_position, input_length);
        if (next_delim == -1) {
            next_delim = find_in_array(sequence, '\0', start_position, input_length);
        }
        if (next_delim == -1) {
            continue;
        }

        if (next_delim - start_position == 0) { // allows for more than one space between words
            start_position ++;
            continue;
        }

        cpp_sequence = static_cast<string>(sequence);
        terms[no_of_terms] = cpp_sequence.substr(start_position, next_delim - start_position);
        start_position = next_delim;
        if (start_position == input_length) {
            continue;
        }
        no_of_terms ++;
    }

    return no_of_terms;
}

void display_occurences(int occurences, int no_of_words)
{// precondition:
    assert (no_of_words >= occurences);
/*  postcondition:
    uses cout to display the information given in occurences and no_of_words
*/

    // Using an int for this so it rounds automatically
    int percentage = (occurences * 100)/no_of_words;

    cout << "Found sequence " << occurences << " times in  " << no_of_words << " words (" << percentage << "%)" << endl << endl;

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
        cout << "File is open already";
        return 0;
    }
    infile.open(filename);
    if (!infile.is_open()) {
        cout << "Couldn't open " << filename << endl;
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
    string options [6] = {"enter", "content", "stop", "count", "where", "context"};
    string command;
    string filename;
    string terms [MAX_NO_OF_TERMS];
    int no_of_words = 0;
    int no_of_terms = 0;
    string purge; // used to purge the command line


    while (command != options[Stop]) {
        cout << "> ";
        cin >> command;

        

        if (command == options[Enter]) {
            // Opens the file and reads it to contents
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
        
        else if (command == options[Content]) {
            // Lists the current contents
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

        else if (command == options[Stop]) {
            // Stops the program
            continue;
        }

        else if (command == options[Count]) {
            // Counts the amount of time a sequence occurs in the contents
            if (no_of_words == 0) {
                cout << "No file read. Use enter <filename> to open a file." << endl;
                continue;
            }

            no_of_terms = process_terms(cin, terms);

            int occurences = count_command(contents, no_of_words, terms, no_of_terms);
            display_occurences(occurences, no_of_words);
        }

        else if (command == options[Where]) {
            // Displays the indices where a sequence occurs in the contents
            if (no_of_words == 0) {
                cout << "No file read. Use enter <filename> to open a file." << endl;
                continue;
            }

            no_of_terms = process_terms(cin, terms);
            int no_of_match = 0;
            for (int i = 0; i < no_of_words; i++) {
                if (contents[i] == terms[no_of_match]) {
                    no_of_match ++;
                    if (no_of_match == no_of_terms) {
                        cout << "Found occurence at index " << i - no_of_terms + 2 << endl;
                        no_of_match = 0;
                    }
                }
                else {
                    no_of_match = 0;
                }
            }

            cout << endl;

            int occurences = count_command(contents, no_of_words, terms, no_of_terms);
            display_occurences(occurences, no_of_words);
        }

        else if (command == options[Context]) {
            // Displays all occurences of a sequence in the contents, with context surrounding it
            if (no_of_words == 0) {
                cout << "No file read. Use enter <filename> to open a file." << endl;
                continue;
            }
            int context_amount;
            cin >> context_amount;

            no_of_terms = process_terms(cin, terms);

            cout << context_amount << endl;
            
            int no_of_match = 0;
            for (int i = 0; i < no_of_words; i++) {
                if (contents[i] == terms[no_of_match]) {
                    no_of_match ++;
                    if (no_of_match == no_of_terms) {
                        for (int j = max(0, i-no_of_terms-context_amount+1); j <= min(no_of_words, i+context_amount); j++) {
                            cout << contents[j] << " ";
                        }
                        cout << endl;
                                                
                        no_of_match = 0;
                    }
                }
                else {
                    no_of_match = 0;
                }
            }
            cout << endl;

            int occurences = count_command(contents, no_of_words, terms, no_of_terms);
            display_occurences(occurences, no_of_words);
        }

        else {
            cout << "That is not a command" << endl;
        }
        
        if(command != options[Enter] && command != options[Count]
            && command != options[Where] && command != options[Context]) {
            getline(cin, purge);
        }
        
    }

    return 0;
}
#endif

