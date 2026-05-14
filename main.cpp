#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <windows.h>

#include "include/Running.h"
#include "include/Cycling.h"
#include "include/Strength.h"
#include "include/Sleep.h"

#include "include/UserProfile.h"
#include "include/CaloriesTracker.h"
#include "include/HistoryManager.h"
#include "include/HealthAnalyzer.h"

using namespace std;

// =========================================
// CLEAR SCREEN
// =========================================

void clearScreen() {

    system("cls");
}

// =========================================
// PAUSE SCREEN
// =========================================

void pauseScreen() {

    cout << "\nPress Enter To Continue...";

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    cin.get();
}

// =========================================
// TITLE
// =========================================

void showTitle() {

    cout << "========================================================\n";
    cout << "                FITTRACK PRO SYSTEM\n";
    cout << "========================================================\n\n";
}

// =========================================
// LOADING
// =========================================

void loading() {

    cout << "Loading";

    for(int i=0;i<3;i++) {

        cout << ".";

        Sleep(400);
    }

    cout << endl;
}

// =========================================
// MAIN
// =========================================

int main() {

    clearScreen();

    showTitle();

    loading();

    UserProfile user;


    HistoryManager manager;

    // =====================================
    // LOAD PROFILE
    // =====================================
    CaloriesTracker caloriesTracker(
    manager.getHistory()
);

    if(user.loadProfile()) {

        clearScreen();

        showTitle();

        cout << "Welcome Back, "
             << user.getName()
             << "!\n\n";
    }

    // =====================================
    // REGISTER
    // =====================================

    else {

        string name;

        double weight;
        double height;

        int age;

        int goalChoice;

        cout << "=== USER REGISTRATION ===\n\n";

        cout << "Input Name : ";

        getline(cin,name);

        do {

            cout << "Input Weight (20-300 kg): ";

            cin >> weight;

            if(weight < 20 || weight > 300) {

                cout << "Invalid Weight!\n\n";
            }

        } while(weight < 20 || weight > 300);

        do {

            cout << "Input Height (100-250 cm): ";

            cin >> height;

            if(height < 100 || height > 250) {

                cout << "Invalid Height!\n\n";
            }

        } while(height < 100 || height > 250);

        do {

            cout << "Input Age (5-120): ";

            cin >> age;

            if(age < 5 || age > 120) {

                cout << "Invalid Age!\n\n";
            }

        } while(age < 5 || age > 120);

        cout << "\n=== CHOOSE GOAL ===\n\n";

        cout << "1. Weight Loss\n";
        cout << "2. Muscle Gain\n";
        cout << "3. Healthy Lifestyle\n\n";

        cout << "Choose : ";

        cin >> goalChoice;

        user.setName(name);

        user.setWeight(weight);

        user.setHeight(height);

        user.setAge(age);

        switch(goalChoice) {

            case 1:

                user.setGoal(
                    "Weight Loss"
                );

                break;

            case 2:

                user.setGoal(
                    "Muscle Gain"
                );

                break;

            default:

                user.setGoal(
                    "Healthy Lifestyle"
                );
        }

        user.saveProfile();

        clearScreen();

        showTitle();

        cout << "Profile Saved Successfully!\n\n";
    }

    // =====================================
    // MENU
    // =====================================

    int choice;

    do {

        double bmi =
        HealthAnalyzer
        ::calculateBMI(

            user.getWeight(),
            user.getHeight()
        );

        clearScreen();

        showTitle();

        cout << "PROFILE SUMMARY\n";

        cout << "========================================================\n\n";

        cout << "Name                : "
             << user.getName()
             << endl;

        cout << "Weight              : "
             << user.getWeight()
             << " kg\n";

        cout << "Height              : "
             << user.getHeight()
             << " cm\n";

        cout << "Age                 : "
             << user.getAge()
             << endl;

        cout << "Goal                : "
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

        cout << "Ideal Weight        : "
             << user.getIdealWeight()
             << " kg\n";

        cout << "Daily Calories Need : "
             << user
                .getRecommendedCalories()
             << " kcal\n";

        cout << "\n========================================================\n";

        cout << "\nMAIN MENU\n\n";

        cout << "[1] Add Activity\n";
        cout << "[2] Show History\n";
        cout << "[3] Health Analysis\n";
        cout << "[4] Calories Summary\n";
        cout << "[0] Exit\n\n";

        cout << "Choose Menu : ";

        cin >> choice;

        // =====================================
        // SWITCH MENU
        // =====================================

        switch(choice) {

            // =================================
            // ADD ACTIVITY
            // =================================

            case 1: {

                clearScreen();

                showTitle();

                string date;

                string start;
                string finish;

                int type;

                cout << "=== ADD ACTIVITY ===\n\n";

                cout << "Input Date : ";

                cin >> date;

                cout << "\n1. Running\n";
                cout << "2. Cycling\n";
                cout << "3. Strength\n";
                cout << "4. Sleep\n\n";

                cout << "Choose Activity : ";

                cin >> type;

                cout << "\nInput Start Time (HH:MM): ";

                cin >> start;

                cout << "Input Finish Time (HH:MM): ";

                cin >> finish;

                HealthActivity* activity;

                switch(type) {

                    case 1:

                        activity =
                        new Running(

                            start,
                            finish,
                            "High",
                            user.getWeight()
                        );

                        break;

                    case 2:

                        activity =
                        new Cycling(

                            start,
                            finish,
                            "Medium",
                            user.getWeight()
                        );

                        break;

                    case 3:

                        activity =
                        new Strength(

                            start,
                            finish,
                            "High",
                            user.getWeight()
                        );

                        break;

                    default:

                        activity =
                        new SleepActivity(

                            start,
                            finish,
                            "Low",
                            8
                        );
                }

                manager.addActivity(

                    date,
                    activity
                );

                double calories =
                activity
                ->calculateBurnedCalories();

                    calories;


                manager.saveToFile();

                cout << "\nActivity Saved Successfully!\n\n";

                cout << "Calories Burned : "
                     << calories
                     << " kcal\n";

                pauseScreen();

                break;
            }

            // =================================
            // SHOW HISTORY
            // =================================

            case 2:

                clearScreen();

                showTitle();

                manager.showHistory();

                pauseScreen();

                break;

            // =================================
            // ANALYSIS
            // =================================

            case 3: {

                clearScreen();

                showTitle();

                double bmi =
                HealthAnalyzer
                ::calculateBMI(

                    user.getWeight(),
                    user.getHeight()
                );

                cout << "=== HEALTH ANALYSIS ===\n\n";

                cout << "BMI Category : "
                     << HealthAnalyzer
                        ::getBMICategory(bmi)
                     << endl;

                cout << "\nRecommendation:\n\n";

                if(bmi > 25) {

                    cout << "- Try More Cardio Exercise\n";

                    cout << "- Reduce Calories Intake\n";
                }

                else if(bmi < 18.5) {

                    cout << "- Increase Nutrition Intake\n";

                    cout << "- Try Strength Training\n";
                }

                else {

                    cout << "- Keep Your Healthy Lifestyle\n";
                }

                pauseScreen();

                break;
            }

            // =================================
            // Calories Summary
            // =================================

            case 4: {

    clearScreen();

    showTitle();

    caloriesTracker
    .showSummary();

    pauseScreen();

    break;
}

            // =================================
            // EXIT
            // =================================

            case 0:

                clearScreen();

                showTitle();

                cout << "Thank You For Using FITTRACK PRO\n\n";

                break;

            // =================================
            // INVALID
            // =================================

            default:

                cout << "\nInvalid Menu!\n";

                pauseScreen();
        }

    } while(choice != 0);

    return 0;
}