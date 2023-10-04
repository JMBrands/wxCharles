#include "main.cpp"
#include "gtest/gtest.h"

using namespace std;

TEST(part1, encrypt_control)
{
    for(int c = 0; c < 32; c++) {
        for(int r : {0, 1, 32, 42, 96, 65535, 45774747}) {
            EXPECT_EQ(rotate_char(c, r, Encrypt), c);
        }
    }
}

TEST(part1, encrypt_other)
{
    EXPECT_EQ(rotate_char(' ', 0, Encrypt), ' ');
    EXPECT_EQ(rotate_char('1', 1, Encrypt), '2');
    EXPECT_EQ(rotate_char('a', 32, Encrypt), '!');
    EXPECT_EQ(rotate_char('G', 42, Encrypt), 'q');
    EXPECT_EQ(rotate_char('#', 96, Encrypt), '#');
    EXPECT_EQ(rotate_char('@', 65535, Encrypt), '\x7f');
    EXPECT_EQ(rotate_char('~', 45774747, Encrypt), '9');
}

TEST(part1, decrypt_control)
{
    for(int c = 0; c < 32; c++) {
        for(int r : {0, 1, 32, 42, 96, 65535, 45774747}) {
            EXPECT_EQ(rotate_char(c, r, Decrypt), c);
        }
    }
}

TEST(part1, decrypt_other)
{
    EXPECT_EQ(rotate_char(' ', 0, Decrypt), ' ');
    EXPECT_EQ(rotate_char('2', 1, Decrypt), '1');
    EXPECT_EQ(rotate_char('!', 32, Decrypt), 'a');
    EXPECT_EQ(rotate_char('q', 42, Decrypt), 'G');
    EXPECT_EQ(rotate_char('#', 96, Decrypt), '#');
    EXPECT_EQ(rotate_char('\x7f', 65535, Decrypt), '@');
    EXPECT_EQ(rotate_char('9', 45774747, Decrypt), '~');
}

TEST(part1, inverse)
{
    for (int c = 0; c < 128; c++) {
        for(int r : {0, 1, 32, 42, 96, 65535, 45774747}) {
            EXPECT_EQ(rotate_char(rotate_char(c, r, Encrypt), r, Decrypt), c);
        }
    }
}

bool streams_match(ifstream& ins, ifstream& refs) {
    char c, refc;

    // Loop over every character in the reference stream.
    while(refs.get(refc)) {
        // The input stream must also be able to read a character.
        // It must also match the reference character read from the reference stream.
        if(!ins.get(c) || c != refc) {
            return false;
        }
    }

    // We know the input stream begins with the reference stream, but may contain additional characters.
    return true;
}

int get_stream_length(ifstream& is)
{
    // Get the length of the stream by moving to the end and getting the read position.
    // We then move back again to the start of the stream for further reading.
    is.seekg(0, ios_base::end);
    int length = static_cast<int>(is.tellg());
    is.seekg(0, ios_base::beg);

    return length;
}

TEST(part3, use_OTP_1)
{
    const int R = 1;
    const string INPUT_FILENAME = "test.txt";
    const string OUTPUT_FILENAME = "output" + to_string(R) + ".txt";
    const string TEST_FILENAME = "test_encrypted_with_" + to_string(R) + ".txt";

    ifstream input_file(INPUT_FILENAME);
    ofstream output_file(OUTPUT_FILENAME);
    use_OTP(input_file, output_file, Encrypt, R);
    output_file.close();

    ifstream expected_file(TEST_FILENAME);
    ifstream actual_file(OUTPUT_FILENAME);
    int expected_length = get_stream_length(expected_file);
    int actual_length = get_stream_length(actual_file);

    EXPECT_TRUE(streams_match(actual_file, expected_file));
    EXPECT_EQ(actual_length, expected_length);
}

TEST(part3, use_OTP_42)
{
    const int R = 42;
    const string INPUT_FILENAME = "test.txt";
    const string OUTPUT_FILENAME = "output" + to_string(R) + ".txt";
    const string TEST_FILENAME = "test_encrypted_with_" + to_string(R) + ".txt";

    ifstream input_file(INPUT_FILENAME);
    ofstream output_file(OUTPUT_FILENAME);
    use_OTP(input_file, output_file, Encrypt, R);
    output_file.close();

    ifstream expected_file(TEST_FILENAME);
    ifstream actual_file(OUTPUT_FILENAME);
    int expected_length = get_stream_length(expected_file);
    int actual_length = get_stream_length(actual_file);

    EXPECT_TRUE(streams_match(actual_file, expected_file));
    EXPECT_EQ(actual_length, expected_length);
}

TEST(part3, use_OTP_96)
{
    const int R = 96;
    const string INPUT_FILENAME = "test.txt";
    const string OUTPUT_FILENAME = "output" + to_string(R) + ".txt";
    const string TEST_FILENAME = "test_encrypted_with_" + to_string(R) + ".txt";

    ifstream input_file(INPUT_FILENAME);
    ofstream output_file(OUTPUT_FILENAME);
    use_OTP(input_file, output_file, Encrypt, R);
    output_file.close();

    ifstream expected_file(TEST_FILENAME);
    ifstream actual_file(OUTPUT_FILENAME);
    int expected_length = get_stream_length(expected_file);
    int actual_length = get_stream_length(actual_file);

    EXPECT_TRUE(streams_match(actual_file, expected_file));
    EXPECT_EQ(actual_length, expected_length);
}

TEST(part3, use_OTP_65535)
{
    const int R = 65535;
    const string INPUT_FILENAME = "test.txt";
    const string OUTPUT_FILENAME = "output" + to_string(R) + ".txt";
    const string TEST_FILENAME = "test_encrypted_with_" + to_string(R) + ".txt";

    ifstream input_file(INPUT_FILENAME);
    ofstream output_file(OUTPUT_FILENAME);
    use_OTP(input_file, output_file, Encrypt, R);
    output_file.close();

    ifstream expected_file(TEST_FILENAME);
    ifstream actual_file(OUTPUT_FILENAME);
    int expected_length = get_stream_length(expected_file);
    int actual_length = get_stream_length(actual_file);

    EXPECT_TRUE(streams_match(actual_file, expected_file));
    EXPECT_EQ(actual_length, expected_length);
}
