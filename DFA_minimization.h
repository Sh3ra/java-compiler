//
// Created by wzattout on 03/05/2021.
//

#ifndef JAVA_COMPILER_DFA_MINIMIZATION_H
#define JAVA_COMPILER_DFA_MINIMIZATION_H

#endif //JAVA_COMPILER_DFA_MINIMIZATION_H

#include "iostream"
#include "bits/stdc++.h"
#include "DFA.h"

using namespace std;

DFA_Node *minimize() {
    vector<vector<DFA_Node *>> minimizedStates;
    map<DFA_Node *, int> states;
    vector<char> inputs = get_inputs();
    int numOfStates = 2, firstOfCurrentStates = 2, notAccepted, added, firstOfLastStates = 1;
    vector<DFA_Node *> nonFinal;
    vector<vector<DFA_Node *>> final;
    for (auto &all_dfa_node : all_dfa_nodes) {
        if (!all_dfa_node->get_end()) {
            nonFinal.push_back(all_dfa_node);
            states[all_dfa_node] = 0;
        } else {
            int added_ = 0;
            for (int i = 0; i < final.size(); ++i) {
                if (all_dfa_node->get_token() == final.at(i).at(0)->get_token()) {
                    final.at(i).push_back(all_dfa_node);
                    states[all_dfa_node] = 1 + i;
                    added_ = 1;
                    break;
                }
            }
            if (!added_) {
                vector<DFA_Node *> temp;
                temp.push_back(all_dfa_node);
                final.push_back(temp);
                states[all_dfa_node] = final.size();
            }
        }
    }
    minimizedStates.push_back(nonFinal);
    for (auto & i : final) {
        minimizedStates.push_back(i);
    }
    for (int m = 0; m < firstOfCurrentStates; ++m) {
        for (int i = 0; i < minimizedStates.at(m).size(); ++i) {
            added = 0;
            if (firstOfCurrentStates == minimizedStates.size()) {
                minimizedStates.emplace_back();
                minimizedStates.at(firstOfCurrentStates).push_back(minimizedStates.at(m).at(i));
                states[minimizedStates.at(m).at(i)] = firstOfCurrentStates;
            } else {
                for (int j = firstOfCurrentStates; j < minimizedStates.size(); ++j) {
                    notAccepted = 0;
                    for (char &input : inputs) {
                        map<char, DFA_Node *> map1 = minimizedStates.at(m).at(i)->get_edges();
                        map<char, DFA_Node *> map2 = minimizedStates.at(j).at(0)->get_edges();
                        if ((map1.find(input) == map1.end() && map2.find(input) != map2.end())
                            || (map2.find(input) == map2.end() && map1.find(input) != map1.end()) ||
                            (map2.find(input) != map2.end() && map1.find(input) != map1.end() &&
                             states[map1[input]] != states[map2[input]])) {
                            notAccepted++;
                            break;
                        }
                    }
                    if (!notAccepted) {
                        minimizedStates.at(j).push_back(minimizedStates.at(m).at(i));
                        states[minimizedStates.at(m).at(i)] = j;
                        added = 1;
                        break;
                    }
                }
                if (!added) {
                    minimizedStates.emplace_back();
                    minimizedStates.at(minimizedStates.size() - 1).push_back(minimizedStates.at(m).at(i));
                    states[minimizedStates.at(m).at(i)] = minimizedStates.size() - 1;
                }
            }
        }
        if (m == firstOfLastStates) {
            if (minimizedStates.size() - firstOfLastStates - 1 == numOfStates) {
                break;
            }
            numOfStates = minimizedStates.size() - firstOfLastStates - 1;
            firstOfLastStates = minimizedStates.size() - 1;
        }
        firstOfCurrentStates = minimizedStates.size();
    }
    vector<DFA_Node *> finalMinimizedStates(minimizedStates.size() - firstOfLastStates - 1);
    for (auto &finalMinimizedState : finalMinimizedStates) {
        finalMinimizedState = new DFA_Node();
    }
    for (int i = 0; i < finalMinimizedStates.size(); ++i) {
        for (int j = 0; j < minimizedStates.at(firstOfLastStates + i + 1).size(); ++j) {
            map<char, DFA_Node *> map1 = minimizedStates.at(firstOfLastStates + i + 1).at(j)->get_edges();
            for (char &input : inputs) {
                if (map1.find(input) != map1.end()) {
                    finalMinimizedStates.at(i)->add_edge(input, finalMinimizedStates[
                            states[minimizedStates.at(firstOfLastStates + i + 1).at(j)->get_edges()[input]] -
                            firstOfLastStates - 1]);
                }
            }
            if (minimizedStates.at(firstOfLastStates + i + 1).at(j)->get_end()) {
                finalMinimizedStates.at(i)->set_end(true);
                finalMinimizedStates.at(i)->set_token(minimizedStates.at(firstOfLastStates + i + 1).at(j)->get_token());
            } else {
                finalMinimizedStates.at(i)->set_end(false);
                if (minimizedStates.at(firstOfLastStates + i + 1).at(j)->get_isRoot()) {
                    finalMinimizedStates.at(i)->set_isRoot();
                }
            }
        }
    }
    for (auto & finalMinimizedState : finalMinimizedStates) {
        if (finalMinimizedState->get_isRoot()) {
            return finalMinimizedState;
        }
    }
    return nullptr;
}