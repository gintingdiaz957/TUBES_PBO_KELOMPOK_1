#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <iostream>
#include <iomanip>

#include "UserProfile.h"
#include "HealthAnalyzer.h"
#include "Warna.h"

using namespace std;

class ProfileView {

public:

    static void showProfileSummary(
        UserProfile& user
    ) {

        double bmi =
        HealthAnalyzer
        ::calculateBMI(
            user.getWeight(),
            user.getHeight()
        );

        setColor(6);
        cout << "RINGKASAN PROFIL\n";

        setColor(11);
        cout << "========================================================\n\n";

        resetColor();

        cout << "Nama                : "
             << user.getName()
             << endl;

        cout << "Berat Badan         : "
             << user.getWeight()
             << " kg\n";

        cout << "Tinggi Badan        : "
             << user.getHeight()
             << " cm\n";

        cout << "Umur                : "
             << user.getAge()
             << endl;

        cout << "Tujuan              : "
             << user.getGoal()
             << endl;

        cout << "BMI                 : "
             << fixed
             << setprecision(1)
             << bmi
             << " ("
             << HealthAnalyzer
                ::getBMICategory(bmi)
             << ")\n";

        cout << "Berat Badan Ideal   : "
             << user.getIdealWeight()
             << " kg\n";

        cout << "Kebutuhan Kalori    : "
             << user.getRecommendedCalories()
             << " kcal\n";
    }

    static void showHealthAnalysis(
        UserProfile& user
    ) {

        double bmi =
        HealthAnalyzer
        ::calculateBMI(
            user.getWeight(),
            user.getHeight()
        );

        setColor(11);
        cout << "=== ";

        setColor(6);
        cout << "ANALISIS KESEHATAN";

        setColor(11);
        cout << " ===\n\n";

        setColor(8);
        cout << "Kategori BMI : "
             << HealthAnalyzer
                ::getBMICategory(bmi)
             << endl;

        setColor(6);
        cout << "\nRekomendasi:\n\n";

        if(bmi > 25) {

            cout << "- Perbanyak Olahraga Kardio\n";
            cout << "- Kurangi Asupan Kalori\n";
        }

        else if(bmi < 18.5) {

            cout << "- Tingkatkan Asupan Nutrisi\n";
            cout << "- Coba Latihan Kekuatan\n";
        }

        else {

            cout << "- Pertahankan Pola Hidup Sehat\n";
        }

        resetColor();
    }
};

#endif