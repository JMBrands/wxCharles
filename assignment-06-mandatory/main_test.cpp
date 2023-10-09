#include "main.cpp"
#include "gtest/gtest.h"

// Note that the following array declarations only initialize 12x12 grids.
// The NO_OF_ROWS and NO_OF_COLUMNS constants have values 40 and 60 however.
// In this case the 'missing' values will be 'zero-initialized'.
// This means they will have the value 0, which corresponds to the enum member Dead.
// Effectively we only describe a portion of the top-left part of the universe to test with.
// The rest of the universe will implicitly be made up of dead cells.
Cell glider0[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Live, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider1[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Live, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider2[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Live, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider3[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider4[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

void array_copy(Cell source [NO_OF_ROWS][NO_OF_COLUMNS], Cell dest [NO_OF_ROWS][NO_OF_COLUMNS]) {
    for(int i = 0; i < NO_OF_ROWS; i++) {
        for(int j = 0; j < NO_OF_COLUMNS; j++) {
            dest[i][j] = source[i][j];
        }
    }
}

// Check if the inner part of two universes match.
// Note that by design the outer dead frame is not checked.
bool generation_match(Cell generation [NO_OF_ROWS][NO_OF_COLUMNS], Cell reference [NO_OF_ROWS][NO_OF_COLUMNS]) {
    for(int i = 0; i < NO_OF_ROWS; i++) {
        for(int j = 0; j < NO_OF_COLUMNS; j++) {
            if(generation[i][j] != reference[i][j])
                return false;
        }
    }

    return true;
}

TEST(part1, cell_at)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS] = {
        {Live, Dead},
        {Dead, Live},
    };

    EXPECT_EQ(cell_at(universe, 0, 0), Live);
    EXPECT_EQ(cell_at(universe, 0, 1), Dead);
    EXPECT_EQ(cell_at(universe, 1, 0), Dead);
    EXPECT_EQ(cell_at(universe, 1, 1), Live);
    EXPECT_EQ(cell_at(universe, -1, -1), Dead);
    EXPECT_EQ(cell_at(universe, 0, NO_OF_COLUMNS + 10), Dead);
    EXPECT_EQ(cell_at(universe, -5, 0), Dead);
    EXPECT_EQ(cell_at(universe, NO_OF_ROWS, 0), Dead);
    EXPECT_EQ(cell_at(universe, NO_OF_ROWS + 4, NO_OF_COLUMNS + 8), Dead);
}

TEST(part2, read_universe_10_cell_row)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    for(int i = 0; i < 10; i++) {
        expected[18][24 + i] = Live;
    }

    EXPECT_TRUE(read_universe_file("10_cell_row.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_glider0)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[37][2] = Live;
    expected[37][3] = Live;
    expected[37][4] = Live;
    expected[38][4] = Live;
    expected[39][3] = Live;

    EXPECT_TRUE(read_universe_file("glider0.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_glider1)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[36][3] = Live;
    expected[37][3] = Live;
    expected[37][4] = Live;
    expected[38][2] = Live;
    expected[38][4] = Live;

    EXPECT_TRUE(read_universe_file("glider1.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_glider2)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[36][3] = Live;
    expected[36][4] = Live;
    expected[37][2] = Live;
    expected[37][4] = Live;
    expected[38][4] = Live;

    EXPECT_TRUE(read_universe_file("glider2.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_glider3)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[36][3] = Live;
    expected[36][4] = Live;
    expected[37][4] = Live;
    expected[37][5] = Live;
    expected[38][3] = Live;

    EXPECT_TRUE(read_universe_file("glider3.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_glider4)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[36][3] = Live;
    expected[36][4] = Live;
    expected[36][5] = Live;
    expected[37][5] = Live;
    expected[38][4] = Live;

    EXPECT_TRUE(read_universe_file("glider4.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_Gosper_glider_gun)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[2][26] = Live;
    expected[3][24] = Live;
    expected[3][26] = Live;
    expected[4][14] = Live;
    expected[4][15] = Live;
    expected[4][22] = Live;
    expected[4][23] = Live;
    expected[4][36] = Live;
    expected[4][37] = Live;
    expected[5][13] = Live;
    expected[5][17] = Live;
    expected[5][22] = Live;
    expected[5][23] = Live;
    expected[5][36] = Live;
    expected[5][37] = Live;
    expected[6][2] = Live;
    expected[6][3] = Live;
    expected[6][12] = Live;
    expected[6][18] = Live;
    expected[6][22] = Live;
    expected[6][23] = Live;
    expected[7][2] = Live;
    expected[7][3] = Live;
    expected[7][12] = Live;
    expected[7][16] = Live;
    expected[7][18] = Live;
    expected[7][19] = Live;
    expected[7][24] = Live;
    expected[7][26] = Live;
    expected[8][12] = Live;
    expected[8][18] = Live;
    expected[8][26] = Live;
    expected[9][13] = Live;
    expected[9][17] = Live;
    expected[10][14] = Live;
    expected[10][15] = Live;

    EXPECT_TRUE(read_universe_file("Gosper_glider_gun.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_pulsar)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
    expected[14][22] = Live;
    expected[14][28] = Live;
    expected[15][22] = Live;
    expected[15][28] = Live;
    expected[16][22] = Live;
    expected[16][23] = Live;
    expected[16][27] = Live;
    expected[16][28] = Live;
    expected[18][18] = Live;
    expected[18][19] = Live;
    expected[18][20] = Live;
    expected[18][23] = Live;
    expected[18][24] = Live;
    expected[18][26] = Live;
    expected[18][27] = Live;
    expected[18][30] = Live;
    expected[18][31] = Live;
    expected[18][32] = Live;
    expected[19][20] = Live;
    expected[19][22] = Live;
    expected[19][24] = Live;
    expected[19][26] = Live;
    expected[19][28] = Live;
    expected[19][30] = Live;
    expected[20][22] = Live;
    expected[20][23] = Live;
    expected[20][27] = Live;
    expected[20][28] = Live;
    expected[22][22] = Live;
    expected[22][23] = Live;
    expected[22][27] = Live;
    expected[22][28] = Live;
    expected[23][20] = Live;
    expected[23][22] = Live;
    expected[23][24] = Live;
    expected[23][26] = Live;
    expected[23][28] = Live;
    expected[23][30] = Live;
    expected[24][18] = Live;
    expected[24][19] = Live;
    expected[24][20] = Live;
    expected[24][23] = Live;
    expected[24][24] = Live;
    expected[24][26] = Live;
    expected[24][27] = Live;
    expected[24][30] = Live;
    expected[24][31] = Live;
    expected[24][32] = Live;
    expected[26][22] = Live;
    expected[26][23] = Live;
    expected[26][27] = Live;
    expected[26][28] = Live;
    expected[27][22] = Live;
    expected[27][28] = Live;
    expected[28][22] = Live;
    expected[28][28] = Live;

    EXPECT_TRUE(read_universe_file("pulsar.txt", universe));
    EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_missing)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    EXPECT_FALSE(read_universe_file("this-file-does-not-exist.txt", universe));
}

TEST(part2, read_universe_bad_format1)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    EXPECT_FALSE(read_universe_file("bad_format_1.txt", universe));
}

TEST(part2, read_universe_bad_format2)
{
    Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
    EXPECT_FALSE(read_universe_file("bad_format_2.txt", universe));
}

TEST(part3, glider_0)
{
    Cell now [NO_OF_ROWS][NO_OF_COLUMNS];
    Cell next [NO_OF_ROWS][NO_OF_COLUMNS];
    array_copy(glider0, now);
    next_generation(now, next);
    EXPECT_TRUE(generation_match(next, glider1));
}

TEST(part3, glider_1)
{
    Cell now [NO_OF_ROWS][NO_OF_COLUMNS];
    Cell next [NO_OF_ROWS][NO_OF_COLUMNS];
    array_copy(glider1, now);
    next_generation(now, next);
    EXPECT_TRUE(generation_match(next, glider2));
}

TEST(part3, glider_2)
{
    Cell now [NO_OF_ROWS][NO_OF_COLUMNS];
    Cell next [NO_OF_ROWS][NO_OF_COLUMNS];
    array_copy(glider2, now);
    next_generation(now, next);
    EXPECT_TRUE(generation_match(next, glider3));
}

TEST(part3, glider_3)
{
    Cell now [NO_OF_ROWS][NO_OF_COLUMNS];
    Cell next [NO_OF_ROWS][NO_OF_COLUMNS];
    array_copy(glider3, now);
    next_generation(now, next);
    EXPECT_TRUE(generation_match(next, glider4));
}
