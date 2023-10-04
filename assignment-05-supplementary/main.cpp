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
    const int seed75 = seed * 75 ;
    int next = (seed75 & 65535) - (seed75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

#ifndef TESTING
int main ()
{
    return 0;
}
#endif
