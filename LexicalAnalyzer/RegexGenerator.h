//
// Created by maroa on 01-May-21.
//

#ifndef JAVA_COMPILER_REGEXGENERATOR_H
#define JAVA_COMPILER_REGEXGENERATOR_H

#include "RegularExpression.h"
#include "RegularDefinition.h"
#include "RegexGenerationStrategy.h"
#include <vector>

using namespace std;

class RegexGenerator {
private:
    RegexGenerationStrategy *generationStrategy{};
public:
    explicit RegexGenerator(RegexGenerationStrategy *generationStrategy);

    RegularExpression
    generateRegex(RegularExpression &regex, const vector<RegularDefinition> &RegularDefinitionList);
};

#endif //JAVA_COMPILER_REGEXGENERATOR_H