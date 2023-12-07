#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

typedef int cents;
struct Gift {
    cents price;
    string name;
};

typedef vector<Gift> Inventory;

struct Store {
    vector<Gift> inventory;
};

struct Wishlist {
    cents budget;
    vector<Gift> gifts;
};

istream& operator>> (istream& in, Gift& gift) {
    cents price;
    string name;
    in >> price;
    getline(in, name);
    gift = {price, name};
    return in;
}

ostream& operator<< (ostream& out, const Gift& gift) {
    out  << static_cast<float>(gift.price)/100 << " euros, " << gift.name;
    return out;
}

ostream& operator<< (ostream& out, const Store& store) {
    for (int i = 0; i < ssize(store.inventory); i++) {
        out << store.inventory.at(i) << endl;
    }
    return out;
}

bool operator== (const Gift& a, const Gift& b) {
    return a.name == b.name && a.price == b.price;
}

void read_store(istream& store, Store& giftstore) {
    Gift gift;
    while (!store.eof()) {
        store >> gift; // TODO: make this stop putting random values at the end
        cout << gift << endl;
        giftstore.inventory.push_back(gift);
    }
    giftstore.inventory.pop_back();
}

Gift find_gift(string giftname, const Store& store) {
    for (Gift gift : store.inventory) {
        if (gift.name == giftname) {
            return gift;
        }
    }
    return {};
}

void read_available_wishlist(istream& list, Wishlist& wishlist, const Store& store) {
    list >> wishlist.budget;
    string giftname;
    Gift gift;
    Gift not_found = {};
    while (!list.eof()) {
        list >> giftname;
        gift = find_gift(giftname, store);
        if (gift != not_found) {
            wishlist.gifts.push_back(gift);
        }
    }
}

void show(Wishlist& list, cents remaining) {
    for (Gift gift : list.gifts) {
        cout << gift << endl;
    }
    cout << "Budget remaining: " << remaining << " cents" << endl;
}

cents gifts(const Wishlist& list, Wishlist& current, int index, cents budget) {
    
    if (index >= ssize(list.gifts)) {
        
        return budget;
    }


    return budget;
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
    ifstream Andrew("Andrew.txt");
    Wishlist list;
    read_available_wishlist(Andrew, list, giftstore);
    show(list, list.budget);


    return 0;
}
#endif
