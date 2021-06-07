//
// Created by wzattout on 09/05/2021.
//

#ifndef JAVA_COMPILER_TESTCODE_H
#define JAVA_COMPILER_TESTCODE_H

#endif //JAVA_COMPILER_TESTCODE_H

#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "LexicalAnalyzer/lexicalAnalyzer.cpp"
#include "Parser/topDownParser.cpp"

string input;

void takeCodeInput(fstream *file1) {
    char ch;
    if (file1->get(ch)) {
        input.push_back(ch);
    }
}

void getAndUseToken(DFA_Node *minimizedGraph) {
    initializeStack();
    fstream file1, file2;
    string filePath1 = "mainCode.txt";
    file1.open(filePath1, ios::in);
    string filePath2 = "lexicalAnalyzerOutput.txt";
    file2.open(filePath2, ios::out);
    string token;
    DFA_Node *currentState = minimizedGraph;
    int lastAcceptingIndex = -1;
    takeCodeInput(&file1);
    for (int i = 0; i < input.size(); ++i) {
        map<char, DFA_Node *> temp = currentState->get_edges();
        if (temp.find(input.at(i)) != temp.end()) {
            currentState = currentState->get_edges().at(input.at(i));
            if (currentState->get_end()) {
                lastAcceptingIndex = i;
                token = currentState->get_token();
            }
        } else if (lastAcceptingIndex != -1) {
            file2 << token << endl;
            parseInput(token);
            i = lastAcceptingIndex;
            lastAcceptingIndex = -1;
            token = "";
            currentState = minimizedGraph;
        } else if (input.at(i) != ' ' && input.at(i) != '\n'&& input.at(i) != '\r') {
            file2 << "Error!" << endl;
        }
        if (!file1.eof()) {
            takeCodeInput(&file1);
        } else if (i == input.size() - 1) {
            if (lastAcceptingIndex == i) {
                file2 << token << endl;
                parseInput(token);
            } else {
                if (lastAcceptingIndex != -1) {
                    file2 << token << endl;
                    parseInput(token);
                    i = lastAcceptingIndex;
                    lastAcceptingIndex = -1;
                    token = "";
                    currentState = minimizedGraph;
                } else if (input.at(i) != ' ' && input.at(i) != '\n' && input.at(i) != '\r') {
                    file2 << "Error!" << endl;
                }
            }
        }
    }
}
