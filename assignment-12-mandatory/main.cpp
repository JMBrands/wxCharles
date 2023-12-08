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
    if (name.at(0) == ' ') {
        name = name.substr(1);
    }
    gift = {price, name};
    return in;
}

ostream& operator<< (ostream& out, const Gift& gift) {
    out  << static_cast<float>(gift.price)/100 << " euros, ";
    out << gift.name;
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
// precondition:
    assert(!store.eof());
/* post-condition:
    giftstore gets filled with all the items in store
*/
    Gift gift;
    while (store.peek() != EOF) {
        store >> gift;
        giftstore.inventory.push_back(gift);
    }
}

Gift find_gift(string giftname, const Store& store) {
// precondition:
    assert(true);
/* post-condition:
    if a gift with the name giftname is in store,
    it will get returned, otherwise return an empty gift
*/
    for (Gift gift : store.inventory) {
        if (gift.name == giftname) {
            return gift;
        }
    }
    return {};
}

void read_available_wishlist(istream& list, Wishlist& wishlist, const Store& store) {    
// precondition:
    assert(!list.eof());
/* post-condition:
    wishlist gets filled with every item in store that's also on list
*/
    list >> wishlist.budget;
    string giftname;
    Gift gift;
    Gift not_found = {};
    while (!list.eof()) {
        getline(list, giftname);
        gift = find_gift(giftname, store);
        if (gift != not_found) {
            wishlist.gifts.push_back(gift);
        }
    }
}

void show(const Wishlist& list, cents remaining) {
// precondition:
    assert(true);
/* post-condition:
    prints the entire wishlist, and the budget remaining on it
*/
    for (Gift gift : list.gifts) {
        cout << gift;
        cout << endl;
    }
    cout << "Budget remaining: " << remaining << " cents" << endl;
}

cents gifts(const Wishlist& list, Wishlist& current, int index, cents budget, Wishlist& optimal) {
// precondition:
    assert(true);
/* post-condition:
    optimal is the list with the least amount of budget remaining, 
    made from only items on list
*/

    if (index >= ssize(list.gifts)) {
        return -1;
    }
    if (budget < 1) {
        return -1;
    }
    current.gifts.push_back(list.gifts.at(index));
    int budget_with = gifts(list, current, index+1, budget-list.gifts.at(index).price, optimal);
    current.gifts.pop_back();
    int budget_without = gifts(list, current, index+1, budget, optimal);
    
    if (budget_with == -1 && budget_without == -1 && budget < list.budget) {
        if (budget < optimal.budget) {
            //show(current, budget);
            //cout << "optimal budget: " << static_cast<int>(optimal.budget) << endl;
            //cout << endl;
            optimal.budget = budget;
            optimal.gifts = current.gifts;
        }
    }
    
    if (budget_with == -1) {
        if (budget_without != -1) {
            budget = budget_without;
        }
    }
    else if (budget_without == -1) {
        budget = budget_with;
    }
    else {
        budget = min(budget_with, budget_without);
    }
    
    return budget;
}

void calculate_wishlist(string person, string storename, ofstream& out) {
//precondition:
    assert(true);
/* post-condition:
    prints the optimal gift selection for the person,
    when bought at storename. Also sends it to the specified file.
*/
    
    ifstream store(storename+".txt");
    Store giftstore;
    read_store(store,giftstore);
    ifstream Person(person+".txt");
    Wishlist list, cur, solution;
    read_available_wishlist(Person, list, giftstore);
    solution.budget = list.budget;
    gifts(list, cur, 0, list.budget, solution);
    cout << "Best gifts for " << person << ":" << endl;
    show(solution, solution.budget);
    cout << endl;

    out << "Best gifts for " << person << ":" << endl;
    for (Gift gift : solution.gifts) {
        out << gift;
        out << endl;
    }
    out << "Budget remaining: " << solution.budget << " cents" << endl;
    out << endl;
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the gift store has been loaded, and the optimal gift lists of each name
    (Andrew ... Fabienne) has been computed and printed to `cout`
*/
    ofstream best("best_gifts.txt");
    calculate_wishlist("Andrew","giftstore", best);
    calculate_wishlist("Belle","giftstore", best);
    calculate_wishlist("Chris","giftstore", best);
    calculate_wishlist("Desiree","giftstore", best);
    calculate_wishlist("Edward","giftstore", best);
    calculate_wishlist("Fabienne","giftstore", best);

    return 0;
}
#endif
