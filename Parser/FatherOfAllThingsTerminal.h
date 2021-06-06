//
// Created by marwan_ashraf on 06-Jun-21.
//

#ifndef JAVA_COMPILER_FATHEROFALLTHINGSTERMINAL_H
#define JAVA_COMPILER_FATHEROFALLTHINGSTERMINAL_H

#include <string>
#include <utility>

using namespace std;

class FatherOfAllThingsTerminal {
protected:
    string name;
    bool isTerminalFlag = false;
public:
    explicit FatherOfAllThingsTerminal(string name) : name(std::move(name)) {}

    const string &getName() const {
        return name;
    }

    bool isThisMe(const string &testName) {
        return name == testName;
    }

    bool isTerminal() const {
        return isTerminalFlag;
    }
};

#endif //JAVA_COMPILER_FATHEROFALLTHINGSTERMINAL_H