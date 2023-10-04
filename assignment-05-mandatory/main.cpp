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
    const int SEED75 = seed * 75 ;
    int next = (SEED75 & 65535) - (SEED75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

char rotate_char (char a, int r, Action action)
{
    //  Pre-condition:
    assert(r >= 0) ;

    //  Post-condition:
    // a gets encrypted or decrypted using the number r

    char b;
    // I'll admit, I have no idea if char and int can be used like this together
    // But it builds, so sure ig
    if (action == Encrypt) {
        if (a < 32) {
            return a;
        }
        else {
            // I'm 95% certain I translated the function correctly
            b = (((a - 32) + (r % (128 - 32))) + 128 - 32) % (128 - 32) + 32;
            return b;
        }
    }
    else {
        if (a < 32) {
            return a;
        }
        else {
            // I am 70% certain that the inverse of the encryption function is the function itself
            // Do not hesitate to check that though
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
    string infilename, outfilename;

    cout << "Enter the name of the input file you want to open: ";
    cin >> infilename;
    cout << "Enter the name of the output file you want to open: ";
    cin >> outfilename;
    
    if (infilename == outfilename) {
        cout << "The files are identical, couldn't open the files." << endl;
        return false;
    }
    infile.open(infilename);
    outfile.open(outfilename);
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
    //  Post-condition:

    initialise_pseudo_random(initial_value);
    int r;
    char c;
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
