#include "main.cpp"
#include "gtest/gtest.h"

TEST (bonus, first_day_of_year) {
    EXPECT_EQ (first_day_of_year (2007), Monday);
    EXPECT_EQ (first_day_of_year (2023), Sunday);
    EXPECT_EQ (first_day_of_year (1970), Thursday);
}

TEST (bonus, num_days_in_month) {
    EXPECT_EQ (num_days_in_month (February, 2008), 29);
    EXPECT_EQ (num_days_in_month (February, 2009), 28);
    EXPECT_EQ (num_days_in_month (August, 2012), 31);
}