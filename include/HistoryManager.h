#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "HealthActivity.h"
#include "Warna.h"

using namespace std;

class HistoryManager {

private:

    map<string, vector<HealthActivity*>>
    history;

    struct ActivityRecord {

        string activity;
        string start;
        string finish;
        string duration;
        string calories;
        string note;
    };

    string trimStr(string s) {

        size_t st =
        s.find_first_not_of(" \t");

        size_t en =
        s.find_last_not_of(" \t");

        return (st == string::npos)
             ? ""
             : s.substr(st, en - st + 1);
    }

public:

    void addActivity(
        string date,
        HealthActivity* activity
    ) {

        history[date]
        .push_back(activity);
    }

    void saveToFile() {

        ofstream file(
            "health_logs.txt",
            ios::app
        );

        time_t now = time(0);
        char* dt = ctime(&now);

        file << "========================================================\n";
        file << "Disimpan Pada : " << dt;
        file << "========================================================\n";

        for(auto& pair : history) {

            file << "\nDate : "
                 << pair.first
                 << "\n\n";

            file << left
                 << setw(15) << "Activity"
                 << setw(15) << "Start"
                 << setw(15) << "Finish"
                 << setw(15) << "Duration"
                 << setw(15) << "Calories"
                 << setw(25) << "Note"
                 << endl;

            for(auto activity : pair.second) {

                file << setw(15)
                     << activity->getActivityName();

                file << setw(15)
                     << activity->getStartTime();

                file << setw(15)
                     << activity->getFinishTime();

                file << setw(15)
                     << activity->getDuration();

                file << setw(15)
                     << activity->calculateBurnedCalories();

                file << setw(25)
                     << activity->getActivityNote();

                file << endl;
            }
        }

        file << "\n\n";
        file.close();
    }

    void showHistoryFromFile() {

        setColor(11);
        cout << "\n=====================================================================\n";

        setColor(6);
        cout << "                   RIWAYAT AKTIVITAS\n";

        setColor(11);
        cout << "=====================================================================\n\n";

        ifstream file("health_logs.txt");

        if(!file.is_open()) {

            setColor(12);
            cout << "Belum ada riwayat aktivitas tersimpan.\n";
            resetColor();

            return;
        }

        map<string, vector<ActivityRecord>> fileHistory;
        map<string, set<string>> seen;

        string line;
        string currentDate = "";
        bool inDataSection = false;

        while(getline(file, line)) {

            if(!line.empty() && line.back() == '\r') {

                line.pop_back();
            }

            if(line.find("Date : ") != string::npos) {

                currentDate =
                trimStr(line.substr(7));

                inDataSection = false;
            }

            else if(!currentDate.empty()
                 && line.find("Activity") != string::npos
                 && line.find("Start") != string::npos) {

                inDataSection = true;
            }

            else if(line.find("===") != string::npos
                 || line.find("Disimpan Pada") != string::npos) {

                inDataSection = false;
            }

            else if(inDataSection && line.size() >= 45) {

                ActivityRecord rec;

                rec.activity = trimStr(line.substr(0, 15));
                rec.start    = trimStr(line.substr(15, 15));
                rec.finish   = trimStr(line.substr(30, 15));
                rec.duration = trimStr(line.substr(45, 15));

                rec.calories =
                line.size() >= 60
                ? trimStr(line.substr(60, 15))
                : "";

                rec.note =
                line.size() >= 75
                ? trimStr(line.substr(75))
                : "-";

                if(rec.note.empty()) rec.note = "-";
                if(rec.activity.empty()) continue;

                string key =
                rec.activity + "|" +
                rec.start + "|" +
                rec.finish + "|" +
                rec.duration + "|" +
                rec.calories + "|" +
                rec.note;

                if(seen[currentDate].find(key)
                   == seen[currentDate].end())
                {
                    seen[currentDate].insert(key);
                    fileHistory[currentDate].push_back(rec);
                }
            }
        }

        file.close();

        if(fileHistory.empty()) {

            setColor(12);
            cout << "Belum ada riwayat aktivitas tersimpan.\n";
            resetColor();

            return;
        }

        for(auto& pair : fileHistory) {

            setColor(8);
            cout << "Tanggal : ";

            resetColor();
            cout << pair.first << "\n";

            setColor(11);
            cout << "---------------------------------------------------------------------\n";

            setColor(6);
            cout << left
                 << setw(18) << "Aktivitas"
                 << setw(15) << "Mulai"
                 << setw(15) << "Selesai"
                 << setw(15) << "Durasi"
                 << setw(15) << "Kalori"
                 << "\n";

            setColor(11);
            cout << "---------------------------------------------------------------------\n";

            for(auto& rec : pair.second) {

                resetColor();
                cout << left
                     << setw(18) << rec.activity;

                setColor(10);
                cout << setw(15) << rec.start
                     << setw(15) << rec.finish
                     << setw(15) << rec.duration
                     << setw(15) << rec.calories
                     << "\n";

                if(rec.activity == "Tidur"
                   && rec.note != "-")
                {
                    setColor(14);
                    cout << "  -> Kualitas Tidur : ";

                    setColor(10);
                    cout << rec.note << "\n";
                }
            }

            cout << "\n";
        }

        resetColor();
    }

    map<string, vector<HealthActivity*>>& getHistory() {

        return history;
    }

    ~HistoryManager() {

        for(auto& pair : history) {

            for(auto activity : pair.second) {

                delete activity;
            }
        }
    }
};

#endif