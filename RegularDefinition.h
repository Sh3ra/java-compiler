//
// Created by maroa on 30-Apr-21.
//

#ifndef JAVA_COMPILER_REGULARDEFINITION_H
#define JAVA_COMPILER_REGULARDEFINITION_H

#include <string>

using namespace std;

class RegularDefinition {
private:
    string name;
    string definition;
public:
    RegularDefinition(string name, string definition);

    string getName();

    string getDefinition();
};

#endif //JAVA_COMPILER_REGULARDEFINITION_H