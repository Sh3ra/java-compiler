//
// Created by marwan_ashraf on 06-Jun-21.
//

#include <iostream>
#include "Facade.h"
#include "InputReader.h"

void Facade::addNonTerminal(NonTerminal *nonTerminal) {
    nonTerminals.push_back(nonTerminal);
}

void Facade::addTerminal(Terminal *terminal) {
    terminals.push_back(terminal);
}

const vector<NonTerminal *> &Facade::getNonTerminals() const {
    return nonTerminals;
}

const vector<Terminal *> &Facade::getTerminals() const {
    return terminals;
}

void Facade::readInput() {
    InputReader reader(this);
    reader.readInput();
}

Terminal *Facade::findTerminal(const string &terminalName) const {
    for (Terminal *terminal:this->getTerminals()) {
        if (terminal->isThisMe(terminalName))
            return terminal;
    }
    return nullptr;
}

NonTerminal *Facade::findNonTerminal(const string &nonTerminalName) const {
    for (NonTerminal *nonTerminal:this->getNonTerminals()) {
        if (nonTerminal->isThisMe(nonTerminalName))
            return nonTerminal;
    }
    return nullptr;
}

int main() {
    /*Facade facade;
    facade.readInput();
    NonTerminal *nonTerminal = facade.getNonTerminals()[0];
    vector<vector<FatherOfAllThingsTerminal>> productions = nonTerminal->getProductions();
    string name = productions[0][0].getName();
    if (productions[0][0].isTerminal()) {
        Terminal *terminal = facade.findTerminal(name);
    } else {
        NonTerminal *nonTerminal2 = facade.findNonTerminal(name);
        cout << name;
    }*/
}