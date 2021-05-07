//
// Created by maroa on 01-May-21.
//

#include "RegularDefinition.h"

string RegularDefinition::getName() {
    return name;
}

string RegularDefinition::getDefinition() {
    return definition;
}

RegularDefinition::RegularDefinition(string name, string definition) : name(move(name)), definition(move(definition)) {}