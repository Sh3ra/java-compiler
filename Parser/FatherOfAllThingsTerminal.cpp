//
// Created by marwan_ashraf on 06-Jun-21.
//

#include <utility>
#include <vector>
#include <bits/stdc++.h>
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
    bool goesToEpsilonFlag;
    map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>> predictive_table_row;
public:
    explicit NonTerminal(string newName) : FatherOfAllThingsTerminal(std::move(newName)) {
        goesToEpsilonFlag = false;
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

    void addFirst(const pair<Terminal, vector<FatherOfAllThingsTerminal>>& newFirst) {
        first.push_back(newFirst);
    }

    void addFollow(const Terminal &newFollow) {
        follow.push_back(newFollow);
    }

    void addProduction(const vector<FatherOfAllThingsTerminal> &production) {
        productions.push_back(production);
    }

    const map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>> &getPredictiveTableRow() const {
        return predictive_table_row;
    }

    void setPredictiveTableRow(
            const map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>> &predictiveTableRow) {
        predictive_table_row = predictiveTableRow;
    }

    void
    addToPredictiveTable(pair<bool, bool> sync_and_epsilon, const vector<FatherOfAllThingsTerminal> &addedProductions,
                         const string &t) {
        predictive_table_row[t] = {sync_and_epsilon, addedProductions};
    }

    bool goesToEpsilon() const {
        return goesToEpsilonFlag;
    }

    void setGoesToEpsilonFlag(bool goesToEpsilon) {
        NonTerminal::goesToEpsilonFlag = goesToEpsilon;
    }
};
