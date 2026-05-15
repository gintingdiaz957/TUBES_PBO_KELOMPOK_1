#ifndef SLEEP_H
#define SLEEP_H

#include "HealthActivity.h"

class SleepActivity : public HealthActivity {

private:

    double hours;

public:

    SleepActivity(
        string s,
        string f,
        string i,
        double h
    )
    : HealthActivity(s,f,i)
    {

        hours = h;
    }

    double
    calculateBurnedCalories() const override {

        return 50 * hours;
    }

    string
    getActivityName() const override {

        return "Tidur";
    }

    string getSleepQuality() {

        if(hours >= 8) {
            return "Sangat Baik";
        }

        else if(hours >= 6) {
            return "Baik";
        }

        return "Kurang";
    }
};

#endif