//
// Created by wzattout on 09/05/2021.
//

#ifndef JAVA_COMPILER_TESTCODE_H
#define JAVA_COMPILER_TESTCODE_H

#endif //JAVA_COMPILER_TESTCODE_H

#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "DFA_minimization.h"

string takeInput() {
    fstream file;
    string filePath = "test.txt", result = "";
    file.open(filePath, ios::in);
    string line;
    while (getline(file, line)) {
        result.append(line);
    }
    return result;
}

void getTokens(DFA_Node *minimizedGraph) {
    fstream file;
    string filePath = "outputPhase1.txt", input = takeInput();
    file.open(filePath, ios::out);
    string token = "";
    DFA_Node *currentState = minimizedGraph;
    int lastAcceptingIndex = -1;
    for (int i = 0; i < input.size(); ++i) {
        map<char, DFA_Node *> temp = currentState->get_edges();
        if (temp.find(input.at(i)) != temp.end()) {
            currentState = currentState->get_edges().at(input.at(i));
            if (currentState->get_end()) {
                lastAcceptingIndex = i;
                token = currentState->get_token();
            }
        } else if (lastAcceptingIndex != -1) {
            file << token << endl;
            i = lastAcceptingIndex;
            lastAcceptingIndex = -1;
            token = "";
            currentState = minimizedGraph;
        } else if (input.at(i) != ' ') {
            file << "Error!" << endl;
            currentState = minimizedGraph;
        }
        if (i == input.size() - 1) {
            if (lastAcceptingIndex == i) {
                file << token << endl;
            } else {
                if (lastAcceptingIndex != -1) {
                    file << token << endl;
                    i = lastAcceptingIndex;
                    lastAcceptingIndex = -1;
                    token = "";
                    currentState = minimizedGraph;
                } else if (input.at(i) != ' ') {
                    file << "Error!" << endl;
                }
            }
        }
    }
}
