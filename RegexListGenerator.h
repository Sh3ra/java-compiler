//
// Created by maroa on 30-Apr-21.
//

#ifndef JAVA_COMPILER_REGEXLISTGENERATOR_H
#define JAVA_COMPILER_REGEXLISTGENERATOR_H

#include <vector>
#include "RegularDefinition.h"
#include "RegularExpression.h"
#include "RegexGenerator.h"

using namespace std;

class RegexListGenerator {
private:
    vector<RegularDefinition> regularDefinitionList;
    string keywordPattern = R"(\{.+\})";
    string expressionPattern = R"((.+)\:(.+))";
    string punctuationPattern = R"(\[.+\])";
public:
    void addRegularDefinition(const RegularDefinition &regularDefinition);

    vector<RegularDefinition> getRegularDefinitionList();

    void generateRegexList(vector<RegularExpression> &regexList);

    void setRegularDefinitionList(const vector<RegularDefinition> &newRegularDefinitionList);
};

#endif //JAVA_COMPILER_REGEXLISTGENERATOR_H
