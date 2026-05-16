#include <iostream>

#include "include/Screen.h"

#include "include/UserProfile.h"
#include "include/HistoryManager.h"
#include "include/CaloriesTracker.h"

#include "include/MenuView.h"
#include "include/ProfileView.h"
#include "include/RegistrationForm.h"
#include "include/ActivityForm.h"

#include "include/Warna.h"

using namespace std;

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
        MenuView
        ::showMainMenu();

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