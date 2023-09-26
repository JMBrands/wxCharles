#include <iostream>

using namespace std;

enum Month
{
  January = 1, February, March, April, May, June,
  July, August, September, October, November, December
};

/* The function easter_base uses the Meeus/Jones/Butcher formula to compute
   the number that is used to determine on which month (easter_month below)
   and day (easter_day below) Easter is in the given year.
*/
int easter_base (int year)
{
  const int A = year % 19;
  const int B = year / 100;
  const int C = year % 100;
  const int D = B / 4;
  const int E = B % 4;
  const int F = (B + 8) / 25;
  const int G = (B - F + 1) / 3;
  const int H = (19 * A + B - D - G + 15) % 30;
  const int I = C / 4;
  const int K = C % 4;
  const int L = (32 + 2 * E + 2 * I - H - K) % 7;
  const int M = (A + 11 * H + 22 * L) / 451;
  return H + L - 7 * M + 114;
}

/* The result of easter_year is the day number of the month in which Easter
   occurs in the given year.
*/
int calculate_easter_day (int year)
{
  return (easter_base (year) % 31) + 1 ;
}

/* The result of easter_month is the month in which Easter occurs in the given
   year.
*/
Month calculate_easter_month (int year)
{
  return static_cast<Month> (easter_base (year) / 31) ;
}

/********************************************************************
  Assignment part 1: Leap years
********************************************************************/
bool is_leap_year (int year)
{
  // implement this function
  return false;
}

int number_of_days_in_month (int year, Month month)
{
  // implement this function
  return 0;
}

/********************************************************************
  Assignment part 2: Holy days based on Easter
********************************************************************/
string show_carnival (int easter_day, Month easter_month, int year)
{
  // implement this function
  return "";
}

string show_good_friday (int easter_day, Month easter_month, int year)
{
  // implement this function
  return "";
}

string show_easter (int easter_day, Month easter_month)
{
  // implement this function
  return "";
}

string show_whitsuntide (int easter_day, Month easter_month, int year)
{
  // implement this function
  return "";
}

string show_ascension_day (int easter_day, Month easter_month, int year)
{
  // implement this function
  return "";
}

void show_holy_days (int year)
{
  // implement this function
}

#ifndef TESTING
int main()
{
  return 0;
}
#endif
