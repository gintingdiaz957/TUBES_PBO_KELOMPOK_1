#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <iostream>

#include "UserProfile.h"
#include "MenuView.h"
#include "InputValidator.h"
#include "Warna.h"

using namespace std;

class RegistrationForm {

public:

    static void registerUser(
        UserProfile& user
    ) {

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

        resetColor();

        name =
        InputValidator
        ::inputName(
            "Nama : "
        );

        weight =
        InputValidator
        ::inputDouble(
            "Berat Badan (20-300 kg): ",
            20,
            300,
            "Berat Badan Tidak Valid!"
        );

        height =
        InputValidator
        ::inputDouble(
            "Tinggi Badan (100-250 cm): ",
            100,
            250,
            "Tinggi Badan Tidak Valid!"
        );

        age =
        InputValidator
        ::inputInt(
            "Umur (5-120): ",
            5,
            120,
            "Umur Tidak Valid!"
        );

        goalChoice =
        MenuView
        ::showGoalMenu();

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

        setColor(10);
        cout << "\nProfil Berhasil Disimpan!\n\n";

        resetColor();
    }
};

#endif