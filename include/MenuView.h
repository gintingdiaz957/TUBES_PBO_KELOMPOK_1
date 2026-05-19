#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <iostream>

#include "Warna.h"
#include "InputValidator.h"

using namespace std;

class MenuView {

public:

    static int showMainMenu() {

        setColor(11);
        cout << "\n========================================================\n";

        setColor(6);
        cout << "\nMENU UTAMA\n\n";

        cout << "[1] Tambah Aktivitas\n";
        cout << "[2] Lihat Riwayat\n";
        cout << "[3] Analisis Kesehatan\n";
        cout << "[4] Ringkasan Kalori\n";
        cout << "[5] Target Kesehatan\n";
        cout << "[0] Keluar\n\n";

        resetColor();

        return InputValidator
        ::inputInt(
            "Pilih Menu : ",
            0,
            5,
            "Menu Tidak Valid!"
        );
    }

    static int showActivityMenu() {

        setColor(6);
        cout << "\n1. Lari\n";
        cout << "2. Bersepeda\n";
        cout << "3. Latihan Beban\n";
        cout << "4. Tidur\n\n";

        resetColor();

        return InputValidator
        ::inputInt(
            "Pilih Aktivitas : ",
            1,
            4,
            "Pilihan aktivitas tidak valid!"
        );
    }

    static int showGoalMenu() {

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

        resetColor();

        return InputValidator
        ::inputInt(
            "Pilih : ",
            1,
            3,
            "Pilihan tujuan tidak valid!"
        );
    }
};

#endif