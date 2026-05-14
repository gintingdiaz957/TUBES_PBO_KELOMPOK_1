#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "HealthActivity.h"

using namespace std;

class HistoryManager
{

private:
    map<
        string,
        vector<HealthActivity *>>
        history;

public:
    void addActivity(
        string date,
        HealthActivity *activity)
    {

        history[date]
            .push_back(activity);
    }

    // =====================================
    // SHOW HISTORY
    // =====================================

    void showHistory()
    {

        cout << "\n========================================================\n";
        cout << "                    ACTIVITY HISTORY\n";
        cout << "========================================================\n\n";

        for (auto &pair : history)
        {

            cout << "Date : "
                 << pair.first
                 << endl;

            cout << "--------------------------------------------------------\n";

            for (auto activity : pair.second)
            {

                cout
                    << *activity
                    << endl;
            }
        }
    }

    // =====================================
    // SAVE TO TXT
    // =====================================

    void saveToFile()
    {

        ofstream file(
            "health_logs.txt",
            ios::app);

        time_t now =
            time(0);

        char *dt =
            ctime(&now);

        file << "========================================================\n";

        file << "Saved At : "
             << dt;

        file << "========================================================\n";

        for (auto &pair : history)
        {

            file << "\nDate : "
                 << pair.first
                 << "\n\n";

            file
                << left
                << setw(15)
                << "Activity"

                << setw(15)
                << "Start"

                << setw(15)
                << "Finish"

                << setw(15)
                << "Duration"

                << setw(15)
                << "Calories"

                << endl;

            for (auto activity : pair.second)
            {

                file
                    << setw(15)
                    << activity
                           ->getActivityName();

                file
                    << setw(15)
                    << activity
                           ->getStartTime();

                file
                    << setw(15)
                    << activity
                           ->getFinishTime();

                file
                    << setw(15)
                    << activity
                           ->getDuration();

                file
                    << setw(15)
                    << activity
                           ->calculateBurnedCalories();

                file
                    << endl;
            }
        }

        file << "\n\n";

        file.close();
    }

    // =====================================
    // DESTRUCTOR
    // =====================================

    map<
        string,
        vector<HealthActivity *>> &
    getHistory()
    {

        return history;
    }
    ~HistoryManager()
    {

        for (auto &pair : history)
        {

            for (auto activity : pair.second)
            {

                delete activity;
            }
        }
    }
};

#endif