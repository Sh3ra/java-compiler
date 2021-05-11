//
// Created by marwan_ashraf on 06-May-21.
//

#ifndef JAVA_COMPILER_REGEXGENERATIONSTRATEGY_H
#define JAVA_COMPILER_REGEXGENERATIONSTRATEGY_H


#include <vector>

class RegexGenerationStrategy {
public:
    virtual RegularExpression generateRegex(RegularExpression &regex, vector<RegularDefinition> regDefList) = 0;
};


#endif //JAVA_COMPILER_REGEXGENERATIONSTRATEGY_H
