//
// Created by marwan_ashraf on 07-Jun-21.
//

#include "FirstFollowFinder.h"

void FirstFollowFinder::findFirst() {
    vector<NonTerminal *> nonTerminals = facade->getNonTerminals();
    for (int i = (int) nonTerminals.size() - 1; i >= 0; i--) {
        vector<vector<FatherOfAllThingsTerminal>> productions = nonTerminals[i]->getProductions();
        for (const auto &production:productions) {
            if (production[0].isTerminal()) {
                pair<Terminal, vector<FatherOfAllThingsTerminal>> newFirst(
                        *facade->findTerminal(production[0].getName()), production);
                nonTerminals[i]->addFirst(newFirst);
            } else {
                for (const auto &first: facade->findNonTerminal(production[0].getName())->getFirst()) {
                    pair<Terminal, vector<FatherOfAllThingsTerminal>> newFirst(first.first, production);
                    nonTerminals[i]->addFirst(newFirst);
                }
            }
        }
    }
    facade->setNonTerminals(nonTerminals);
}

void FirstFollowFinder::findFollow() {
    vector<NonTerminal *> nonTerminals = facade->getNonTerminals();
    nonTerminals[0]->addFollowName(facade->findTerminal("$")->getName());
    for (auto nonTerminal:nonTerminals) {
        const string &nonTerminalName = nonTerminal->getName();
        for (auto nonTerminalSearch:nonTerminals) {
            const vector<vector<FatherOfAllThingsTerminal>> &productions = nonTerminalSearch->getProductions();
            for (auto production:productions) {
                for (size_t i = 0; i < production.size(); i++) {
                    if (production[i].isThisMe(nonTerminalName)) {
                        int j;
                        for (j = 1; j < production.size() - i; j++) {
                            if (production[i + j].isTerminal()) {
                                nonTerminal->addFollowName(
                                        facade->findTerminal(production[i + j].getName())->getName());
                                break;
                            } else {
                                NonTerminal follower = *facade->findNonTerminal(production[i + j].getName());
                                for (auto firstOfFollower:follower.getFirst()) {
                                    if (!firstOfFollower.first.isThisMe("Epsilon")) {
                                        nonTerminal->addFollowName(firstOfFollower.first.getName());
                                    }
                                }
                                if (!follower.goesToEpsilon()) {
                                    break;
                                }
                            }
                        }
                        if (i + j == production.size()) {
                            nonTerminal->addFollowDependencyName(nonTerminalSearch->getName());
                        }
                    }
                }
            }
        }
    }
    for (auto nonTerminal:nonTerminals) {
        set<string> followNames = nonTerminal->getFollowNames();
        for (const auto &followName:followNames) {
            nonTerminal->addFollowTerminal(*facade->findTerminal(followName));
        }
        set<string> followDependencyNames = nonTerminal->getFollowDependenciesNames();
        for (const auto &followDependencyName:followDependencyNames) {
            nonTerminal->addFollowDependency(*facade->findNonTerminal(followDependencyName));
        }
    }
    facade->setNonTerminals(nonTerminals);
}

FirstFollowFinder::FirstFollowFinder(Facade *facade) : facade(facade) {}
