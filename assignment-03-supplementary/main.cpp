#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.1415926;  // the number pi
const double EPS = 0.00001;   // the precision used in the test (main)

/********************************************************************
    Bonus assignment: computing approximations of sinus and cosinus
********************************************************************/

int factorial(unsigned int x)
{    
    if (x == 1 || x == 0) 
    {
        return 1;
    }

    unsigned long output = x*factorial(x-1);

    return output;

}

int power(double x, unsigned int y)
{
    if (y == 0)
    {
        return 1;
    }

    double output = x * power(x, y-1);

    return output;
}

// sinus (x,eps,max_no_steps) computes and prints the approximations of sin (`x`), with an accuracy of `eps` and at most `max_no_steps`
void sinus (double x, double eps, int max_no_steps)
{
    double output = 0;
    
    for (int i = 1; i < 2* max_no_steps; i+=2) 
    {
        if (i % 4 == 1) {
            output += power(x, i)/factorial(i);
        }
        else {
            output -= power(x, i)/factorial(i);
        }
        cout << "x: " << x << ", i: " << i << ", output: " << output << endl;
        if (abs(output-sin(i)) < eps) {
            cout << "sine of " << x << " is " << output << " within precision " << eps << endl;
            break;
        }

    }
    cout << "sine of " << x << " is approximately " << output << endl;
}

// cos (x,eps,max_no_steps) computes and prints the approximations of cos (`x`), with an accuracy of `eps` and at most `max_no_steps`
void cosinus (double x, double eps, int max_no_steps)
{
    //implement this function
}

int main ()
{
    for (double angle = 0; angle <= PI; angle += PI/10)
    {
        sinus(angle, EPS, 20);
        cout << "Point 2" << endl;
		cout << "sin (" << angle << ") = " << sin (angle) << endl;
    }
    
    /*for (double angle = 0; angle <= PI; angle += PI/100)
    {
        sinus   (angle, EPS, 20);
		cout << "sin (" << angle << ") = " << sin (angle) << endl;
        cosinus (angle, EPS, 20);
		cout << "cos (" << angle << ") = " << cos (angle) << endl;
    }*/
    return 0;
}
