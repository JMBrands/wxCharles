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



*/

/********************************************************************
    Assignment part 2: Inclusion
********************************************************************/
void inclusion (double e, double v)
{
    float a = 0;
    float b = max(v, (double) 1);
    float x = b;
    if ((a*a) == v) {
        cout << "Inclusion square root of " << v << " is " << a << endl;
    }
    else if ((b*b) == v) {
        cout << "Inclusion square root of " << v << " is " << b << endl;
    }
    else {
        do {
            x = (a+b) / 2;
            if (x*x > v) {
                b = x;
            }
            else {
                a = x;
            }
            //cout << "a, b, x: " << a << ' ' << b << ' ' << x << endl << abs((x*x)-v) << endl;
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
    float x = max(v, (double) 1);
    while (abs((x*x)-v) > e) {
        x = x - ((x*x)-v)/(2*x);
    }
    cout << "Newton Raphson square root of " << v << " is " << x << " for epsilon " << e << endl;

}

int main ()
{
    for (int i = 0; i <= 100; i++) {
        newton_raphson(0.001,i);
    }
    return 0;
}
