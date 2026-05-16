#ifndef CALORIESTRACKER_H
#define CALORIESTRACKER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

#include "Warna.h"

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

        setColor(11);
        cout << "\n========================================================\n";

        setColor(6);
        cout << "               RINGKASAN KALORI\n";

        setColor(11);
        cout << "========================================================\n\n";

        cout << fixed
             << setprecision(1);

        setColor(14);
        cout << "Total Kalori Terbakar : ";

        setColor(10);
        cout << totalCalories;

        setColor(15);
        cout << " kcal\n\n";

        setColor(6);
        cout << "Kalori Per Tanggal\n";

        setColor(11);
        cout << "--------------------------------------------------------\n";

        for(auto& pair
            : caloriesByDate)
        {
            setColor(8);
            cout << "Tanggal ";

            setColor(15);
            cout << pair.first;

            setColor(8);
            cout << " : ";

            setColor(10);
            cout << pair.second;

            setColor(15);
            cout << " kcal\n";
        }

        cout << endl;

        resetColor();
    }
};

#endif