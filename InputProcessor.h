//
// Created by marwan_ashraf on 07-May-21.
//

#ifndef JAVA_COMPILER_INPUTPROCESSOR_H
#define JAVA_COMPILER_INPUTPROCESSOR_H

#include "RegexListGenerator.h"

class InputProcessor {
private:
    string filePath = "a.txt";
    vector<RegularExpression> regexList;
    RegexListGenerator regexListGenerator;

    void addRegex(const RegularExpression &regularExpression);

public:
    void processInput();

    void generateRegexList();

    void setFilePath(const string &path);

    const vector<RegularExpression> &getRegexList() const;

    vector<char> getPossibleCharacters();
};


#endif //JAVA_COMPILER_INPUTPROCESSOR_H
