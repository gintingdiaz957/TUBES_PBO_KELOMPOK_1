#ifndef STRENGTH_H
#define STRENGTH_H

#include "HealthActivity.h"

class Strength : public HealthActivity {

private:

    double weight;

public:

    Strength(
        string s,
        string f,
        string i,
        double w
    )
    : HealthActivity(s,f,i)
    {

        weight = w;
    }

    double
    calculateBurnedCalories() const override {

        return 5.0
             * weight
             * (getDuration() / 60.0);
    }

    string
    getActivityName() const override {

        return "Latihan Beban";
    }
};

#endif