#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Gift {
    int price;
    string type;
    string name;
};

struct Store {
    vector<Gift> inventory;
};

struct Wishlist {
    int budget;
    vector<Gift> gifts;
};

istream& operator>> (istream& in, Gift& gift) {
    int price;
    string type, name;
    in >> price >> type;
    getline(in, name);
    gift = {price, type, name};
    return in;
}

ostream& operator<< (ostream& out, const Gift& gift) {
    out << "€" << static_cast<float>(gift.price)/100 << ", " << gift.type << gift.name;
    return out;
}

ostream& operator<< (ostream& out, const Store& store) {
    for (int i = 0; i < ssize(store.inventory); i++) {
        out << store.inventory.at(i) << endl;
    }
    return out;
}

void read_store(istream& store, Store& giftstore) {
    Gift gift;
    while (!store.eof()) {
        store >> gift; // TODO: make this stop putting random values at the end
        cout << gift << endl;
        giftstore.inventory.push_back(gift);
    }
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the gift store has been loaded, and the optimal gift lists of each name
    (Andrew ... Fabienne) has been computed and printed to `cout`
*/
    Gift test;
    ifstream store("giftstore.txt");
    Store giftstore;
    read_store(store, giftstore);
    cout << giftstore;
    return 0;
}
#endif
