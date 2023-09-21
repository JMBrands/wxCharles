#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Desktop testing:
Inclusion algorithm:
    v = 0
    a = 0, b = 1
    a*a = v, sqrt(v) = 0;

    v = 1
    a = 0, b = 1
    b*b = v, sqrt(v) = 0;

    v = 0.25
    a = 0, b = 1
    x = 0.5
    |x*x - v| < 0.1
    appr. sqrt(v) = 0.5;

    v = 25
    a = 0, b = 25
    x = 12.5
    x*x > v, b = 12.5
    x = 6.25
    x*x > v, b = 6.25
    x = 3.125
    x*x < v, a = 3.125
    x = 4.6875
    x*x < v, a = 4.6875
    x = 5.46875
    x*x > v, b = 5.46875
    x = 5.078125
    x*x > v, b = 5.078125
    |x*x - v| < 0.1
    appr. sqrt(v) = 5.078125

    v = 20
    a = 0, b = 20
    x = 10
    x*x > v, b = 10
    x = 5
    x*x > v, b = 5
    x = 2.5
    x*x < v, a = 2.5
    x = 3.75
    x*x < v, a = 3.75
    x = 4.375
    x*x < v, a = 4.375
    x = 4.6875
    x*x > v, b = 4.6875
    x = 4.53125
    x*x > v, b = 4.53125
    x = 4.453125
    x*x < v, a = 4.453125
    x = 4.4921875
    x*x > v, b = 4.4921875
    x = 4.47265625
    x*x > v, b = 4.47265625
    |x*x - v| < 0.1
    appr. sqrt(v) = 4.47265625

Newton-Raphson:
    v = 0
    x = 1
    x = 0.5
    x = 0.25
    |x*x - v| < 0.1
    appr. sqrt(v) = 0.25

    v = 1
    x = 1
    |x*x - v| < 0.1
    appr. sqrt(v) = 1
    
    v = 0.25
    x = 1
    x = 0.625
    x = 0.5125
    |x*x - v| < 0.1
    appr. sqrt(v) = 0.5125
    
    v = 25
    x = 25
    x = 13
    x = 7.46154
    x = 5.40603
    x = 5.01525
    x = 5.00002
    |x*x - v| < 0.1
    appr. sqrt(25) = 5.00002

    v = 20
    x = 20
    x = 10.5
    x = 6.20238
    x = 4.71347
    x = 4.47831
    |x*x - v| < 0.1
    appr. sqrt(20) = 4.47831

    As you can see, newton-rhapson only takes roughly 
    half the steps that inclusion needs. 
    (the calculations are harder to do manually though, but that's what computers are for)
*/

/********************************************************************
    Assignment part 2: Inclusion
********************************************************************/
void inclusion (double e, double v)
{
    double a = 0;
    double b = max(v, 1.0);
    double x;
    int n = 0;
    if ((a*a) == v) {
        cout << "Inclusion square root of " << v << " is " << a << endl;
    }
    else if ((b*b) == v) {
        cout << "Inclusion square root of " << v << " is " << b << endl;
    }
    else {
        do {
            x = (a+b) / 2;

            // cout << "n: " << n << "\ta: " << a << "\tx: " << x << "\tb: " << b << endl;
            // The assignment didn't specify we could add labels, but can be re-enabled if you want
            cout << n << "\t" << a << "\t" << x << "\t" << b << endl;
            
            if (x*x > v) {
                b = x;
            }
            else {
                a = x;
            }
            n++;
        }
        while (abs((x*x)-v) > e);
        cout << "Inclusion square root of " << v << " is  " << x << " for epsilon " << e << endl;
    }
}

/********************************************************************
    Assignment part 3: Newton-Raphson
********************************************************************/
void newton_raphson (double e, double v)
{
    double x = max(v, 1.0);
    
    for (int n = 0; abs((x*x)-v) > e; n++) {
        cout << n << '\t' << x << endl;
        x = x - ((x*x)-v)/(2*x);
    }
    cout << "Newton Raphson square root of " << v << " is " << x << " for epsilon " << e << endl;

}

int main ()
{
    for (int i = 0; i <= 50; i++) {
        // Demonstration of the algorithms
        inclusion(0.1, i);
        newton_raphson(0.1, i);
        cout << endl;
    }
    return 0;
}
