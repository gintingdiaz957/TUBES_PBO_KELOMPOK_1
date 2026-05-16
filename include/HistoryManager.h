#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <iostream>
#include <map>
#include <set>        
#include <vector>
#include <fstream>
#include <sstream>    
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "HealthActivity.h"
#include "Warna.h"

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

        setColor(11);
        cout << "\n========================================================\n";

        setColor(6);
        cout << "                   RIWAYAT AKTIVITAS\n";

        setColor(11);
        cout << "========================================================\n\n";

        for (auto &pair : history)
        {

            setColor(8);
            cout << "Tanggal : ";

            setColor(15);
            cout << pair.first
                 << endl;

            setColor(11);
            cout << "---------------------------------------------------------------------\n";

            for (auto activity : pair.second)
            {

                cout
                    << *activity
                    << endl;
            }
        }

        resetColor();
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

        file << "Disimpan Pada : "
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
    // SHOW HISTORY FROM FILE
    // =====================================

    void showHistoryFromFile() {

        setColor(11);
        cout << "\n=====================================================================\n";

        setColor(6);
        cout << "                   RIWAYAT AKTIVITAS\n";

        setColor(11);
        cout << "=====================================================================\n\n";

        ifstream file("health_logs.txt");

        if (!file.is_open()) {

            setColor(12);
            cout << "Belum ada riwayat aktivitas tersimpan.\n";

            resetColor();

            return;
        }

        struct ActivityRecord {
            string activity;
            string start;
            string finish;
            string duration;
            string calories;
        };

        map<string, vector<ActivityRecord>> fileHistory;
        map<string, set<string>> seen;

        string line;
        string currentDate = "";
        bool inDataSection = false;

        while (getline(file, line)) {

            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            if (line.find("Date : ") != string::npos) {

                currentDate = line.substr(7);

                size_t start = currentDate.find_first_not_of(" \t");
                size_t end   = currentDate.find_last_not_of(" \t");

                if (start != string::npos) {
                    currentDate = currentDate.substr(start, end - start + 1);
                }

                inDataSection = false;
            }

            else if (!currentDate.empty()
                && line.find("Activity") != string::npos
                && line.find("Start")    != string::npos) {

                inDataSection = true;
            }

            else if (line.find("===") != string::npos
                  || line.find("Saved At") != string::npos) {

                inDataSection = false;
            }

            else if (inDataSection && line.size() >= 45) {

                auto trimStr = [](string s) -> string {
                    size_t st = s.find_first_not_of(" \t");
                    size_t en = s.find_last_not_of(" \t");
                    return (st == string::npos) ? "" : s.substr(st, en - st + 1);
                };

                ActivityRecord rec;
                rec.activity = trimStr(line.substr(0, 15));
                rec.start    = trimStr(line.substr(15, 15));
                rec.finish   = trimStr(line.substr(30, 15));
                rec.duration = trimStr(line.substr(45, 15));

                if (line.size() >= 60) {
                    rec.calories = trimStr(line.substr(60));
                }

                if (rec.activity.empty()) continue;

                string key = rec.activity + "|" + rec.start + "|" + rec.finish;

                if (seen[currentDate].find(key) == seen[currentDate].end()) {
                    seen[currentDate].insert(key);
                    fileHistory[currentDate].push_back(rec);
                }
            }
        }

        file.close();

        if (fileHistory.empty()) {

            setColor(12);
            cout << "Belum ada riwayat aktivitas tersimpan.\n";

            resetColor();

            return;
        }

        for (auto& pair : fileHistory) {

            setColor(8);
            cout << "Tanggal : ";

            setColor(15);
            cout << pair.first << "\n";

            setColor(11);
            cout << "---------------------------------------------------------------------\n";

            setColor(6);
            cout << left
                 << setw(15) << "Aktivitas"
                 << setw(15) << "Mulai"
                 << setw(15) << "Selesai"
                 << setw(15) << "Durasi"
                 << setw(15) << "Kalori"
                 << "\n";

            setColor(15);

            for (auto& rec : pair.second) {

                setColor(15);
                cout << left
                     << setw(15) << rec.activity;

                setColor(10);
                cout << setw(15) << rec.start
                     << setw(15) << rec.finish
                     << setw(15) << rec.duration
                     << setw(15) << rec.calories
                     << "\n";
            }

            cout << "\n";
        }

        resetColor();
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