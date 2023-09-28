#include "main.cpp"
#include "gtest/gtest.h"

TEST (bonus, first_day_of_year) {
    EXPECT_EQ (first_day_of_year (2007), Monday);
    EXPECT_EQ (first_day_of_year (2023), Sunday);
    EXPECT_EQ (first_day_of_year (1999), Friday);
    EXPECT_EQ (first_day_of_year (2004), Thursday);
    EXPECT_EQ (first_day_of_year (2012), Sunday);
    EXPECT_EQ (first_day_of_year (1998), Thursday);
    EXPECT_EQ (first_day_of_year (2013), Tuesday);
    EXPECT_EQ (first_day_of_year (1996), Monday);
    EXPECT_EQ (first_day_of_year (1995), Sunday);
    EXPECT_EQ (first_day_of_year (1970), Thursday);
    EXPECT_EQ (first_day_of_year (2001), Monday);
    EXPECT_EQ (first_day_of_year (2000), Saturday);

}

TEST (bonus, num_days_in_month) {
    EXPECT_EQ (num_days_in_month (February, 2008), 29);
    EXPECT_EQ (num_days_in_month (February, 2009), 28);
    EXPECT_EQ (num_days_in_month (August, 2012), 31);
}

TEST(FirstDayOfMonthTest, January) {
  EXPECT_EQ(first_day_of_month(January, 2007), Monday);
  EXPECT_EQ(first_day_of_month(January, 2023), Sunday);
  EXPECT_EQ(first_day_of_month(January, 1999), Friday);
  EXPECT_EQ(first_day_of_month(January, 2004), Thursday);
  EXPECT_EQ(first_day_of_month(January, 2012), Sunday);
}

TEST(FirstDayOfMonthTest, February) {
  EXPECT_EQ(first_day_of_month(February, 2007), Thursday);
  EXPECT_EQ(first_day_of_month(February, 2023), Wednesday);
  EXPECT_EQ(first_day_of_month(February, 1999), Monday);
  EXPECT_EQ(first_day_of_month(February, 2004), Sunday);
  EXPECT_EQ(first_day_of_month(February, 2012), Wednesday);
}

TEST(FirstDayOfMonthTest, March) {
  EXPECT_EQ(first_day_of_month(March, 2007), Thursday);
  EXPECT_EQ(first_day_of_month(March, 2023), Wednesday);
  EXPECT_EQ(first_day_of_month(March, 1999), Monday);
  EXPECT_EQ(first_day_of_month(March, 2004), Monday);
  EXPECT_EQ(first_day_of_month(March, 2012), Thursday);
}

TEST(FirstDayOfMonthTest, April) {
  EXPECT_EQ(first_day_of_month(April, 2007), Sunday);
  EXPECT_EQ(first_day_of_month(April, 2023), Saturday);
  EXPECT_EQ(first_day_of_month(April, 1999), Thursday);
  EXPECT_EQ(first_day_of_month(April, 2004), Thursday);
  EXPECT_EQ(first_day_of_month(April, 2012), Sunday);
}

TEST(FirstDayOfMonthTest, May) {
  EXPECT_EQ(first_day_of_month(May, 2007), Tuesday);
  EXPECT_EQ(first_day_of_month(May, 2023), Monday);
  EXPECT_EQ(first_day_of_month(May, 1999), Saturday);
  EXPECT_EQ(first_day_of_month(May, 2004), Saturday);
  EXPECT_EQ(first_day_of_month(May, 2012), Tuesday);
}

TEST(FirstDayOfMonthTest, June) {
  EXPECT_EQ(first_day_of_month(June, 2007), Friday);
  EXPECT_EQ(first_day_of_month(June, 2023), Thursday);
  EXPECT_EQ(first_day_of_month(June, 1999), Tuesday);
  EXPECT_EQ(first_day_of_month(June, 2004), Tuesday);
  EXPECT_EQ(first_day_of_month(June, 2012), Friday);
}

TEST(FirstDayOfMonthTest, July) {
  EXPECT_EQ(first_day_of_month(July, 2007), Sunday);
  EXPECT_EQ(first_day_of_month(July, 2023), Saturday);
  EXPECT_EQ(first_day_of_month(July, 1999), Thursday);
  EXPECT_EQ(first_day_of_month(July, 2004), Thursday);
  EXPECT_EQ(first_day_of_month(July, 2012), Sunday);
}

TEST(FirstDayOfMonthTest, August) {
  EXPECT_EQ(first_day_of_month(August, 2007), Wednesday);
  EXPECT_EQ(first_day_of_month(August, 2023), Tuesday);
  EXPECT_EQ(first_day_of_month(August, 1999), Sunday);
  EXPECT_EQ(first_day_of_month(August, 2004), Sunday);
  EXPECT_EQ(first_day_of_month(August, 2012), Wednesday);
}

TEST(FirstDayOfMonthTest, September) {
  EXPECT_EQ(first_day_of_month(September, 2007), Saturday);
  EXPECT_EQ(first_day_of_month(September, 2023), Friday);
  EXPECT_EQ(first_day_of_month(September, 1999), Wednesday);
  EXPECT_EQ(first_day_of_month(September, 2004), Wednesday);
  EXPECT_EQ(first_day_of_month(September, 2012), Saturday);
}

TEST(FirstDayOfMonthTest, October) {
  EXPECT_EQ(first_day_of_month(October, 2007), Monday);
  EXPECT_EQ(first_day_of_month(October, 2023), Sunday);
  EXPECT_EQ(first_day_of_month(October, 1999), Friday);
  EXPECT_EQ(first_day_of_month(October, 2004), Friday);
  EXPECT_EQ(first_day_of_month(October, 2012), Monday);
}

TEST(FirstDayOfMonthTest, November) {
  EXPECT_EQ(first_day_of_month(November, 2007), Thursday);
  EXPECT_EQ(first_day_of_month(November, 2023), Wednesday);
  EXPECT_EQ(first_day_of_month(November, 1999), Monday);
  EXPECT_EQ(first_day_of_month(November, 2004), Monday);
  EXPECT_EQ(first_day_of_month(November, 2012), Thursday);
}

TEST(FirstDayOfMonthTest, December) {
  EXPECT_EQ(first_day_of_month(December, 2007), Saturday);
  EXPECT_EQ(first_day_of_month(December, 2023), Friday);
  EXPECT_EQ(first_day_of_month(December, 1999), Wednesday);
  EXPECT_EQ(first_day_of_month(December, 2004), Wednesday);
  EXPECT_EQ(first_day_of_month(December, 2012), Saturday);
}