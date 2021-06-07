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
                pair<Terminal, vector<FatherOfAllThingsTerminal>> newFirst(*facade->findTerminal(production[0].getName()),
                                                                           production);
                nonTerminals[i]->addFirst(newFirst);
            } else {
                for (const auto& first: facade->findNonTerminal(production[0].getName())->getFirst()) {
                    pair<Terminal, vector<FatherOfAllThingsTerminal>> newFirst(first.first, production);
                    nonTerminals[i]->addFirst(newFirst);
                }
            }
        }
    }
    facade->setNonTerminals(nonTerminals);
}

void FirstFollowFinder::findFollow() {
    
}

FirstFollowFinder::FirstFollowFinder(Facade *facade) : facade(facade) {}
