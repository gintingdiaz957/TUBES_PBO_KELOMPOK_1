#ifndef HEALTHSUMMARY_H
#define HEALTHSUMMARY_H

#include <iostream>
#include <iomanip>

#include "UserProfile.h"
#include "HealthAnalyzer.h"
#include "Warna.h"

using namespace std;

class HealthSummary {

private:

    string name;

    double weight;
    double height;

    int age;

    string goal;

    double bmi;
    string bmiCategory;

    double idealWeight;
    double recommendedCalories;

public:

    HealthSummary(
        UserProfile& user
    ) {

        name = user.getName();

        weight = user.getWeight();
        height = user.getHeight();

        age = user.getAge();

        goal = user.getGoal();

        bmi =
        HealthAnalyzer
        ::calculateBMI(
            weight,
            height
        );

        bmiCategory =
        HealthAnalyzer
        ::getBMICategory(
            bmi
        );

        idealWeight =
        user.getIdealWeight();

        recommendedCalories =
        user.getRecommendedCalories();
    }

    friend ostream& operator<<(
        ostream& os,
        const HealthSummary& summary
    ) {

        setColor(6);
        os << "RINGKASAN PROFIL\n";

        setColor(11);
        os << "========================================================\n\n";

        resetColor();

        os << "Nama                : "
           << summary.name
           << endl;

        os << "Berat Badan         : "
           << summary.weight
           << " kg\n";

        os << "Tinggi Badan        : "
           << summary.height
           << " cm\n";

        os << "Umur                : "
           << summary.age
           << endl;

        os << "Tujuan              : "
           << summary.goal
           << endl;

        os << "BMI                 : "
           << fixed
           << setprecision(1)
           << summary.bmi
           << " ("
           << summary.bmiCategory
           << ")\n";

        os << "Berat Badan Ideal   : "
           << summary.idealWeight
           << " kg\n";

        os << "Kebutuhan Kalori    : "
           << summary.recommendedCalories
           << " kcal\n";

        resetColor();

        return os;
    }
};

#endif