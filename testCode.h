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

vector<string> takeInput() {
    vector<string> inputFile;
    fstream file;
    string filePath = "test.txt";
    file.open(filePath, ios::in);
    string line;
    while (getline(file, line)) {
        inputFile.push_back(line);
    }
    return inputFile;
}

vector<string> inputs = takeInput();

string checkString(DFA_Node *minimizedGraph, string fillIn) {
    DFA_Node *currentNode = minimizedGraph;
    for (char &j : fillIn) {
        currentNode = currentNode->get_edges()[j];
    }
    if (currentNode->get_end()) {
        vector<string>tokens=currentNode->get_token();
        if(find(tokens.begin(),tokens.end(),fillIn)!=tokens.end())
        {
            return fillIn;
        }
        else
        {
            return tokens.front();
        }

    } else {
        return "error";
    }
}

void getTokens(DFA_Node *minimizedGraph) {
    fstream file;
    string filePath = "output.txt";
    file.open(filePath, ios::out);
    string fillIn;
    for (auto &input : inputs) {
        if (!fillIn.empty()) {
            file << checkString(minimizedGraph, fillIn) << endl;
            fillIn.clear();
        }
        for (char &j : input) {
            if (j == ' ' || j == '\n') {
                if (!fillIn.empty()) {
                    file << checkString(minimizedGraph, fillIn) << endl;
                    fillIn.clear();
                }
            } else if (fillIn.empty()) {
                fillIn.push_back(j);
            } else if ((j >= 'A' && j <= 'z') || (j >= '0' && j <= '9')) {
                if ((fillIn.at(fillIn.size() - 1) >= 'A' && fillIn.at(fillIn.size() - 1) <= 'z') ||
                    (fillIn.at(fillIn.size() - 1) >= '0' && fillIn.at(fillIn.size() - 1) <= '9')) {
                    fillIn.push_back(j);
                } else {
                    file << checkString(minimizedGraph, fillIn) << endl;
                    fillIn.clear();
                    fillIn.push_back(j);
                }
            } else if ((fillIn.at(fillIn.size() - 1) >= 'A' && fillIn.at(fillIn.size() - 1) <= 'z') ||
                       (fillIn.at(fillIn.size() - 1) >= '0' && fillIn.at(fillIn.size() - 1) <= '9')) {
                file << checkString(minimizedGraph, fillIn) << endl;
                fillIn.clear();
                fillIn.push_back(j);
            } else {
                fillIn.push_back(j);
            }
        }
    }
    if (!fillIn.empty()) {
        file << checkString(minimizedGraph, fillIn) << endl;
    }
}