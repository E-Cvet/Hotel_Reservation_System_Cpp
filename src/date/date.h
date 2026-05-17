// This part is completely generated with AI, will redo at some point.


#pragma once
#include <string>

struct Date {
    int day;
    int month;
    int year;

    // Constructor — defaults to an empty/invalid date
    Date(int day = 0, int month = 0, int year = 0);

    // Returns the number of days from this date until other.
    // Returns a negative number if other is before this date.
    int days_until(const Date& other) const;

    // Returns true if the date is a valid calendar date.
    bool is_valid() const;

    // Prints the date in DD/MM/YYYY format.
    void display() const;

    // Returns the date as a string in DD/MM/YYYY format.
    std::string to_string() const;

    // Reads a date from the user via console input.
    // Keeps prompting until a valid date is entered.
    static Date read_from_input(const std::string& prompt);

private:
    // Converts the date to a total day count from a fixed reference point.
    // Used internally by days_until().
    int to_days() const;

    // Returns true if the given year is a leap year.
    static bool is_leap_year(int year);

    // Returns the number of days in the given month of the given year.
    static int days_in_month(int month, int year);
};