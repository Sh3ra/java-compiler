//
// Created by marwan_ashraf on 06-Jun-21.
//

#include <utility>
#include <vector>
#include "FatherOfAllThingsTerminal.h"

class Terminal : public FatherOfAllThingsTerminal {
public:
    explicit Terminal(string newName) : FatherOfAllThingsTerminal(std::move(newName)) {
        isTerminalFlag = true;
    }
};

class NonTerminal : public FatherOfAllThingsTerminal {
private:
    vector<vector<FatherOfAllThingsTerminal>> productions;
    vector<pair<Terminal, vector<FatherOfAllThingsTerminal>>> first;
    vector<Terminal> follow;
    bool goesToEpsilon;

public:
    explicit NonTerminal(string newName) : FatherOfAllThingsTerminal(std::move(newName)) {
        goesToEpsilon = false;
        isTerminalFlag = false;
    }

    const vector<vector<FatherOfAllThingsTerminal>> &getProductions() const {
        return productions;
    }

    vector<pair<Terminal, vector<FatherOfAllThingsTerminal>>> getFirst() const {
        return first;
    }

    const vector<Terminal> &getFollow() const {
        return follow;
    }

    void setFirst(const vector<pair<Terminal, vector<FatherOfAllThingsTerminal>>> &setFirst) {
        first = setFirst;
    }

    void setFollow(const vector<Terminal> &setFollow) {
        follow = setFollow;
    }

    void addProduction(const vector<FatherOfAllThingsTerminal> &production) {
        productions.push_back(production);
    }
};
