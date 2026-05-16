#ifndef HEALTHACTIVITY_H
#define HEALTHACTIVITY_H

#include <iostream>

#include "Warna.h"

using namespace std;

class HealthActivity {

protected:

    string startTime;
    string finishTime;
    string intensity;

public:

    HealthActivity(
        string s,
        string f,
        string i
    ) {

        startTime = s;
        finishTime = f;
        intensity = i;
    }

    string getStartTime() const {

        return startTime;
    }

    string getFinishTime() const {

        return finishTime;
    }

    string getIntensity() const {

        return intensity;
    }

    int getDuration() const {

        int sh = stoi(startTime.substr(0, 2));
        int sm = stoi(startTime.substr(3, 2));

        int fh = stoi(finishTime.substr(0, 2));
        int fm = stoi(finishTime.substr(3, 2));

        int start = sh * 60 + sm;
        int finish = fh * 60 + fm;

        if(finish < start) {

            finish += 24 * 60;
        }

        return finish - start;
    }

    virtual double calculateBurnedCalories() const = 0;

    virtual string getActivityName() const = 0;

    virtual string getActivityNote() const {

        return "-";
    }

    virtual ~HealthActivity() {}
};

inline ostream& operator<<(
    ostream& os,
    const HealthActivity& act
) {

    setColor(6);
    os << "Aktivitas      : ";

    resetColor();
    os << act.getActivityName() << endl;

    setColor(6);
    os << "Jam Mulai      : ";

    resetColor();
    os << act.getStartTime() << endl;

    setColor(6);
    os << "Jam Selesai    : ";

    resetColor();
    os << act.getFinishTime() << endl;

    setColor(6);
    os << "Durasi         : ";

    setColor(10);
    os << act.getDuration();

    resetColor();
    os << " menit" << endl;

    setColor(6);
    os << "Kalori Terbakar: ";

    setColor(10);
    os << act.calculateBurnedCalories();

    resetColor();
    os << " kcal" << endl;

    if(act.getActivityNote() != "-") {

        setColor(6);
        os << "Kualitas Tidur : ";

        setColor(10);
        os << act.getActivityNote() << endl;
    }

    resetColor();

    return os;
}

#endif