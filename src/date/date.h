// This part is completely generated with AI, will redo at some point.

#pragma once
#include <string>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    Date(int day = 0, int month = 0, int year = 0);

    int days_until(Date other);

    bool is_valid();

    void display();

    string to_string();

    static Date read_from_input(string prompt);

private:
    int to_days();

    static bool is_leap_year(int year);

    static int days_in_month(int month, int year);
};
