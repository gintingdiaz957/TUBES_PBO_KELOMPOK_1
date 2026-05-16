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
#include "include/caloriesTracker.h"
#include "include/HistoryManager.h"
#include "include/HealthAnalyzer.h"

#include "include/Warna.h"

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

    setColor(10);
    cout << "\nTekan Enter Untuk Melanjutkan...";
    setColor(15);

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

    setColor(11);
    cout << "========================================================\n";

    setColor(11);
    cout << "+";
    
    setColor(6);
    cout << "                FITTRACK PRO SYSTEM                   ";

    setColor(11);
    cout << "+\n";

    setColor(11);
    cout << "========================================================\n\n";

    resetColor();
}

// =========================================
// LOADING
// =========================================

void loading() {

    setColor(10);
    cout << "Memuat";

    for(int i=0;i<3;i++) {

        setColor(10);
        cout << ".";
        
        Sleep(400);
        setColor(15);
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
   CaloriesTracker caloriesTracker;

    if(user.loadProfile()) {

        clearScreen();

        showTitle();

        setColor(10);
        cout << "Selamat Datang Kembali, "
             << user.getName()
             << "!\n\n";
        setColor(15);
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

        setColor(11);
        cout << "=== ";

        setColor(6);
        cout << "REGISTRASI PENGGUNA";

        setColor(11);
        cout << " ===\n\n";

        setColor(8);
        cout << "Nama : ";

        getline(cin,name);
        setColor(15);

        do {

            setColor(14);
            cout << "Berat Badan (20-300 kg): ";

            cin >> weight;

            if(weight < 20 || weight > 300) {

                setColor(12);
                cout << "Berat Badan Tidak Valid!\n\n";
            }

        } while(weight < 20 || weight > 300);

        do {

            setColor(14);
            cout << "Tinggi Badan (100-250 cm): ";

            cin >> height;

            if(height < 100 || height > 250) {

                setColor(12);
                cout << "Tinggi Badan Tidak Valid!\n\n";
            }

        } while(height < 100 || height > 250);

        do {

            setColor(14);
            cout << "Umur (5-120): ";

            cin >> age;

            if(age < 5 || age > 120) {

                setColor(12);
                cout << "Umur Tidak Valid!\n\n";
            }

        } while(age < 5 || age > 120);

        setColor(15);

        setColor(11);
        cout << "\n===";
        
        setColor(6);
        cout << " PILIH TUJUAN ";
        
        setColor(11);
        cout << "===\n\n";

        setColor(6);
        cout << "1. Menurunkan Berat Badan\n";
        cout << "2. Menambah Massa Otot\n";
        cout << "3. Menjaga Pola Hidup Sehat\n\n";

        setColor(6);
        cout << "Pilih : ";

        setColor(8);
        cin >> goalChoice;

        user.setName(name);

        user.setWeight(weight);

        user.setHeight(height);

        user.setAge(age);

        switch(goalChoice) {

            case 1:

                user.setGoal(
                    "Menurunkan Berat Badan"
                );

                break;

            case 2:

                user.setGoal(
                    "Menambah Massa Otot"
                );

                break;

            default:

                user.setGoal(
                    "Menjaga Pola Hidup Sehat"
                );
        }

        user.saveProfile();

        clearScreen();

        showTitle();

        setColor(10);
        cout << "Profil Berhasil Disimpan!\n\n";
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

        setColor(6);
        cout << "RINGKASAN PROFIL\n";

        setColor(11); 
        cout << "========================================================\n\n";
        setColor(15);

        setColor(8);
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
             << user
                .getRecommendedCalories()
             << " kcal\n";

        setColor(11);
        cout << "\n========================================================\n";

        setColor(6);
        cout << "\nMENU UTAMA\n\n";

        cout << "[1] Tambah Aktivitas\n";
        cout << "[2] Lihat Riwayat\n";
        cout << "[3] Analisis Kesehatan\n";
        cout << "[4] Ringkasan Kalori\n";
        cout << "[0] Keluar\n\n";

        cout << "Pilih Menu : ";

        setColor(15);
        cin >> choice;

        // =====================================
        // SWITCH MENU
        // =====================================

        switch(choice) {

            case 1: {

                clearScreen();

                showTitle();

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

                setColor(8);
                cout << "Tanggal : ";

                cin >> date;
                setColor(6);

                cout << "\n1. Lari\n";
                cout << "2. Bersepeda\n";
                cout << "3. Latihan Beban\n";
                cout << "4. Tidur\n\n";

                setColor(6);
                cout << "Pilih Aktivitas : ";

                cin >> type;

                setColor(8);
                cout << "\nJam Mulai (HH:MM): ";

                cin >> start;

                cout << "Jam Selesai (HH:MM): ";

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

                setColor(10);
                cout << "\nAktivitas Berhasil Disimpan!\n\n";
                
                setColor(14);
                cout << "Kalori Terbakar : "
                     << calories
                     << " kcal\n";

                pauseScreen();
                setColor(15);

                break;
            }

            case 2:

                clearScreen();

                showTitle();

                manager.showHistoryFromFile();

                pauseScreen();

                break;

            case 3: {

                clearScreen();

                showTitle();

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

                pauseScreen();

                setColor(15);
                break;
            }

            case 4: {

                clearScreen();

                showTitle();

                CaloriesTracker caloriesTracker;

                caloriesTracker
                .showSummary();

                pauseScreen();

                setColor(15);
                break;
            }

            case 0:

                clearScreen();

                showTitle();

                setColor(10);
                cout << "Terima Kasih Telah Menggunakan FITTRACK PRO\n\n";

                setColor(15);
                break;

            default:

                setColor(12);
                cout << "\nMenu Tidak Valid!\n";

                setColor(15);  
                pauseScreen();
        }

    } while(choice != 0);

    return 0;
}