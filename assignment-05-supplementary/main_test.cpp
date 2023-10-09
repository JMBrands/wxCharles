#include "main.cpp"
#include "gtest/gtest.h"
#include <iostream>

/* Write your own unit tests where needed */

TEST(checking, initialize_words) {
    initialize_words(dictionary);
    EXPECT_FALSE (dictionary.empty());
    /*set<string>::iterator it;
    it = dictionary.begin();
    for (int i = 0; i < 10; i++) {
        string word = *it;
        for (int j = 0; j < word.length(); j++) {
            cout << word[j];
        }
        advance(it, 1);
    }*/
}

TEST(checking, word_exists) {
    initialize_words(dictionary);
    EXPECT_FALSE (dictionary.empty());
    EXPECT_TRUE (word_exists("AIDS", dictionary));
    EXPECT_TRUE (word_exists("a", dictionary));
    EXPECT_TRUE (word_exists("every", dictionary));
    EXPECT_TRUE (word_exists("mother", dictionary));
    EXPECT_FALSE ( word_exists(" a ", dictionary));
    EXPECT_FALSE ( word_exists("warthog", dictionary));
}