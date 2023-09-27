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
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0 ) {
    return true;
  }
  return false;
}

int number_of_days_in_month (int year, Month month)
{
  switch (month)
  {
  case January:
  case March:
  case May:
  case July:
  case August:
  case October:
  case December:
    return 31;
    break;
  
  case April:
  case June:
  case September:
  case November:
    return 30;
    break;
  case February:
    return 28 + is_leap_year(year);
  default:
    break;
  }
  
  return 0;
}

/********************************************************************
  Assignment part 2: Holy days based on Easter
********************************************************************/
string show_carnival (int easter_day, Month easter_month, int year)
{
  int carnival_day; 
  int carnival_month = easter_month-1;
  int carnival_diff = 49 - easter_day;
  if (carnival_diff > number_of_days_in_month(year, static_cast<Month> (easter_month - 1))) {
    carnival_diff -= number_of_days_in_month(year, static_cast<Month> (easter_month - 1));
    carnival_month--;
  }
  carnival_day = number_of_days_in_month(year, static_cast<Month> (carnival_month)) - carnival_diff;
  return to_string(carnival_day) + "-" + to_string(carnival_month);
}

string show_good_friday (int easter_day, Month easter_month, int year)
{
  int good_friday_day;
  int good_friday_month;
  switch (easter_day) {
    case 2:
      good_friday_day = number_of_days_in_month(year, static_cast<Month> (easter_month - 1));
      good_friday_month = easter_month - 1;
      break;
    case 1:
      good_friday_day = number_of_days_in_month(year, static_cast<Month> (easter_month - 1)) - 1;
      good_friday_month = easter_month - 1;
      break;
    default:
      good_friday_day = easter_day - 2;
      good_friday_month = easter_month;
      break;
    }
  return to_string(good_friday_day) + "-" + to_string(good_friday_month);
}

string show_easter (int easter_day, Month easter_month)
{
  return to_string(easter_day) + "-" + to_string(easter_month);
}

string show_whitsuntide (int easter_day, Month easter_month, int year)
{
  int whitsuntide_day;
  Month whitsuntide_month;
  int delta_days = 49;
  whitsuntide_month = static_cast<Month>(easter_month + 1);
  delta_days -= number_of_days_in_month(year, easter_month);
  if (delta_days + easter_day <= number_of_days_in_month(year, whitsuntide_month)) {
    whitsuntide_day =  easter_day + delta_days;
  }
  else {
    delta_days -= number_of_days_in_month(year, whitsuntide_month);
    whitsuntide_month = static_cast<Month> (whitsuntide_month + 1);
    whitsuntide_day = easter_day + delta_days;
    
  }
  
  return to_string(whitsuntide_day) + "-" + to_string(whitsuntide_month);
}

string show_ascension_day (int easter_day, Month easter_month, int year)
{
  int ascension_day;
  Month ascension_month;
  int delta_days = 39;

  ascension_month = static_cast<Month>(easter_month + 1);
  delta_days -= number_of_days_in_month(year, easter_month);
  if (delta_days + easter_day <= number_of_days_in_month(year, ascension_month)) {
    ascension_day =  easter_day + delta_days;
  }
  else {
    delta_days -= number_of_days_in_month(year, ascension_month);
    ascension_month = static_cast<Month> (ascension_month + 1);
    ascension_day = easter_day + delta_days;
    
  }
  
  return to_string(ascension_day) + "-" + to_string(ascension_month);
}

void show_holy_days (int year)
{
  int easter_day = calculate_easter_day(year);
  Month easter_month = static_cast<Month>(calculate_easter_month(year));
  cout << "Carnival: " << show_carnival(easter_day, easter_month, year) << endl
  << "Good Friday: " << show_good_friday(easter_day, easter_month, year) << endl
  << "Easter: " << show_easter(easter_day, easter_month) << endl
  << "Ascension day: " << show_ascension_day(easter_day, easter_month, year) << endl
  << "Whitsuntide: " << show_whitsuntide(easter_day, easter_month, year) << endl;
}

#ifndef TESTING
int main()
{
  int year;
  cout << "Enter the year you want to calculate: ";
  cin >> year;
  cout << endl;
  show_holy_days(year);
  return 0;
}
#endif
