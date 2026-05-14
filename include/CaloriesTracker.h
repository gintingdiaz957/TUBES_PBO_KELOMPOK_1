#ifndef CALORIESTRACKER_H
#define CALORIESTRACKER_H

#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

#include "HealthActivity.h"

using namespace std;

class CaloriesTracker {

private:

    map<
        string,
        vector<HealthActivity*>
    >& history;

public:

    CaloriesTracker(

        map<
            string,
            vector<HealthActivity*>
        >& h

    ) : history(h) {}

    // =====================================
    // TOTAL ALL CALORIES
    // =====================================

    double getTotalCalories() {

        double total = 0;

        for(auto& pair : history) {

            for(auto activity
                : pair.second)
            {

                total +=
                activity
                ->calculateBurnedCalories();
            }
        }

        return total;
    }

    // =====================================
    // TOTAL BY DATE
    // =====================================

    double getCaloriesByDate(
        string date
    ) {

        double total = 0;

        if(history.find(date)
           != history.end())
        {

            for(auto activity
                : history[date])
            {

                total +=
                activity
                ->calculateBurnedCalories();
            }
        }

        return total;
    }

    // =====================================
    // TOTAL ACTIVITIES
    // =====================================

    int getTotalActivities() {

        int total = 0;

        for(auto& pair : history) {

            total +=
            pair.second.size();
        }

        return total;
    }

    // =====================================
    // HIGHEST CALORIE ACTIVITY
    // =====================================

    string getHighestBurnActivity() {

        double highest = 0;

        string result =
        "No Activity";

        for(auto& pair : history) {

            for(auto activity
                : pair.second)
            {

                double calories =
                activity
                ->calculateBurnedCalories();

                if(calories > highest) {

                    highest = calories;

                    result =
                    activity
                    ->getActivityName();
                }
            }
        }

        return result;
    }

    // =====================================
    // SHOW SUMMARY
    // =====================================

    void showSummary() {

        cout << "\n========================================================\n";

        cout << "                 CALORIES SUMMARY\n";

        cout << "========================================================\n\n";

        cout << fixed
             << setprecision(1);

        cout << "Total Calories Burned : "
             << getTotalCalories()
             << " kcal\n";

        cout << "Total Activities      : "
             << getTotalActivities()
             << endl;

        cout << "Highest Burn Activity : "
             << getHighestBurnActivity()
             << endl;

        cout << "\n========================================================\n";

        cout << "\nCALORIES BY DATE\n\n";

        for(auto& pair : history) {

            cout << "Date "
                 << pair.first
                 << " : "
                 << getCaloriesByDate(
                        pair.first
                    )
                 << " kcal\n";
        }

        cout << endl;
    }
};

#endif