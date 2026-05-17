// This part complements the AI generated code with more AI generated code. Will redo at some point too.

#include "date.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// ── Helpers ───────────────────────────────────────────────────────────────────

bool Date::is_leap_year(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::days_in_month(int m, int y) {
    switch (m) {
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

// Converts the date into a total number of days from a fixed reference point.
// Uses the standard Julian Day Number formula so arithmetic works correctly
// across month and year boundaries.
int Date::to_days() const {
    int y = year;
    int m = month;
    int d = day;
    if (m < 3) { y--; m += 12; }
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

// ── Constructor ───────────────────────────────────────────────────────────────

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {}

// ── Public methods ────────────────────────────────────────────────────────────

bool Date::is_valid() const {
    if (year < 1)                          return false;
    if (month < 1 || month > 12)           return false;
    if (day < 1 || day > days_in_month(month, year)) return false;
    return true;
}

int Date::days_until(const Date& other) const {
    return other.to_days() - this->to_days();
}

void Date::display() const {
    std::cout << to_string();
}

std::string Date::to_string() const {
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << day   << "/"
        << std::setw(2) << month << "/"
        << year;
    return oss.str();
}

// Prompts the user to enter a date, re-asking on invalid input.
Date Date::read_from_input(const std::string& prompt) {
    int d, m, y;
    char slash;

    while (true) {
        std::cout << prompt << " (DD/MM/YYYY): ";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        if (iss >> d >> slash >> m >> slash >> y && slash == '/') {
            Date date(d, m, y);
            if (date.is_valid()) {
                return date;
            }
        }
        std::cout << "  Invalid date, please try again.\n";
    }
}