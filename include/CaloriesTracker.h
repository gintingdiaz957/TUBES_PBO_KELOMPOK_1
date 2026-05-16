#ifndef CALORIESTRACKER_H
#define CALORIESTRACKER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>

#include "Warna.h"

using namespace std;

class CaloriesTracker {

private:

    map<string, double>
    caloriesByDate;

    double totalCalories;

    string trimString(string text) {

        size_t start =
        text.find_first_not_of(" \t\r\n");

        size_t end =
        text.find_last_not_of(" \t\r\n");

        if(start == string::npos) {

            return "";
        }

        return text.substr(
            start,
            end - start + 1
        );
    }

public:

    CaloriesTracker() {

        totalCalories = 0;

        loadCalories();
    }

    void loadCalories() {

        caloriesByDate.clear();
        totalCalories = 0;

        ifstream file("health_logs.txt");

        if(!file.is_open()) {

            return;
        }

        string line;
        string currentDate;
        bool inDataSection = false;

        set<string> seen;

        while(getline(file, line)) {

            if(!line.empty() && line.back() == '\r') {

                line.pop_back();
            }

            if(line.find("Date : ") != string::npos) {

                currentDate =
                trimString(line.substr(7));

                inDataSection = false;
            }

            else if(!currentDate.empty()
                 && line.find("Activity") != string::npos
                 && line.find("Calories") != string::npos) {

                inDataSection = true;
            }

            else if(line.find("===") != string::npos
                 || line.empty()) {

                inDataSection = false;
            }

            else if(inDataSection
                 && line.size() >= 60) {

                string activity =
                trimString(line.substr(0, 15));

                string start =
                trimString(line.substr(15, 15));

                string finish =
                trimString(line.substr(30, 15));

                string duration =
                trimString(line.substr(45, 15));

                string caloriesText =
                trimString(line.substr(60, 15));

                if(activity.empty()
                   || caloriesText.empty())
                {
                    continue;
                }

                string key =
                currentDate + "|" +
                activity + "|" +
                start + "|" +
                finish + "|" +
                duration + "|" +
                caloriesText;

                if(seen.find(key) != seen.end()) {

                    continue;
                }

                seen.insert(key);

                stringstream ss(caloriesText);

                double calories = 0;

                ss >> calories;

                if(!ss.fail()) {

                    caloriesByDate[currentDate]
                    += calories;

                    totalCalories += calories;
                }
            }
        }

        file.close();
    }

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

        resetColor();
        cout << " kcal\n\n";

        setColor(6);
        cout << "Kalori Per Tanggal\n";

        setColor(11);
        cout << "--------------------------------------------------------\n";

        if(caloriesByDate.empty()) {

            setColor(12);
            cout << "Belum ada data kalori tersimpan.\n";
        }

        for(auto& pair : caloriesByDate) {

            setColor(8);
            cout << "Tanggal ";

            resetColor();
            cout << pair.first;

            setColor(8);
            cout << " : ";

            setColor(10);
            cout << pair.second;

            resetColor();
            cout << " kcal\n";
        }

        cout << endl;

        resetColor();
    }
};

#endif