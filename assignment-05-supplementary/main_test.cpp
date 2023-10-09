#include "main.cpp"
#include "gtest/gtest.h"

/* Write your own unit tests where needed */

TEST(checking, initialize_words) {
    EXPECT_NO_THROW (initialize_words(dictionary));
}

TEST(checking, word_exists) {
    EXPECT_TRUE (word_exists("a", dictionary));
    EXPECT_TRUE (word_exists("every", dictionary));
    EXPECT_TRUE (word_exists("mother", dictionary));
    EXPECT_FALSE ( word_exists(" a ", dictionary));
    EXPECT_FALSE ( word_exists("warthog", dictionary));
}

TEST(checking, file_valid) {
    EXPECT_TRUE(file_valid("a warthog investigator works here", dictionary));

}

TEST(decrypting, decrypting) {
    bool solved = false;

    for (int r = 1; !solved && r <= 6555; r++) {
        cout << r << ": ";
        ifstream infile("secret.txt", ios_base::binary);
        ostringstream out("", ios_base::binary);
        decrypt(infile, out, r);
        infile.close();
        // cout << out.str() << endl;
        if (file_valid(out.str(), dictionary, 0.8)) {
            cout << "valid" << endl;
            ofstream outf("source.txt", ios_base::binary);
            outf << out.str();
            outf.close();
            solved = true;
        } else {
            cout << "invalid" << endl;
        }
    }
}