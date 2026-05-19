#include <iostream>

#include "include/Screen.h"

#include "include/UserProfile.h"
#include "include/HistoryManager.h"
#include "include/CaloriesTracker.h"
#include "include/GoalView.h"

#include "include/MenuView.h"
#include "include/ProfileView.h"
#include "include/RegistrationForm.h"
#include "include/ActivityForm.h"
#include "include/ReportFeatures.h"

#include "include/Warna.h"

using namespace std;

int showExtendedMainMenu() {

    setColor(11);
    cout << "\n========================================================\n";

    setColor(6);
    cout << "\nMENU UTAMA\n\n";

    cout << "[1] Tambah Aktivitas\n";
    cout << "[2] Lihat Riwayat\n";
    cout << "[3] Analisis Kesehatan\n";
    cout << "[4] Ringkasan Kalori\n";
    cout << "[5] Target Kesehatan\n";
    cout << "[6] Progress Target Harian\n";
    cout << "[7] Riwayat 7 Hari Terakhir\n";
    cout << "[0] Keluar\n\n";

    resetColor();

    return InputValidator
    ::inputInt(
        "Pilih Menu : ",
        0,
        7,
        "Menu Tidak Valid!"
    );
}

int main() {

    clearScreen();

    showTitle();

    loading();

    UserProfile user;
    HistoryManager manager;

    if(user.loadProfile()) {

        clearScreen();

        showTitle();

        setColor(10);
        cout << "Selamat Datang Kembali, "
             << user.getName()
             << "!\n\n";

        resetColor();
    }

    else {

        clearScreen();

        showTitle();

        RegistrationForm
        ::registerUser(user);

        pauseScreen();
    }

    int choice;

    do {

        clearScreen();

        showTitle();

        ProfileView
        ::showProfileSummary(user);

        choice =
        showExtendedMainMenu();

        switch(choice) {

            case 1:

                clearScreen();

                showTitle();

                ActivityForm
                ::addActivity(
                    user,
                    manager
                );

                pauseScreen();

                break;

            case 2:

                clearScreen();

                showTitle();

                manager
                .showHistoryFromFile();

                pauseScreen();

                break;

            case 3:

                clearScreen();

                showTitle();

                ProfileView
                ::showHealthAnalysis(user);

                pauseScreen();

                break;

            case 4: {

                clearScreen();

                showTitle();

                CaloriesTracker caloriesTracker;

                caloriesTracker
                .showSummary();

                pauseScreen();

                break;
            }

            case 5:

                clearScreen();

                showTitle();

                GoalView
                ::showGoals(
                    user,
                    manager
                );

                pauseScreen();

                break;

            case 6:

                clearScreen();

                showTitle();

                ReportFeatures
                ::showDailyProgress();

                pauseScreen();

                break;

            case 7:

                clearScreen();

                showTitle();

                ReportFeatures
                ::showWeeklyReport();

                pauseScreen();

                break;

            case 0:

                clearScreen();

                showTitle();

                setColor(10);
                cout << "Terima Kasih Telah Menggunakan FITTRACK PRO\n\n";

                resetColor();

                break;
        }

    } while(choice != 0);

    return 0;
}