#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class InputValidator {

private:

    static bool isLeapYear(
        int year
    ) {

        if(year % 400 == 0) {

            return true;
        }

        if(year % 100 == 0) {

            return false;
        }

        return year % 4 == 0;
    }

    static int getDaysInMonth(
        int month,
        int year
    ) {

        switch(month) {

            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:

                return 31;

            case 4:
            case 6:
            case 9:
            case 11:

                return 30;

            case 2:

                if(isLeapYear(year)) {

                    return 29;
                }

                return 28;

            default:

                return 0;
        }
    }

public:

    static bool isValidDate(
        int day,
        int month,
        int year
    ) {

        if(year < 1900 || year > 2100) {

            return false;
        }

        if(month < 1 || month > 12) {

            return false;
        }

        int maxDay =
        getDaysInMonth(
            month,
            year
        );

        if(day < 1 || day > maxDay) {

            return false;
        }

        return true;
    }

    static bool isValidTime(
        string time
    ) {

        if(time.length() != 5) {

            return false;
        }

        if(time[2] != ':') {

            return false;
        }

        if(!isdigit(time[0]) ||
           !isdigit(time[1]) ||
           !isdigit(time[3]) ||
           !isdigit(time[4]))
        {

            return false;
        }

        int hour =
        stoi(time.substr(0,2));

        int minute =
        stoi(time.substr(3,2));

        if(hour < 0 || hour > 23) {

            return false;
        }

        if(minute < 0 || minute > 59) {

            return false;
        }

        return true;
    }

    static string formatDate(
        int day,
        int month,
        int year
    ) {

        stringstream ss;

        ss << setw(2)
           << setfill('0')
           << day
           << "-";

        ss << setw(2)
           << setfill('0')
           << month
           << "-";

        ss << year;

        return ss.str();
    }
};

#endif