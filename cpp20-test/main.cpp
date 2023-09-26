#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

struct S {
    int a;
    int b;
};

#ifndef TESTING
int main ()
{
    const int SLEEP_FOR = 1000;
    vector<int> vec = {1, 2, 3};
    S s = { .a = 10, .b = 5 };

    chrono::time_point t1 = chrono::high_resolution_clock::now();

    this_thread::sleep_for(std::chrono::milliseconds(SLEEP_FOR));

    chrono::time_point t2 = chrono::high_resolution_clock::now();

    cout << "Slept for " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << ", expected " << SLEEP_FOR << endl;

    if(ssize(vec) == 3 && s.a == s.b * 2) {
        cout << "All okay" << endl;
    }

    return 0;
}
#endif
