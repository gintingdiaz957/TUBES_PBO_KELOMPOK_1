#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <windows.h>

#include "Warna.h"

using namespace std;

void clearScreen() {

    system("cls");
}

void pauseScreen() {

    setColor(10);
    cout << "\nTekan Enter Untuk Melanjutkan...";
    resetColor();

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    cin.get();
}

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

void loading() {

    setColor(10);
    cout << "Memuat";

    for(int i = 0; i < 3; i++) {

        cout << ".";
        Sleep(400);
    }

    cout << endl;

    resetColor();
}

#endif