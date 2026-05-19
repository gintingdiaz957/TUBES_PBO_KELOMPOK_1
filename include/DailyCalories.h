#ifndef DAILYCALORIES_H
#define DAILYCALORIES_H

#include <iostream>

using namespace std;

class DailyCalories {

private:

    string date;

    double calories;

public:

    DailyCalories(
        string d = "",
        double c = 0
    ) {
        date = d;
        calories = c;
    }

    string getDate() const {

        return date;
    }

    double getCalories() const {

        return calories;
    }

    DailyCalories operator+(
        const DailyCalories& other
    ) const {

        return DailyCalories(
            date,
            calories + other.calories
        );
    }
};

#endif