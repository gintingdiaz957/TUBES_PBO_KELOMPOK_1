#ifndef GOALVIEW_H
#define GOALVIEW_H

#include <iostream>

#include "UserProfile.h"
#include "HistoryManager.h"
#include "GoalTracker.h"
#include "HealthAnalyzer.h"
#include "Warna.h"

using namespace std;

class GoalView {

public:

    static void showGoals(
        UserProfile& user,
        HistoryManager& manager
    ) {

        setColor(11);
        cout << "=== ";

        setColor(6);
        cout << "TARGET KESEHATAN";

        setColor(11);
        cout << " ===\n\n";

        resetColor();

        GoalTracker<double> calorieGoal(
            "Target Kalori Harian",
            user.getRecommendedCalories(),
            user.getRecommendedCalories(),
            "kcal"
        );

        GoalTracker<int> activityGoal(
            "Target Aktivitas",
            5,
            manager.getTotalActivities(),
            "aktivitas"
        );

        double bmi =
        HealthAnalyzer
        ::calculateBMI(
            user.getWeight(),
            user.getHeight()
        );

        GoalTracker<double> bmiGoal(
            "Target BMI Normal",
            25.0,
            bmi,
            "BMI"
        );

        calorieGoal.showGoal();

        cout << "\n";

        activityGoal.showGoal();

        cout << "\n";

        bmiGoal.showGoal();
    }
};

#endif