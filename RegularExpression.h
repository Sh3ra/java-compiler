//
// Created by maroa on 01-May-21.
//

#ifndef JAVA_COMPILER_REGULAREXPRESSION_H
#define JAVA_COMPILER_REGULAREXPRESSION_H

#include <string>

using namespace std;

class RegularExpression {
private:
    string name;
    string expression;
public:
    RegularExpression(string name, string definition);

    string getName();

    void setName(const string &newName);

    string getExpression();

    void setExpression(const string &newExpression);
};


#endif //JAVA_COMPILER_REGULAREXPRESSION_H
