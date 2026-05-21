// This part complements the AI generated code with more AI generated code. Will redo at some point too.

#include "date.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

bool Date::is_leap_year(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::days_in_month(int m, int y)
{
    switch (m)
    {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return is_leap_year(y) ? 29 : 28;
        default:
            return 0;
    }
}

int Date::to_days()
{
    int y = year;
    int m = month;
    int d = day;
    if (m < 3) { y--; m += 12; }
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {}

bool Date::is_valid()
{
    if (year < 1)                                      return false;
    if (month < 1 || month > 12)                       return false;
    if (day < 1 || day > days_in_month(month, year))   return false;
    return true;
}

int Date::days_until(Date other)
{
    return other.to_days() - this->to_days();
}

void Date::display()
{
    cout << to_string();
}

string Date::to_string()
{
    ostringstream oss;
    oss << setfill('0')
        << setw(2) << day   << "/"
        << setw(2) << month << "/"
        << year;
    return oss.str();
}

Date Date::read_from_input(string prompt)
{
    int d, m, y;
    char slash;

    while (true)
    {
        cout << prompt << " (DD/MM/YYYY): ";
        string input;
        getline(cin, input);

        istringstream iss(input);
        if (iss >> d >> slash >> m >> slash >> y && slash == '/')
        {
            Date date(d, m, y);
            if (date.is_valid())
            {
                return date;
            }
        }
        cout << "  Invalid date, please try again." << endl;
    }
}
