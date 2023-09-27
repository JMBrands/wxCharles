#include <iostream>

using namespace std;

enum Month
{
  January = 1, February, March, April, May, June,
  July, August, September, October, November, December
};

enum Weekday
{
  Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

bool leap_year(int year) {
  if (year % 4 == 0 && (year % 100 != 0 || year % 400)) {
    return true;
  }
  return false;
}

int num_days_in_month(Month month, int year) {
  switch (month) {
    case January:
    case March:
    case May:
    case July:
    case August:
    case October:
    case December:
      return 31;
      break;
    case February:
      return 28 + leap_year(year);
      break;
    case April:
    case June:
    case September:
    case November:
      return 30;
      break;
  }
}

Weekday first_day_of_year(int year) {
  /* 2007 was chosen as base year since it's our birthyear
  Also it started on a monday
  This function just calculates the amount of years and leap years in between
  and based on that it calculates the first day of said year
  */
  int base_year = 2007; // not necessary, but works nicer
  Weekday base_day = Monday; // also not necessary
  int delta_days;
  int delta_leapyears;
  
  if (year == base_year) {
    return base_day;
  }
  else if (year > base_year) {
    for (int i = base_year; i < year; i++) {
      delta_days += 1 + leap_year(i);
    }
  } else {
    for (int i = base_year; i > year; i--) {
      delta_days -= 1 + leap_year(i - 1);
    }
  }
  return static_cast<Weekday> ((base_day + delta_days) % 7);
  
}

Weekday first_day_of_month(int year, Month month) {
  Weekday first_day_of_year = first_day_of_year(year);
  Weekday first_day = first_day_of_year;
  for(int i = 1, i < month, i++) {
    first_day += num_days_in_month(i);
    first_day %= 7;
  }
  return first_day;
}

void show_month (Month month, int year)
{
  // implement this function

  str calendar[35];
  Weekday i;
  for (i = Monday, i < first_day_of_month(year, month), i++) {
    calendar [i] = ""
  }
  int j = 1;
  for (i, i < first_day_of_month(year, static_cast<Month>(month + 1)), i++) {
    calendar[i] = as_string(j);
    j++;
  }

  cout << "Mo Tu We Th Fr Sa Su" << endl;
}

void show_months ()
{
  // implement this function
}

#ifndef TESTING
int main ()
{
  return 0;
}
#endif
