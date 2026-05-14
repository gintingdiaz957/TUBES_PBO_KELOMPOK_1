#ifndef GOALTRACKER_H
#define GOALTRACKER_H

template <typename T>

class GoalTracker {

private:

    T target;
    T current;

public:

    GoalTracker(T t) {

        target = t;
        current = 0;
    }

    void addProgress(T value) {

        current += value;
    }

    T getCurrent() {

        return current;
    }

    T getTarget() {

        return target;
    }

    double getPercentage() {

        return (double)
               current
               / target
               * 100;
    }
};

#endif