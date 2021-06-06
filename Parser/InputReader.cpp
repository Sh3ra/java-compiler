//
// Created by marwan_ashraf on 06-Jun-21.
//

#include <regex>
#include <fstream>
#include "InputReader.h"

void InputReader::readInput() {
    fstream file;
    file.open(filePath, ios::in);
    if (file.is_open()) {
        string completeInputLine, inputLine;
        vector<string> completeInputLines;
        while (getline(file, inputLine)) {
            if (regex_match(inputLine, regex(R"(.+\:\:\=.+)"))) {
                if (!completeInputLine.empty()) {
                    completeInputLines.push_back(completeInputLine);
                }
                completeInputLine = inputLine;
            } else {
                completeInputLine += inputLine;
            }
        }
        completeInputLines.push_back(completeInputLine);
        file.close();
        for (const auto &line: completeInputLines) {
            string nonTerminalName, productions;
            stringstream stream(line);
            string separator = "::=";
            stream >> nonTerminalName >> separator >> productions;
            while (!stream.eof()) {
                string temp;
                stream >> temp;
                productions += " " + temp;
            }
            bool flag = false;
            NonTerminal *nonTerminal;
            for (NonTerminal *nT:facade->getNonTerminals()) {
                if (nT->isThisMe(nonTerminalName)) {
                    flag = true;
                    nonTerminal = nT;
                    break;
                }
            }
            if (!flag) {
                nonTerminal = new NonTerminal(regex_replace(nonTerminalName, regex("\\s+"), ""));
                facade->addNonTerminal(nonTerminal);
            }
            stream.clear();
            stream.str(string(productions));
            vector<string> splitProductions;
            string production;
            while (getline(stream, production, '|')) {
                production = regex_replace(production, regex("\\s+"), " ");
                splitProductions.push_back(regex_replace(production, regex("^\\s|\\s$"), ""));
            }
            for (const string &splitProduction: splitProductions) {
                vector<string> productionElements;
                string element;
                stream.clear();
                stream.str(string(splitProduction));
                while (getline(stream, element, ' ')) {
                    productionElements.push_back(element);
                }
                vector<FatherOfAllThingsTerminal> nonTerminalProduction;
                for (const string &productionElement:productionElements) {
                    if (regex_match(productionElement, regex("\\'.+\\'"))) {
                        string terminalName = regex_replace(productionElement, regex("\\'"), "");
                        flag = false;
                        for (Terminal *terminal: facade->getTerminals()) {
                            if (terminal->isThisMe(terminalName)) {
                                nonTerminalProduction.push_back(*terminal);
                                flag = true;
                                break;
                            }
                        }
                        if (!flag) {
                            auto *newTerminal = new Terminal(terminalName);
                            facade->addTerminal(newTerminal);
                            nonTerminalProduction.push_back(*newTerminal);
                        }
                    } else {
                        const string &newNonTerminalName = productionElement;
                        flag = false;
                        for (NonTerminal *nT: facade->getNonTerminals()) {
                            if (nT->isThisMe(newNonTerminalName)) {
                                nonTerminalProduction.push_back(*nT);
                                flag = true;
                                break;
                            }
                        }
                        if (!flag) {
                            auto *newNonTerminal = new NonTerminal(newNonTerminalName);
                            facade->addNonTerminal(newNonTerminal);
                            nonTerminalProduction.push_back(*newNonTerminal);

                        }
                    }
                }
                nonTerminal->addProduction(nonTerminalProduction);
            }
        }
    }
}

void InputReader::setFilePath(const string &path) {
    filePath = path;
}

InputReader::InputReader(Facade *facade) {
    this->facade = facade;
}

