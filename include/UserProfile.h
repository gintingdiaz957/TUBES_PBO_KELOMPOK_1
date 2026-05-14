#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <fstream>

#include "InvalidInputException.h"

using namespace std;

class UserProfile {

private:

    string name;

    double weight;
    double height;

    int age;

    string goal;

public:

    void setName(string n) {

        if(n.length() < 2) {

            throw InvalidInputException(
                "Invalid Name"
            );
        }

        name = n;
    }

    void setWeight(double w) {

        if(w < 20 || w > 300) {

            throw InvalidInputException(
                "Weight must be 20-300"
            );
        }

        weight = w;
    }

    void setHeight(double h) {

        if(h < 100 || h > 250) {

            throw InvalidInputException(
                "Height must be 100-250"
            );
        }

        height = h;
    }

    void setAge(int a) {

        if(a < 5 || a > 120) {

            throw InvalidInputException(
                "Age must be 5-120"
            );
        }

        age = a;
    }

    void setGoal(string g) {

        goal = g;
    }

    string getName() {

        return name;
    }

    double getWeight() {

        return weight;
    }

    double getHeight() {

        return height;
    }

    int getAge() {

        return age;
    }

    string getGoal() {

        return goal;
    }

    double getIdealWeight() {

        return
        (height - 100)
        - ((height - 100) * 0.1);
    }

    double getRecommendedCalories() {

        return 25 * weight;
    }

    // =====================================
    // SAVE PROFILE
    // =====================================

    void saveProfile() {

        ofstream file(
            "user_profile.dat",
            ios::binary
        );

        file.write(
            (char*)&weight,
            sizeof(weight)
        );

        file.write(
            (char*)&height,
            sizeof(height)
        );

        file.write(
            (char*)&age,
            sizeof(age)
        );

        int len =
        name.length();

        file.write(
            (char*)&len,
            sizeof(len)
        );

        file.write(
            name.c_str(),
            len
        );

        len =
        goal.length();

        file.write(
            (char*)&len,
            sizeof(len)
        );

        file.write(
            goal.c_str(),
            len
        );

        file.close();
    }

    // =====================================
    // LOAD PROFILE
    // =====================================

    bool loadProfile() {

        ifstream file(
            "user_profile.dat",
            ios::binary
        );

        if(!file) {

            return false;
        }

        file.read(
            (char*)&weight,
            sizeof(weight)
        );

        file.read(
            (char*)&height,
            sizeof(height)
        );

        file.read(
            (char*)&age,
            sizeof(age)
        );

        int len;

        file.read(
            (char*)&len,
            sizeof(len)
        );

        char* buffer =
        new char[len + 1];

        file.read(
            buffer,
            len
        );

        buffer[len] = '\0';

        name = buffer;

        delete[] buffer;

        file.read(
            (char*)&len,
            sizeof(len)
        );

        buffer =
        new char[len + 1];

        file.read(
            buffer,
            len
        );

        buffer[len] = '\0';

        goal = buffer;

        delete[] buffer;

        file.close();

        return true;
    }
};

#endif