#include "main.cpp"
#include "gtest/gtest.h"

/* Write your own unit tests where needed */

TEST(checking, initialize_words) {
    EXPECT_NO_THROW (initialize_words(dictionary));
}

TEST(checking, word_exists) {
    initialize_words(dictionary);
    for (string x : dictionary) {
        cout << x << endl;
    } cout << "test" << endl;
    EXPECT_TRUE (word_exists("a", dictionary));
    EXPECT_TRUE (word_exists("every", dictionary));
    EXPECT_TRUE (word_exists("mother", dictionary));
    EXPECT_FALSE ( word_exists(" a ", dictionary));
    EXPECT_FALSE ( word_exists("warthog", dictionary));
}