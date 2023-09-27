#include "main.cpp"
#include "gtest/gtest.h"

TEST (bonus, first_day_of_year) {
    EXPECT_EQ (first_day_of_year(2007), Monday);
    EXPECT_EQ (first_day_of_year(2023), Sunday);
    EXPECT_EQ (first_day_of_year(1970), Thursday);
}