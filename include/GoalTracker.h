#ifndef GOALTRACKER_H
#define GOALTRACKER_H

#include <iostream>
#include <iomanip>

#include "Warna.h"

using namespace std;

template <typename T>
class GoalTracker {

private:

    string goalName;

    T target;

    T current;

    string unit;

public:

    GoalTracker(
        string name,
        T targetValue,
        T currentValue,
        string u
    ) {

        goalName = name;

        target = targetValue;

        current = currentValue;

        unit = u;
    }

    void addProgress(
        T value
    ) {

        current =
        current + value;
    }

    bool isAchieved() const {

        return current >= target;
    }

    T getRemaining() const {

        if(current >= target) {

            return 0;
        }

        return target - current;
    }

    double getProgressPercent() const {

        if(target == 0) {

            return 0;
        }

        return
        (static_cast<double>(current)
        /
        static_cast<double>(target))
        * 100;
    }

    void showGoal() const {

        setColor(6);
        cout << "Target          : ";

        resetColor();
        cout << goalName << endl;

        setColor(6);
        cout << "Nilai Sekarang  : ";

        setColor(10);
        cout << current
             << " "
             << unit
             << endl;

        setColor(6);
        cout << "Nilai Target    : ";

        setColor(10);
        cout << target
             << " "
             << unit
             << endl;

        setColor(6);
        cout << "Progress        : ";

        setColor(10);
        cout << fixed
             << setprecision(1)
             << getProgressPercent()
             << "%\n";

        setColor(6);
        cout << "Sisa Target     : ";

        setColor(10);
        cout << getRemaining()
             << " "
             << unit
             << endl;

        if(isAchieved()) {

            setColor(10);
            cout << "Status          : Target tercapai\n";
        }

        else {

            setColor(14);
            cout << "Status          : Target belum tercapai\n";
        }

        resetColor();
    }
};

#endif