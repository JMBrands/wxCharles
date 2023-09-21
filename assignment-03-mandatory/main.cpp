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
