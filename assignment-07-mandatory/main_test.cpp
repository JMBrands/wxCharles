#include "main.cpp"
#include "gtest/gtest.h"

const string ALICE_FILENAME = "Alice's Adventures In Wonderland.txt";
const string DESKTOP_FILENAME = "desktop.txt";
const int NO_OF_WORDS_DESKTOP = 10;
string content_desktop [NO_OF_WORDS_DESKTOP] = {"Rose", "is", "a", "rose", "is", "a", "rose", "is", "a", "rose."};
const string VOGON_POEM_FILENAME = "Vogon poem.txt";
const int NO_OF_WORDS_VOGON_POEM = 78;
string content_vogon_poem [NO_OF_WORDS_VOGON_POEM] = {
    "O", "freddled", "gruntbuggly"
   ,"Thy", "micturations", "are", "to", "me"
   ,"As", "plurdled", "gabbleblotchits", "on", "a", "lurgid", "bee"
   ,"That", "mordiously", "hath", "bitled", "out", "its", "earted", "jurtles"
   ,"Into", "a", "rancid", "festering..."
   ,"Now", "the", "jurpling", "slayjid", "agrocrustules"
   ,"Are", "splurping", "hagrilly", "up", "the", "axlegrurts"
   ,"And", "living", "glupules", "frat", "and", "slipulate"
   ,"Like", "jowling", "meated", "liverslime"
   ,"Groop,", "I", "implore", "thee,", "my", "foonting", "turlingdromes"
   ,"And", "hooptiously", "drangle", "me", "with", "crinkly", "bindlewurdles"
   ,"Or", "else", "I", "shall", "rend", "thee", "in", "the", "gobberwarts", "with", "my", "blurglecruncheon,", "see", "if", "I", "don't."
};

bool equal_content (string data1 [], string data2 [], int length)
{// precondition:
    assert (length >= 0);
/*  postcondition:
    result is true only if the first length words in data1 are equal to the first length words in data2
    (which is true in case of length 0).
*/
    for (int i = 0 ; i < length ; i++)
        if (data1[i] != data2[i])
            return false;       // counter example found, so result is false
    return true;
}

TEST(enter_command, desktop)
{
    string content[MAX_NO_OF_WORDS];
    EXPECT_EQ(enter_command(DESKTOP_FILENAME, content), NO_OF_WORDS_DESKTOP);
    EXPECT_TRUE(equal_content(content, content_desktop, NO_OF_WORDS_DESKTOP));
}

TEST(enter_command, vogon_poem)
{
    string content[MAX_NO_OF_WORDS];
    EXPECT_EQ(enter_command(VOGON_POEM_FILENAME, content), NO_OF_WORDS_VOGON_POEM);
    EXPECT_TRUE(equal_content(content, content_vogon_poem, NO_OF_WORDS_VOGON_POEM));
}

TEST(enter_command, alice)
{
    string content[MAX_NO_OF_WORDS];
    EXPECT_EQ(enter_command(ALICE_FILENAME, content), MAX_NO_OF_WORDS);
}

TEST(count_command, desktop1)
{
    const int EXPECTED = 2;
    const int NO_OF_TERMS = 1;
    string terms[NO_OF_TERMS] = {"rose"};
    int actual = count_command(content_desktop, NO_OF_WORDS_DESKTOP, terms, NO_OF_TERMS);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(count_command, desktop2)
{
    const int EXPECTED = 3;
    const int NO_OF_TERMS = 2;
    string terms[NO_OF_TERMS] = {"is", "a"};
    int actual = count_command(content_desktop, NO_OF_WORDS_DESKTOP, terms, NO_OF_TERMS);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(count_command, vogon_poem1)
{
    const int EXPECTED = 3;
    const int NO_OF_TERMS = 1;
    string terms[NO_OF_TERMS] = {"the"};
    int actual = count_command(content_vogon_poem, NO_OF_WORDS_VOGON_POEM, terms, NO_OF_TERMS);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(count_command, vogon_poem2)
{
    const int EXPECTED = 1;
    const int NO_OF_TERMS = 2;
    string terms[NO_OF_TERMS] = {"meated", "liverslime"};
    int actual = count_command(content_vogon_poem, NO_OF_WORDS_VOGON_POEM, terms, NO_OF_TERMS);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(count_command, alice1)
{
    const int EXPECTED = 216;
    const int NO_OF_TERMS = 1;
    string terms[NO_OF_TERMS] = {"Alice"};
    string content[MAX_NO_OF_WORDS];
    int no_of_words = enter_command(ALICE_FILENAME, content);
    int actual = count_command(content, no_of_words, terms, NO_OF_TERMS);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(count_command, alice2)
{
    const int EXPECTED = 9;
    const int NO_OF_TERMS = 2;
    string terms[NO_OF_TERMS] = {"White","Rabbit"};
    string content[MAX_NO_OF_WORDS];
    int no_of_words = enter_command(ALICE_FILENAME, content);
    int actual = count_command(content, no_of_words, terms, NO_OF_TERMS);
    EXPECT_EQ(actual, EXPECTED);
}
