//
// Created by marwan_ashraf on 06-Jun-21.
//

#include <iostream>
#include "Facade.h"
#include "InputReader.h"
#include "FirstFollowFinder.h"

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

void Facade::readAndProcessInput() {
    InputReader reader(this);
    reader.readInput();
    FirstFollowFinder finder(this);
    finder.findFirst();
    finder.findFollow();
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

void Facade::setNonTerminals(const vector<NonTerminal *> &newNonTerminals) {
    Facade::nonTerminals = newNonTerminals;
}

/*void Facade::setTerminals(const vector<Terminal *> &newTerminals) {
    Facade::terminals = newTerminals;
}*/

int main() {
    Facade facade;
    facade.readAndProcessInput();
    facade.findNonTerminal("FACTOR")->getFollowTerminals();
    return 0;
}