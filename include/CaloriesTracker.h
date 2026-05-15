#ifndef CALORIESTRACKER_H
#define CALORIESTRACKER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

class CaloriesTracker {

private:

    map<string,double>
    caloriesByDate;

    double totalCalories;

public:

    CaloriesTracker() {

        totalCalories = 0;

        loadCalories();
    }

    // =====================================
    // LOAD FROM TXT
    // =====================================

    void loadCalories() {

        ifstream file(
            "health_logs.txt"
        );

        string line;

        string currentDate;

        while(getline(file,line)) {

            // =============================
            // GET DATE
            // =============================

            if(line.find("Date : ")
               != string::npos)
            {

                currentDate =
                line.substr(7);
            }

            // =============================
            // GET CALORIES
            // =============================

            else if(
                line.find("Calories")
                != string::npos
            &&
                line.find("Calories Burned")
                == string::npos
            ) {

                stringstream ss(line);

                string temp;

                double calories;

                ss >> temp;

                ss >> calories;

                caloriesByDate[
                    currentDate
                ] += calories;

                totalCalories +=
                calories;
            }
        }

        file.close();
    }

    // =====================================
    // SHOW SUMMARY
    // =====================================

    void showSummary() {

        cout << "\n========================================================\n";

        cout << "                CALORIES SUMMARY\n";

        cout << "========================================================\n\n";

        cout << fixed
             << setprecision(1);

        cout << "Total Calories Burned : "
             << totalCalories
             << " kcal\n\n";

        cout << "Calories By Date\n";

        cout << "--------------------------------------------------------\n";

        for(auto& pair
            : caloriesByDate)
        {

            cout << "Date "
                 << pair.first
                 << " : "
                 << pair.second
                 << " kcal\n";
        }

        cout << endl;
    }
};

#endif