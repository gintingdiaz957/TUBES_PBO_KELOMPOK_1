#ifndef RUNNING_H
#define RUNNING_H

#include "Cardio.h"

class Running : public Cardio {

public:

    Running(
        string s,
        string f,
        string i,
        double w
    )
    : Cardio(s,f,i,w){}

    double
    calculateBurnedCalories() const override {

        return 8.0
             * weight
             * (getDuration() / 60.0);
    }

    string
    getActivityName() const override {

        return "Lari";
    }
};

#endif