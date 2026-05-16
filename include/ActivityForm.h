#ifndef ACTIVITYFORM_H
#define ACTIVITYFORM_H

#include <iostream>
#include <iomanip>

#include "Running.h"
#include "Cycling.h"
#include "Strength.h"
#include "Sleep.h"

#include "UserProfile.h"
#include "HistoryManager.h"
#include "MenuView.h"
#include "InputValidator.h"
#include "Warna.h"

using namespace std;

class ActivityForm {

private:

    static HealthActivity* createActivity(
        int type,
        string start,
        string finish,
        UserProfile& user
    ) {

        switch(type) {

            case 1:
                return new Running(
                    start,
                    finish,
                    "High",
                    user.getWeight()
                );

            case 2:
                return new Cycling(
                    start,
                    finish,
                    "Medium",
                    user.getWeight()
                );

            case 3:
                return new Strength(
                    start,
                    finish,
                    "High",
                    user.getWeight()
                );

            default:
                return new SleepActivity(
                    start,
                    finish,
                    "Low",
                    0,
                    user.getAge()
                );
        }
    }

    static void showSleepResult(
        int type,
        HealthActivity* activity
    ) {

        if(type != 4) {

            return;
        }

        SleepActivity* sleepActivity =
        static_cast<SleepActivity*>(activity);

        setColor(14);
        cout << "Durasi Tidur    : ";

        setColor(10);
        cout << fixed
             << setprecision(1)
             << sleepActivity->getSleepHours()
             << " jam\n";

        setColor(14);
        cout << "Kualitas Tidur  : ";

        setColor(10);
        cout << sleepActivity->getSleepQuality()
             << "\n";

        setColor(14);
        cout << "Rekomendasi     : ";

        setColor(10);
        cout << sleepActivity
                ->getRecommendedSleepRange()
             << "\n";

        resetColor();
    }

public:

    static void addActivity(
        UserProfile& user,
        HistoryManager& manager
    ) {

        string date;
        string start;
        string finish;

        int type;

        setColor(11);
        cout << "=== ";

        setColor(6);
        cout << "TAMBAH AKTIVITAS";

        setColor(11);
        cout << " ===\n\n";

        resetColor();

        date =
        InputValidator
        ::inputDate();

        type =
        MenuView
        ::showActivityMenu();

        start =
        InputValidator
        ::inputTime(
            "\nJam Mulai (HH:MM): ",
            "Jam mulai tidak valid! Contoh benar: 08:30"
        );

        finish =
        InputValidator
        ::inputTime(
            "Jam Selesai (HH:MM): ",
            "Jam selesai tidak valid! Contoh benar: 17:45"
        );

        HealthActivity* activity =
        createActivity(
            type,
            start,
            finish,
            user
        );

        manager.addActivity(
            date,
            activity
        );

        double calories =
        activity
        ->calculateBurnedCalories();

        manager.saveToFile();

        setColor(10);
        cout << "\nAktivitas Berhasil Disimpan!\n\n";

        setColor(14);
        cout << "Kalori Terbakar : ";

        setColor(10);
        cout << calories
             << " kcal\n";

        showSleepResult(
            type,
            activity
        );

        resetColor();
    }
};

#endif