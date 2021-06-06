//
// Created by marwan_ashraf on 06-Jun-21.
//

#ifndef JAVA_COMPILER_INPUTREADER_H
#define JAVA_COMPILER_INPUTREADER_H

#include "Facade.h"

class InputReader {
private:
    string filePath = "grammar.txt";
    Facade *facade;
public:
    explicit InputReader(Facade *facade);

    void readInput();

    void setFilePath(const string &path);
};

#endif //JAVA_COMPILER_INPUTREADER_H