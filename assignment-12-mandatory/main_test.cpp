#include "main.cpp"
#include "gtest/gtest.h"

/*
    Write your own unit tests for this assignment.
    Take a look at the documentation on Brightspace to help you out.
    Essentially you want test cases that:
    1. load the gift store
    2. load the respective wish list
    3. compute the optimal gifts
    4. check that the remaining budget has the correct value
*/

TEST(generate_list, generate_list) {
    ifstream giftstore("giftstore.txt");
    Store store;
    read_store(giftstore, store);
    ifstream Andrew("Andrew.txt");
    Wishlist list;
    read_available_wishlist(Andrew, list, store);
    EXPECT_EQ(list.budget, 5000);
}