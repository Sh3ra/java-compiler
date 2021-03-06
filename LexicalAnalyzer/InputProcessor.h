//
// Created by marwan_ashraf on 07-May-21.
//

#ifndef JAVA_COMPILER_INPUTPROCESSOR_H
#define JAVA_COMPILER_INPUTPROCESSOR_H

#include "RegexListGenerator.h"

class InputProcessor {
private:
    string filePath = "rules.txt";
    vector<RegularExpression> regexList;
    RegexListGenerator regexListGenerator;

    void addRegex(const RegularExpression &regularExpression);

public:
    void processInput();

    void generateRegexList();

    void setFilePath(const string &path);

    const vector<RegularExpression> &getRegexList() const;

    static vector<char> getPossibleCharacters();

    int getPriority(const string &tokenName);
};


#endif //JAVA_COMPILER_INPUTPROCESSOR_H
