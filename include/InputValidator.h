#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "Warna.h"

using namespace std;

class InputValidator {

private:

    static bool parseInt(string input, int& value) {

        stringstream ss(input);

        ss >> value;

        return !ss.fail() && ss.eof();
    }

    static bool parseDouble(string input, double& value) {

        stringstream ss(input);

        ss >> value;

        return !ss.fail() && ss.eof();
    }

    static bool isLeapYear(int year) {

        if(year % 400 == 0) return true;
        if(year % 100 == 0) return false;

        return year % 4 == 0;
    }

    static int getDaysInMonth(int month, int year) {

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
                return isLeapYear(year) ? 29 : 28;

            default:
                return 0;
        }
    }

public:

    static int inputInt(
        string label,
        int min,
        int max,
        string errorMessage
    ) {

        string input;
        int value;

        while(true) {

            setColor(14);
            cout << label;

            resetColor();
            cin >> input;

            if(!parseInt(input, value)) {

                setColor(12);
                cout << "Input harus berupa angka!\n\n";
                resetColor();

                continue;
            }

            if(value < min || value > max) {

                setColor(12);
                cout << errorMessage << "\n\n";
                resetColor();

                continue;
            }

            return value;
        }
    }

    static double inputDouble(
        string label,
        double min,
        double max,
        string errorMessage
    ) {

        string input;
        double value;

        while(true) {

            setColor(14);
            cout << label;

            resetColor();
            cin >> input;

            if(!parseDouble(input, value)) {

                setColor(12);
                cout << "Input harus berupa angka!\n\n";
                resetColor();

                continue;
            }

            if(value < min || value > max) {

                setColor(12);
                cout << errorMessage << "\n\n";
                resetColor();

                continue;
            }

            return value;
        }
    }

    static string inputName(string label) {

        string name;

        do {

            setColor(14);
            cout << label;

            resetColor();
            getline(cin >> ws, name);

            if(name.length() < 2) {

                setColor(12);
                cout << "Nama Tidak Valid!\n\n";
                resetColor();
            }

        } while(name.length() < 2);

        return name;
    }

    static bool isValidDate(
        int day,
        int month,
        int year
    ) {

        if(year < 1900 || year > 2100) return false;
        if(month < 1 || month > 12) return false;

        int maxDay =
        getDaysInMonth(month, year);

        return day >= 1 && day <= maxDay;
    }

    static string formatDate(
        int day,
        int month,
        int year
    ) {

        stringstream ss;

        ss << setw(2) << setfill('0') << day << "-";
        ss << setw(2) << setfill('0') << month << "-";
        ss << year;

        return ss.str();
    }

    static string inputDate() {

        int day;
        int month;
        int year;

        while(true) {

            day =
            inputInt(
                "Tanggal : ",
                1,
                31,
                "Tanggal harus 1-31!"
            );

            month =
            inputInt(
                "Bulan   : ",
                1,
                12,
                "Bulan harus 1-12!"
            );

            year =
            inputInt(
                "Tahun   : ",
                1900,
                2100,
                "Tahun harus 1900-2100!"
            );

            if(isValidDate(day, month, year)) {

                return formatDate(
                    day,
                    month,
                    year
                );
            }

            setColor(12);
            cout << "Tanggal tidak valid! Coba masukkan lagi.\n\n";
            resetColor();
        }
    }

    static bool isValidTime(string time) {

        if(time.length() != 5) return false;
        if(time[2] != ':') return false;

        if(!isdigit(time[0]) ||
           !isdigit(time[1]) ||
           !isdigit(time[3]) ||
           !isdigit(time[4]))
        {
            return false;
        }

        int hour =
        stoi(time.substr(0, 2));

        int minute =
        stoi(time.substr(3, 2));

        return hour >= 0 &&
               hour <= 23 &&
               minute >= 0 &&
               minute <= 59;
    }

    static string inputTime(
        string label,
        string errorMessage
    ) {

        string time;

        while(true) {

            setColor(14);
            cout << label;

            resetColor();
            cin >> time;

            if(isValidTime(time)) {

                return time;
            }

            setColor(12);
            cout << errorMessage << "\n\n";
            resetColor();
        }
    }
};

#endif