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
  if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
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
    default:
      return 0;
      break;
  }
}

Weekday first_day_of_year(int year) {
  /* 2007 was chosen as base year since it's our birthyear
  Also it started on a monday
  This function just calculates the amount of years in between
  and based on that it calculates the first day of said year
  it also counts double for leap years
  */
  int base_year = 2007; // not necessary, but now you're able to modify it
  Weekday base_day = Monday; // also not necessary
  int delta_days = 0;

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
  int final_day = (base_day + delta_days) % 7;
  if (final_day < 1) {
    final_day += 7;
  }
  return static_cast<Weekday> (final_day);
  
}

Weekday first_day_of_month(Month month, int year) {
  int first_day = first_day_of_year(year);
  if (month == January) {
    return static_cast<Weekday> (first_day);
  }
  for(int i = 1; i < static_cast <int> (month); i++) {
    first_day += num_days_in_month(static_cast<Month> (i), year) % 7;
  }
  first_day %= 7;
  if (first_day == 0) {
    first_day = 7;
  }
  return static_cast<Weekday> (first_day);
}

void show_month (Month month, int year)
{
  // implement this function

  string calendar[42];
  fill(begin(calendar), end(calendar), "  ");
  Weekday i = first_day_of_month(month, year);
  for (int j = 0; j < num_days_in_month(month, year); j++) {
    if (j < 9) {
      calendar[i+j-1] = to_string(j+1)+" ";
    }
    else {
      calendar[i+j-1] = to_string(j+1);
    }
  }
  cout << "Mo  Tu  We  Th  Fr  Sa  Su" << endl;
  for (int j = 0; j < 42; j++) {
    if (j == 35 && calendar[j] == "  ") {
      cout << endl;
      break;
    }
    cout << calendar[j]+"  ";
    if ((j+1) % 7 == 0) {
      cout << endl;
    }
  }
}

void show_months ()
{
  int year, month;
  cout << "CALENDAR" << endl;
  cout << "Please only enter numerical data" << endl;
  cout << "Please enter the year: ";
  cin >> year;
  cout << "Please enter the month: ";
  cin >> month;
  cout << "Here is the calendar:" << endl << endl;
  show_month(static_cast<Month> (month), year);
}

#ifndef TESTING
int main ()
{
  show_months();
  
  return 0;
}
#endif