#ifndef REPORTFEATURES_H
#define REPORTFEATURES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>

#include "InputValidator.h"
#include "Warna.h"

using namespace std;

struct ReportRecord {

    string date;
    string activity;
    string start;
    string finish;
    string duration;
    double calories;
};

class ReportFeatures {

private:

    static string trimString(string text) {

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

    static int dateToNumber(string date) {

        int day;
        int month;
        int year;

        char dash1;
        char dash2;

        stringstream ss(date);

        ss >> day
           >> dash1
           >> month
           >> dash2
           >> year;

        tm timeInfo = {};

        timeInfo.tm_mday = day;
        timeInfo.tm_mon = month - 1;
        timeInfo.tm_year = year - 1900;

        time_t timeValue =
        mktime(&timeInfo);

        return static_cast<int>(
            timeValue / (60 * 60 * 24)
        );
    }

    static void showBar(double calories) {

        int totalBar =
        static_cast<int>(
            calories / 50
        );

        if(totalBar > 20) {

            totalBar = 20;
        }

        setColor(10);

        for(int i = 0; i < totalBar; i++) {

            cout << "#";
        }

        resetColor();
    }

    static void showProgressBar(double percent) {

        if(percent > 100) {

            percent = 100;
        }

        int filled =
        static_cast<int>(
            percent / 5
        );

        setColor(10);
        cout << "[";

        for(int i = 0; i < 20; i++) {

            if(i < filled) {

                cout << "#";
            }

            else {

                cout << "-";
            }
        }

        cout << "]";

        resetColor();
    }

public:

    static vector<ReportRecord> readHealthLogs() {

        vector<ReportRecord> records;

        ifstream file("health_logs.txt");

        if(!file.is_open()) {

            return records;
        }

        string line;
        string currentDate = "";
        bool inDataSection = false;

        set<string> seen;

        while(getline(file, line)) {

            if(!line.empty() && line.back() == '\r') {

                line.pop_back();
            }

            if(line.find("Date : ") != string::npos) {

                currentDate =
                trimString(
                    line.substr(7)
                );

                inDataSection = false;
            }

            else if(!currentDate.empty()
                 && line.find("Activity") != string::npos
                 && line.find("Start") != string::npos) {

                inDataSection = true;
            }

            else if(line.find("===") != string::npos
                 || line.find("Disimpan Pada") != string::npos
                 || line.empty()) {

                inDataSection = false;
            }

            else if(inDataSection && line.size() >= 60) {

                ReportRecord rec;

                rec.date =
                currentDate;

                rec.activity =
                trimString(
                    line.substr(0, 15)
                );

                rec.start =
                trimString(
                    line.substr(15, 15)
                );

                rec.finish =
                trimString(
                    line.substr(30, 15)
                );

                rec.duration =
                trimString(
                    line.substr(45, 15)
                );

                string caloriesText =
                trimString(
                    line.substr(60, 15)
                );

                if(rec.activity.empty()
                   || caloriesText.empty())
                {
                    continue;
                }

                stringstream ss(caloriesText);

                rec.calories = 0;

                ss >> rec.calories;

                if(ss.fail()) {

                    continue;
                }

                string key =
                rec.date
                + "|"
                + rec.activity
                + "|"
                + rec.start
                + "|"
                + rec.finish
                + "|"
                + rec.duration
                + "|"
                + caloriesText;

                if(seen.find(key) != seen.end()) {

                    continue;
                }

                seen.insert(key);

                records.push_back(rec);
            }
        }

        file.close();

        return records;
    }

    static void showDailyProgress() {

        vector<ReportRecord> records =
        readHealthLogs();

        setColor(11);
        cout << "=== ";

        setColor(6);
        cout << "PROGRESS TARGET HARIAN";

        setColor(11);
        cout << " ===\n\n";

        resetColor();

        if(records.empty()) {

            setColor(12);
            cout << "Belum ada data aktivitas tersimpan.\n";

            resetColor();

            return;
        }

        string date =
        InputValidator
        ::inputDate();

        double target =
        InputValidator
        ::inputDouble(
            "Target Kalori Harian (kcal): ",
            1,
            10000,
            "Target kalori tidak valid!"
        );

        double totalCalories = 0;

        for(auto& rec : records) {

            if(rec.date == date) {

                totalCalories +=
                rec.calories;
            }
        }

        double percent =
        (totalCalories / target) * 100;

        cout << fixed
             << setprecision(1);

        setColor(8);
        cout << "\nTanggal         : ";

        resetColor();
        cout << date << endl;

        setColor(8);
        cout << "Kalori Tercapai : ";

        setColor(10);
        cout << totalCalories
             << " kcal\n";

        setColor(8);
        cout << "Target Kalori   : ";

        setColor(10);
        cout << target
             << " kcal\n";

        setColor(8);
        cout << "Progress        : ";

        showProgressBar(percent);

        setColor(10);
        cout << " "
             << percent
             << "%\n";

        if(totalCalories >= target) {

            setColor(10);
            cout << "Status          : Target tercapai\n";
        }

        else {

            setColor(14);
            cout << "Status          : Target belum tercapai\n";
        }

        resetColor();
    }

    static void showWeeklyReport() {

        vector<ReportRecord> records =
        readHealthLogs();

        setColor(11);
        cout << "=== ";

        setColor(6);
        cout << "RIWAYAT 7 HARI TERAKHIR";

        setColor(11);
        cout << " ===\n\n";

        resetColor();

        if(records.empty()) {

            setColor(12);
            cout << "Belum ada data aktivitas tersimpan.\n";

            resetColor();

            return;
        }

        map<string, int> totalActivities;
        map<string, double> totalCalories;

        for(auto& rec : records) {

            totalActivities[rec.date]++;

            totalCalories[rec.date] +=
            rec.calories;
        }

        vector<string> dates;

        for(auto& pair : totalCalories) {

            dates.push_back(pair.first);
        }

        sort(
            dates.begin(),
            dates.end(),
            [](string a, string b) {

                return dateToNumber(a)
                     > dateToNumber(b);
            }
        );

        setColor(6);
        cout << left
             << setw(15) << "Tanggal"
             << setw(18) << "Total Aktivitas"
             << setw(15) << "Kalori"
             << "Grafik"
             << endl;

        setColor(11);
        cout << "---------------------------------------------------------------------\n";

        int count = 0;

        for(string date : dates) {

            if(count == 7) {

                break;
            }

            resetColor();

            cout << left
                 << setw(15) << date
                 << setw(18) << totalActivities[date]
                 << setw(15) << fixed
                 << setprecision(1)
                 << totalCalories[date];

            showBar(
                totalCalories[date]
            );

            cout << endl;

            count++;
        }

        resetColor();

        cout << "\nKeterangan: 1 tanda # mewakili sekitar 50 kcal.\n";
    }
};

#endif