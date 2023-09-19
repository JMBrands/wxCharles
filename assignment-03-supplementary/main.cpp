#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.1415926;  // the number pi
const double EPS = 0.00001;   // the precision used in the test (main)

/********************************************************************
    Bonus assignment: computing approximations of sinus and cosinus
********************************************************************/
// sinus (x,eps,max_no_steps) computes and prints the approximations of sin (`x`), with an accuracy of `eps` and at most `max_no_steps`
void sinus (double x, double eps, int max_no_steps)
{
    //implement this function
}

// cos (x,eps,max_no_steps) computes and prints the approximations of cos (`x`), with an accuracy of `eps` and at most `max_no_steps`
void cosinus (double x, double eps, int max_no_steps)
{
    //implement this function
}

int main ()
{
    for (double angle = 0; angle <= PI; angle += PI/100)
    {
        sinus   (angle, EPS, 20);
		cout << "sin (" << angle << ") = " << sin (angle) << endl;
        cosinus (angle, EPS, 20);
		cout << "cos (" << angle << ") = " << cos (angle) << endl;
    }
    return 0;
}
