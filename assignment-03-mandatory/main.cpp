#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
/********************************************************************
    Assignment part 2: Inclusion
********************************************************************/
void inclusion (double e, double v)
{
    float a = 0;
    float b = max(v, 1.0); // If v is below 1, b will be 1, otherwise b will be v
    float x;
    if ((a*a) == v) { // Test if a is already the square root of v
        cout << "Inclusion square root of " << v << " is " << a << endl;
    }
    else if ((b*b) == v) { // Test if b is already the square root of v
        cout << "Inclusion square root of " << v << " is " << b << endl;
    }
    else { // a and b were not the square root of v
        do { // Run the code, then check if x is close enough to the square root of v,
             // We used a do-while loop because x gets defined inside the loop
            x = (a+b) / 2; // take the average of a and b
            if (x*x > v) {
                b = x; // b is x if x was too high
            }
            else {
                a = x; // a is x if x was too low
            }
        }
        while (abs((x*x)-v) > e);
        // The line below runs when the do-while loop above is finished,
        // This will mean the condition has been met and x squared is within acceptable limits of v
        cout << "Inclusion square root of " << v << " is  " << x << " for epsilon " << e << endl;
    }
}

/********************************************************************
    Assignment part 3: Newton-Raphson
********************************************************************/
void newton_raphson (double e, double v)
{
    float x = max(v, 1.0); // If v is below 1, b will be 1, otherwise b will be v
    while (abs((x*x)-v) > e) {
        x = x - ((x*x)-v)/(2*x); 
        // This is the formula for x(i+1) rewritten with f(x) and its derivate function already written out
        // Since we can't use functins with returns yet
    }
    cout << "Newton Raphson square root of " << v << " is " << x << " for epsilon " << e << endl;

}

int main ()
{
    for (int i = 0; i <= 100; i++) {
        inclusion(0.1,i);
    }
    return 0;
}
