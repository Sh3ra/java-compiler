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

class Minimization {
public:
    DFA_Node *minimize() {
        vector<vector<DFA_Node>> minimizedStates;
        map<DFA_Node *, int> states;
        vector<char> inputs = get_inputs();
        int numOfStates = 2, firstOfCurrentStates = 2, notAccepted, added;
        vector<DFA_Node *> final, nonFinal;
        for (auto &all_dfa_node : all_dfa_nodes) {
            if (!all_dfa_node->get_end()) {
                nonFinal.push_back(all_dfa_node);
                states[all_dfa_node] = 0;
            } else {
                final.push_back(all_dfa_node);
                states[all_dfa_node] = 1;
            }
        }
        for (int m = 0; m < firstOfCurrentStates; ++m) {
            for (int i = 0; i < minimizedStates.at(m).size(); ++i) {
                added = 0;
                if (firstOfCurrentStates == minimizedStates.size()) {
                    minimizedStates.emplace_back();
                    minimizedStates.at(firstOfCurrentStates).push_back(minimizedStates.at(m).at(i));
                    states[&minimizedStates.at(m).at(i)] = firstOfCurrentStates;
                } else {
                    for (int j = firstOfCurrentStates; j < minimizedStates.size(); ++j) {
                        notAccepted = 0;
                        for (char &input : inputs) {
                            if (states[minimizedStates.at(m).at(i).get_edges()[input]] !=
                                states[minimizedStates.at(j).at(0).get_edges()[input]]) {
                                notAccepted++;
                                break;
                            }
                        }
                        if (!notAccepted) {
                            minimizedStates.at(j).push_back(minimizedStates.at(m).at(i));
                            states[&minimizedStates.at(m).at(i)] = j;
                            added = 1;
                            break;
                        }
                    }
                    if (!added) {
                        minimizedStates.emplace_back();
                        minimizedStates.at(minimizedStates.size() - 1).push_back(minimizedStates.at(m).at(i));
                        states[&minimizedStates.at(m).at(i)] = minimizedStates.size() - 1;
                    }
                }
            }
            if (firstOfCurrentStates - m == 1) {
                if ((minimizedStates.size() - firstOfCurrentStates + 1) == numOfStates) {
                    break;
                } else {
                    numOfStates = minimizedStates.size() - firstOfCurrentStates + 1;
                    firstOfCurrentStates = minimizedStates.size();
                }
            }
        }
        vector<DFA_Node> finalMinimizedStates(minimizedStates.size() - firstOfCurrentStates);
        for (int i = 0; i < finalMinimizedStates.size(); ++i) {
            for (int j = 0; j < minimizedStates.at(firstOfCurrentStates + i).size(); ++j) {
                for (char &input : inputs) {
                    finalMinimizedStates.at(i).add_edge(input, &finalMinimizedStates[
                            states[minimizedStates.at(firstOfCurrentStates + i).at(j).get_edges()[input]] -
                            firstOfCurrentStates]);
                }
                if (minimizedStates.at(firstOfCurrentStates + i).at(j).get_end()) {
                    finalMinimizedStates.at(i).set_end(true);
                } else {
                    finalMinimizedStates.at(i).set_end(false);
                }
            }
        }
        return &finalMinimizedStates.at(0);
    }
};