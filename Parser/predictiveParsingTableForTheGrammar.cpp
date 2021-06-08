#include "Facade.h"
#include <bits/stdc++.h>

using namespace std;
Facade facade;

map<string, map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>>>
generatePredictiveParsingTableForTheGrammar() {
    facade.readAndProcessInput();
    fstream tableFile;
    string filePath = "predictiveTableOutput.txt";
    tableFile.open(filePath, ios::out);

    map<string, map<string, pair<pair<bool, bool>, vector<FatherOfAllThingsTerminal>>>> table;
    vector<NonTerminal *> all_non_terminals = facade.getNonTerminals();
    for (auto &all_non_terminal : all_non_terminals) {
        tableFile << all_non_terminal->getName() << " :\t";
        vector<pair<Terminal, vector<FatherOfAllThingsTerminal>>> First = all_non_terminal->getFirst();
        for (auto &j : First) {
            if (j.first.getName() != "Epsilon") {
                all_non_terminal->addToPredictiveTable({false, false}, j.second, j.first.getName());
                tableFile << j.first.getName() << "[ ";
                for (auto &i : j.second) {
                    tableFile << i.getName() << " ";
                }
                tableFile << "]\t";
            }
        }
        vector<Terminal> Follow = all_non_terminal->getFollowTerminals();
        for (auto &j : Follow) {
            if (all_non_terminal->goesToEpsilon()) {
                all_non_terminal->addToPredictiveTable({false, true}, vector<FatherOfAllThingsTerminal>(), j.getName());
                tableFile << j.getName() << "[ SYNC ]\t";
            } else {
                all_non_terminal->addToPredictiveTable({true, false}, vector<FatherOfAllThingsTerminal>(), j.getName());
                tableFile << j.getName() << "[ EPSILON ]\t";
            }
        }
        tableFile << endl;
        table[all_non_terminal->getName()] = all_non_terminal->getPredictiveTableRow();

    }
    tableFile.close();
    return table;
}
