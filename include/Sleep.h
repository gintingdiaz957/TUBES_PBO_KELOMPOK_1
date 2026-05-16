#ifndef SLEEP_H
#define SLEEP_H

#include <sstream>

#include "HealthActivity.h"

class SleepActivity : public HealthActivity {

private:

    double hours;
    int age;

    double getMinimumSleepHour() const {

        if(age >= 6 && age <= 12) return 9;
        if(age >= 13 && age <= 17) return 8;

        return 7;
    }

    double getMaximumSleepHour() const {

        if(age >= 6 && age <= 12) return 12;
        if(age >= 13 && age <= 17) return 10;

        return 9;
    }

public:

    SleepActivity(
        string s,
        string f,
        string i,
        double h,
        int a
    )
    : HealthActivity(s, f, i)
    {
        hours = getDuration() / 60.0;
        age = a;
    }

    double calculateBurnedCalories() const override {

        return 50 * hours;
    }

    string getActivityName() const override {

        return "Tidur";
    }

    double getSleepHours() const {

        return hours;
    }

    string getSleepQuality() const {

        double minHour = getMinimumSleepHour();
        double maxHour = getMaximumSleepHour();

        if(hours < minHour - 1) return "Kurang";
        if(hours < minHour) return "Hampir Cukup";
        if(hours <= maxHour) return "Baik";
        if(hours <= maxHour + 1) return "Sedikit Berlebih";

        return "Berlebih";
    }

    string getRecommendedSleepRange() const {

        stringstream ss;

        ss << getMinimumSleepHour()
           << "-"
           << getMaximumSleepHour()
           << " jam";

        return ss.str();
    }

    string getActivityNote() const override {

        return getSleepQuality()
             + " ("
             + getRecommendedSleepRange()
             + ")";
    }
};

#endif