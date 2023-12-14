#include "main.cpp"
#include "gtest/gtest.h"

const vector<vector<char>> BAD_FORMAT1 = {
    {'.', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', '?'}
};
const vector<vector<char>> BAD_FORMAT2 = {
    {'.', '.', '.'},
    {'.', 'f', '.', '.'},
    {'.', '.', '.'}
};
const vector<vector<char>> BAD_FORMAT3 = {
    {'.', '.', '.'},
    {'.', '.', '.'},
    {'.', '.', '.'}
};
const vector<vector<char>> BAD_FORMAT4 = {
    {'.', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', 'f'}
};
const vector<vector<char>> CHALLENGE_1 = {
    {'.','.','.','.','r','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','f','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','x','.','.'}
};
const vector<vector<char>> CHALLENGE_1_n = {
    {'.','.','.','.','r','.','.','.','.','.'},
    {'.','.','.','.','f','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','x','.','.'}
};
const vector<vector<char>> CHALLENGE_1_ne = {
    {'.','.','.','.','r','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','f','r','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','x','.','.'}
};
const vector<vector<char>> CHALLENGE_1_nes = {
    {'.','.','.','.','r','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','F','.','.'}
};

TEST(loading, bad_format1)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT1, puzzle));
}

TEST(loading, bad_format2)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT2, puzzle));
}

TEST(loading, bad_format3)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT3, puzzle));
}

TEST(loading, bad_format4)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT4, puzzle));
}

TEST(loading, ok)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_n, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_ne, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_nes, puzzle));
}

TEST(puzzle, is_solvable)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_TRUE(is_solvable(puzzle));
    move_flamingo(puzzle, MoveNorth);
    EXPECT_TRUE(is_solvable(puzzle));
    move_flamingo(puzzle, MoveWest);
    EXPECT_FALSE(is_solvable(puzzle));
}

TEST(is_solved, challenge_1)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, challenge_1_n)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_n, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, challenge_1_ne)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_ne, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, challenge_1_nes)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_nes, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
}

TEST(move, north)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_n, expected));
    move_flamingo(puzzle, MoveNorth);
    EXPECT_EQ(puzzle, expected);
}
