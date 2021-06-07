//
// Created by wzattout on 2021-06-07.
//

#include "iostream"
#include "bits/stdc++.h"
#include "predictiveParsingTableForTheGrammar.cpp"

using namespace std;

stack<FatherOfAllThingsTerminal *> s;
fstream file;

void initializeStack() {
    vector<NonTerminal *> nonTerminals;
    string filePath = "parserOutput.txt";
    //s.push($);
    s.push(nonTerminals[0]);
    file.open(filePath, ios::out);
}

void parseInput(const string &token) {
    map<string, map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>>> parsingTable = generatePredictiveParsingTableForTheGrammar();
    if (s.top()->isTerminal()) {
        if (token == s.top()->getName()) {
            file << "match " + token + " " + s.top()->getName() << endl;
            s.pop();
        } else {
            file << "Error: missing, " + token + " inserted" << endl;
            s.pop();
            parseInput(token);
        }
    } else {
        map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>> temp = parsingTable[s.top()->getName()];
        if (temp.find(token) == temp.end()) {
            file << "Error: discard " + token << endl;
        } else if (temp[token].first.first) {
            file << "Error" << endl;
            s.pop();
            parseInput(token);
        } else if (temp[token].first.second) {
            file << s.top()->getName() + " --> epsilon" << endl;
            s.pop();
        } else {
            s.pop();
            vector<FatherOfAllThingsTerminal> v = temp[token].second;
            file << s.top()->getName() + " --> ";
            for (auto &i : v) {
                s.push(&i);
                file << i.getName() + " ";
            }
            file << endl;
        }
    }
}
