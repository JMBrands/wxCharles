#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.1415926;  // the number pi
const double EPS = 0.00001;   // the precision used in the test (main)

/********************************************************************
    Bonus assignment: computing approximations of sinus and cosinus
********************************************************************/

unsigned long long factorial(unsigned int x)
{    
    if (x == 1 || x == 0) // Checks if x is 1 or 0 and returns 1 if so
    {
        return 1;
    }

    return x*factorial(x-1); // Returns the factorial of x-1 * x,
    // This calls the function again until x is 1, then it multiplies everything

}

double power(double x, unsigned int y)
{
    if (y == 0) // Checks if the exponent y is 0 and returns 1 if so
    {
        return 1;
    }

    return x*power(x,y-1); // Returns x to the power of y-1
    // This calls the function again until y is 1, then it multiplies everything 
}

// sinus (x,eps,max_no_steps) computes and prints the approximations of sin (`x`), with an accuracy of `eps` and at most `max_no_steps`
void sinus (double x, double eps, int max_no_steps)
{
    double output = 0;

    for (int i = 1; i < 2* max_no_steps; i+=2) // Increases i by 2 every iteration because i isn't needed when even
    {
        if (i % 4 == 1) { // Checks if the current iteration is even (i % 4 = 1) or odd (i % 4 = 3)
            output += power(x,i)/factorial(i); // If the current iteration is even, add the difference to the approximation
        }
        else {
            output -= power(x,i)/factorial(i); // If the current iteration is odd, subtract the difference from the approximation
        }
        cout << "x: " << x << ", i: " << i << ", output: " << output << endl;
        if (abs(output-sin(x)) < eps) { // Check if the current approximation has acceptable accuracy and break out of the loop if so
            cout << "sine of " << x << " is " << output << " within precision " << eps << endl;
            break;
        }

    }
    cout << "sine of " << x << " is approximately " << output << endl;
}

// cos (x,eps,max_no_steps) computes and prints the approximations of cos (`x`), with an accuracy of `eps` and at most `max_no_steps`
void cosinus (double x, double eps, int max_no_steps)
{
    double output = 0;
    
    for (int i = 0; i < 2* max_no_steps; i+=2) // Increases i by 2 every iteration because i isn't needed when odd
    {
        if (i % 4 == 0) { // Checks if the current iteration is even (i % 4 = 0) or odd (i % 4 = 2)
            output += power(x,i)/factorial(i); // If the current iteration is even, add the difference to the approximation
        }
        else {
            output -= power(x,i)/factorial(i); // If the current iteration is odd, subtract the difference from the approximation
        }
        cout << "x: " << x << ", i: " << i << ", output: " << output << endl;
        if (abs(output-cos(x)) < eps) { // Check if the current approximation has acceptable accuracy and break out of the loop if so
            cout << "cosine of " << x << " is " << output << " within precision " << eps << endl;
            break;
        }

    }
    cout << "cosine of " << x << " is approximately " << output << endl;
}

int main ()
{
    for (double angle = 0; angle <= PI; angle += PI/10)
    {
        sinus(angle, EPS, 20);
        cout << "Point 2" << endl;
		cout << "sin (" << angle << ") = " << sin (angle) << endl;
    }
    for (double angle = 0; angle <= PI; angle += PI/10)
    {
        cosinus(angle, EPS, 20);
        cout << "Point 2" << endl;
		cout << "cos (" << angle << ") = " << cos (angle) << endl;
    }
    return 0;
}
