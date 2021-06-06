//
// Created by maroa on 01-May-21.
//

#include "RegularExpression.h"

RegularExpression::RegularExpression(string name, string expression) : name(move(name)), expression(move(expression)) {}

string RegularExpression::getName() {
    return name;
}

string RegularExpression::getExpression() {
    return expression;
}

void RegularExpression::setExpression(const string &newExpression) {
    RegularExpression::expression = newExpression;
}

void RegularExpression::setName(const string &newName) {
    RegularExpression::name = newName;
}
