//
// Created by marwan_ashraf on 07-May-21.
//

#include <fstream>
#include <iostream>
#include <regex>
#include "InputProcessor.h"

void InputProcessor::generateRegexList() {
    regexListGenerator.generateRegexList(regexList);
}

void InputProcessor::addRegex(const RegularExpression &regularExpression) {
    regexList.push_back(regularExpression);
}

void InputProcessor::setFilePath(const string &path) {
    InputProcessor::filePath = path;
}

void InputProcessor::processInput() {
    fstream file;
    file.open(filePath, ios::in);
    if (file.is_open()) {
        string rule;
        while (getline(file, rule)) {
            if (regex_match(rule, regex(R"(([^\\]+)\=(.+))"))) {
                rule = regex_replace(rule, regex("\\s+"), "");
                string segment;
                stringstream stream(rule);
                getline(stream, segment, '=');
                string name = segment;
                getline(stream, segment, '=');
                string definition = segment;
                regexListGenerator.addRegularDefinition(RegularDefinition(name, definition));
            } else {
                addRegex(RegularExpression("tempName", rule));
            }
        }
        file.close();
    }
    vector<RegularDefinition> reversedRegularDefinitionList = regexListGenerator.getRegularDefinitionList();
    reverse(reversedRegularDefinitionList.begin(), reversedRegularDefinitionList.end());
    regexListGenerator.setRegularDefinitionList(reversedRegularDefinitionList);
    getPossibleCharacters();
}

const vector<RegularExpression> &InputProcessor::getRegexList() const {
    return regexList;
}

vector<char> InputProcessor::getPossibleCharacters() {
    vector<char> characters;
    characters.clear();
    for (int i = 32; i < 127; i++) {
        characters.push_back((char) i);
    }
    for (char character:characters)
        cout << character << endl;
    return characters;
}
