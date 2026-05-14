#ifndef HEALTHACTIVITY_H
#define HEALTHACTIVITY_H

#include <iostream>

using namespace std;

class HealthActivity
{

protected:
    string startTime;
    string finishTime;

    string intensity;

public:
    HealthActivity(
        string s,
        string f,
        string i)
    {

        startTime = s;
        finishTime = f;

        intensity = i;
    }

    string getStartTime() const
    {

        return startTime;
    }

    string getFinishTime() const
    {

        return finishTime;
    }

    string getIntensity() const
    {

        return intensity;
    }

    int getDuration() const
    {

        int sh = stoi(
            startTime.substr(0, 2));

        int sm = stoi(
            startTime.substr(3, 2));

        int fh = stoi(
            finishTime.substr(0, 2));

        int fm = stoi(
            finishTime.substr(3, 2));

        int start =
            sh * 60 + sm;

        int finish =
            fh * 60 + fm;

        // =====================================
        // HANDLE CROSS MIDNIGHT
        // =====================================

        if (finish < start)
        {

            finish += 24 * 60;
        }

        return finish - start;
    }

    virtual double
    calculateBurnedCalories() const = 0;

    virtual string
    getActivityName() const = 0;

    virtual ~HealthActivity() {}
};

inline ostream &operator<<(
    ostream &os,
    const HealthActivity &act)
{

    os << "Activity        : "
       << act.getActivityName()
       << endl;

    os << "Start Time     : "
       << act.getStartTime()
       << endl;

    os << "Finish Time    : "
       << act.getFinishTime()
       << endl;

    os << "Duration       : "
       << act.getDuration()
       << " minutes"
       << endl;

    os << "Calories Burned: "
       << act.calculateBurnedCalories()
       << " kcal"
       << endl;

    return os;
}

#endif