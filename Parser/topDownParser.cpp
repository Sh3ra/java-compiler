//
// Created by wzattout on 2021-06-07.
//

#include "iostream"
#include "bits/stdc++.h"
#include "predictiveParsingTableForTheGrammar.cpp"

using namespace std;

stack<FatherOfAllThingsTerminal *> s;
fstream file;
map<string, map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>>> parsingTable;

void initializeStack() {
    parsingTable = generatePredictiveParsingTableForTheGrammar();
    vector<NonTerminal *> nonTerminals = facade.getNonTerminals();
    string filePath = "parserOutput.txt";
    s.push(facade.findTerminal("$"));
    s.push(nonTerminals[0]);
    file.open(filePath, ios::out);
}

void parseInput(const string &token) {
    if (token == "$" && s.top()->getName() == "$") {
        file << "accepted code" << endl;
    } else if (s.top()->isTerminal()) {
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
            parseInput(token);
        } else {
            vector<FatherOfAllThingsTerminal> v = temp[token].second;
            file << s.top()->getName() + " --> ";
            s.pop();
            reverse(v.begin(), v.end());
            for (auto &i : v) {
                if(i.isTerminal()){
                    s.push(facade.findTerminal(i.getName()));
                } else {
                    s.push(facade.findNonTerminal(i.getName()));
                }
                file << i.getName() + " ";
            }
            file << endl;
            parseInput(token);
        }
    }
}
