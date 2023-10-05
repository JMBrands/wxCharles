#include <iostream>
#include <fstream>          // for file I/O
#include <cassert>          // for assertion checking

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;

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
    // Lack of comments, very sad
    const int SEED75 = seed * 75 ;
    int next = (SEED75 & 65535) - (SEED75 >> 16) ;
    // Makes sure seed > 0 and seed <= 65536
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

char rotate_char (char a, int r, Action action)
{
    //  Pre-condition:
    assert(r >= 0) ;

    /*  Post-condition:
        result value >= 0, result value < 128,
        result value = a IF a < 32,
        result value = a encrypted with r IF a >= 32 AND action = Encryot,
        result value = a decrypted with r IF a >= 32 AND action = Encrypt
    */
    char b;
    if (action == Encrypt) {
        if (a < 32) {
            // If a < 32 gets encrypted, file might get corrupted
            return a;
        }
        else {
            // Encrypts a with the formula given in the assignment
            b = (((a - 32) + (r % (128 - 32))) + 128 - 32) % (128 - 32) + 32;
            return b;
        }
    }
    else {
        if (a < 32) {
            // If a < 32 gets encrypted, file might get corrupted
            return a;
        }
        else {
            // Decrypts a with the formula given in the assignment
            b = (((a - 32) - (r % (128 - 32))) + 128 - 32) % (128 - 32) + 32;
            return b;
        }
    }

    return '?';
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//  Pre-condition:  
    assert(!infile.is_open() && !outfile.is_open());
//  Post-condition:
    // Assigns 2 files to infile and outfile


    string infilename, outfilename;
    // Handles the input
    cout << "Enter the name of the input file you want to open: ";
    cin >> infilename;
    cout << "Enter the name of the output file you want to open: ";
    cin >> outfilename;
    // Checks for double files
    if (infilename == outfilename) {
        cout << "The files are identical, couldn't open the files." << endl;
        return false;
    }
    // Actually opens the files
    infile.open(infilename);
    outfile.open(outfilename);
    // Error handling
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

Action get_user_action ()
{// Pre-condition:
    assert ( true ) ;
/*  Post-condition:
    result is the Action that the user has indicated that the program should encrypt / decrypt
*/
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "y" || answer == "Y")
        return Encrypt;
    else
        return Decrypt;
}

int initial_encryption_value ()
{// Pre-condition:
    assert (true) ;
/*  Post-condition:
    result is a value between 0 and 65355 (both inclusive)
*/
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
    //  Pre-condition:
    assert(infile.is_open() && outfile.is_open());
    /*  Post-condition:
        Encrypts the file if action is Encrypt, otherwise it will decrypt the file
        If the file gets encrypte
ohs lliw ti 
    */
    initialise_pseudo_random(initial_value);
    int r;
    char c;
    // Encodesh/decodes each character in the file
    do {
        c = infile.get();
        if (!c == infile.eof()) {
            r = next_pseudo_random_number();
            outfile << rotate_char(c, r, action);
        }
    } while(!infile.fail());
}

#ifndef TESTING
int main ()
{
    const Action ACTION = get_user_action();
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl;
        return -1;
    }
    const int INITIAL_VALUE = initial_encryption_value ();
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    input_file.clear ();
    output_file.clear ();
    input_file.close ();
    output_file.close ();

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed successfully. The output might be incorrect." << endl;
        return -1;
    }
    return 0;
}
#endif
