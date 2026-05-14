#ifndef INVALIDINPUTEXCEPTION_H
#define INVALIDINPUTEXCEPTION_H

#include <iostream>

using namespace std;

class InvalidInputException {

private:

    string message;

public:

    InvalidInputException(
        string msg
    ) {

        message = msg;
    }

    string getMessage() {

        return message;
    }
};

#endif