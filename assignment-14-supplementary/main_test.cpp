#include "main.cpp"
#include "gtest/gtest.h"

// Note: some tests may be extremely slow without optimized code.
// You may wish to disable them while developing, focusing on faster tests.
// Of course building an efficient solution is also a fun challenge.
// Our reference solution passes all 28 tests in roughly 2 minutes (no threading).

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
const vector<vector<char>> UNSOLVABLE_CHALLENGE = {
    {'.', '.', 'x'},
    {'.', 'f', '.'},
    {'.', '.', '.'}
};
const vector<vector<char>> CHALLENGE_0 = {
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','F'}
};
const vector<vector<char>> CHALLENGE_1 = {
    {'.','.','.','.','p','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','p','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','f','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','x','.','.'}
};
const vector<vector<char>> CHALLENGE_2 = {
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','p','.','.'},
    {'.','.','f','.','.','.','.'},
    {'.','p','.','.','.','p','.'},
    {'.','.','.','p','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'}
};
const vector<vector<char>> CHALLENGE_3 = {
    {'.','.','p','.','.','.','.'},
    {'.','.','.','p','.','.','p'},
    {'.','p','.','.','.','.','.'},
    {'.','.','.','.','.','x','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','p','.','.'},
    {'f','.','.','.','.','p','.'}
};
const vector<vector<char>> CHALLENGE_4 =  {
    {'p','.','.','f','.','.','p'},
    {'.','p','.','.','.','p','.'},
    {'.','.','.','.','.','.','.'},
    {'.','p','.','.','.','p','.'},
    {'x','.','.','.','.','.','.'},
    {'.','.','.','.','p','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> CHALLENGE_5 =  {
    {'.','.','.','f','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','p','.','p','.'},
    {'.','.','.','p','.','.','.'},
    {'.','x','.','.','.','.','.'},
    {'.','.','.','.','p','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> CHALLENGE_6 =  {
    {'.','.','.','.','.','.','.'},
    {'p','p','p','x','.','.','p'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'f','.','.','.','.','.','p'},
    {'.','.','.','.','.','p','.'}
};
const vector<vector<char>> CHALLENGE_7 =  {
    {'f','.','.','.','.','.','p'},
    {'.','p','.','.','.','p','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','p','.','.','.','p','.'},
    {'p','.','.','.','.','.','p'}
};
const vector<vector<char>> CHALLENGE_8 =  {
    {'.','.','.','.','p','.','.'},
    {'.','f','.','.','.','p','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'p','.','.','.','.','.','p'},
    {'.','p','.','.','.','.','.'}
};
const vector<vector<char>> CHALLENGE_9 =  {
    {'.','.','x','p','.','.','.'},
    {'p','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','f','.','.','p'},
    {'.','.','.','.','.','.','.'},
    {'p','.','.','.','.','.','p'},
    {'.','.','.','.','.','p','.'}
};
const vector<vector<char>> CHALLENGE_10 =  {
    {'.','.','.','p','.','.','.'},
    {'p','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'f','.','.','.','p','.','.'},
    {'.','.','.','.','x','.','.'},
    {'.','.','.','.','.','.','p'},
    {'p','.','.','.','.','.','.'}
};
const vector<vector<char>> CHALLENGE_11 =  {
    {'.','.','.','p','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'x','.','.','p','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','f','.','.','.'}
};
const vector<vector<char>> CHALLENGE_12 =  {
    {'.','.','.','.','.','.','.'},
    {'p','.','.','f','.','.','p'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','x'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','p','p','p','.','.'}
};
const vector<vector<char>> CHALLENGE_13 =  {
    {'p','.','.','.','.','.','.','.','p'},
    {'.','f','.','.','.','.','.','p','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','p','.','.','.','.','.','p','.'},
    {'p','.','.','.','.','.','.','.','p'}
};

TEST(bfs, bad_format1)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT1, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format2)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT2, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format3)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT3, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format4)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT4, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, no_solution)
{
    const int EXPECTED_STEPS = NO_SOLUTION;

    vector<Puzzle> solution_path;
    int actual = breadth_first(UNSOLVABLE_CHALLENGE, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, challenge0)
{
    const int EXPECTED_STEPS = 0;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_0, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge1)
{
    const int EXPECTED_STEPS = 3;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_1, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge2)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_2, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge3)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_3, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge4)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_4, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge5)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_5, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge6)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_6, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge7)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_7, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge8)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_8, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge9)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_9, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge10)
{
    const int EXPECTED_STEPS = 7;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_10, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge11)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_11, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge12)
{
    const int EXPECTED_STEPS = 8;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_12, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge13)
{
    const int EXPECTED_STEPS = 7;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_13, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, bad_format1)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT1, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format2)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT2, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format3)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT3, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format4)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT4, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, no_solution)
{
    const int EXPECTED_STEPS = NO_SOLUTION;

    vector<Puzzle> solution_path;
    int actual = depth_first(UNSOLVABLE_CHALLENGE, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, challenge0)
{
    const int EXPECTED_STEPS = 0;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_0, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge1)
{
    const int EXPECTED_STEPS = 3;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_1, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge2)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_2, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge3)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_3, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge4)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_4, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge5)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_5, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge6)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_6, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge7)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_7, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge8)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_8, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge9)
{
    const int EXPECTED_STEPS = 5;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_9, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge10)
{
    const int EXPECTED_STEPS = 7;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_10, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge11)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_11, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge12)
{
    const int EXPECTED_STEPS = 8;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_12, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge13)
{
    const int EXPECTED_STEPS = 7;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_13, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, depth_limit)
{
    vector<Puzzle> solution_path;

    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 0), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 1), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 2), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 3), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 4), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 5), 5);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 6), 5);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 7), 5);
}
