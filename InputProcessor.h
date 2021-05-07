//
// Created by marwan_ashraf on 07-May-21.
//

#ifndef JAVA_COMPILER_INPUTPROCESSOR_H
#define JAVA_COMPILER_INPUTPROCESSOR_H

#include "RegexListGenerator.h"

class InputProcessor {
private:
    string filePath = "D:\\java-compiler\\a.txt";
    vector<RegularExpression> regexList;
    RegexListGenerator regexListGenerator;

public:
    void processInput();

    void generateRegexList();

    void addRegex(const RegularExpression &regularExpression);

    void setFilePath(const string &path);

    const vector<RegularExpression> &getRegexList() const;
};


#endif //JAVA_COMPILER_INPUTPROCESSOR_H
