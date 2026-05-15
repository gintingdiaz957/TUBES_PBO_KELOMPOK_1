#ifndef HEALTHANALYZER_H
#define HEALTHANALYZER_H

#include <iostream>

using namespace std;

class HealthAnalyzer {

public:

    static double calculateBMI(
        double weight,
        double height
    ) {

        double meter =
        height / 100;

        return weight /
              (meter * meter);
    }

    static string getBMICategory(
        double bmi
    ) {

        if(bmi < 18.5) {

            return "Kurus";
        }

        else if(bmi < 25) {

            return "Normal";
        }

        else if(bmi < 30) {

            return "Kelebihan Berat Badan";
        }

        return "Obesitas";
    }
};

#endif