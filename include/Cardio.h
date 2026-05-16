#ifndef CARDIO_H
#define CARDIO_H

#include "HealthActivity.h"

class Cardio : public HealthActivity {

protected:

    double weight;

public:

    Cardio(
        string s,
        string f,
        string i,
        double w
    )
    : HealthActivity(s, f, i)
    {
        weight = w;
    }
};

#endif