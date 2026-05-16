#ifndef CYCLING_H
#define CYCLING_H

#include "Cardio.h"

class Cycling : public Cardio {

public:

    Cycling(
        string s,
        string f,
        string i,
        double w
    )
    : Cardio(s, f, i, w) {}

    double calculateBurnedCalories() const override {

        return 6.0
             * weight
             * (getDuration() / 60.0);
    }

    string getActivityName() const override {

        return "Bersepeda";
    }
};

#endif