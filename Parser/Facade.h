//
// Created by marwan_ashraf on 06-Jun-21.
//

#ifndef JAVA_COMPILER_FACADE_H
#define JAVA_COMPILER_FACADE_H

#include "FatherOfAllThingsTerminal.cpp"

class Facade {
private:
    vector<NonTerminal *> nonTerminals;
    vector<Terminal *> terminals;

public:
    void addNonTerminal(NonTerminal *nonTerminal);

    void addTerminal(Terminal *terminal);

    const vector<NonTerminal *> &getNonTerminals() const;

    const vector<Terminal *> &getTerminals() const;

    void setNonTerminals(const vector<NonTerminal *> &newNonTerminals);

    void setTerminals(const vector<Terminal *> &newTerminals);

    void readAndProcessInput();

    Terminal *findTerminal(const string &terminalName) const;

    NonTerminal *findNonTerminal(const string &nonTerminalName) const;
};

#endif //JAVA_COMPILER_FACADE_H