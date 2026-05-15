#ifndef WARNA_H
#define WARNA_H

#include <windows.h>

// =========================================
// COLOR SYSTEM
// =========================================

static HANDLE hConsole =
GetStdHandle(STD_OUTPUT_HANDLE);

static void setColor(int color) {

    SetConsoleTextAttribute(
        hConsole,
        color
    );
}

static void resetColor() {

    setColor(15);
}

#endif