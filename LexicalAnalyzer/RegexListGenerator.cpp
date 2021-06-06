//
// Created by maroa on 30-Apr-21.
//

#include <regex>
#include "RegexListGenerator.h"
#include "RegexGenerationStrategy.cpp"

void RegexListGenerator::addRegularDefinition(const RegularDefinition &regularDefinition) {
    RegexListGenerator::regularDefinitionList.push_back(regularDefinition);
}

vector<RegularDefinition> RegexListGenerator::getRegularDefinitionList() {
    return regularDefinitionList;
}

void RegexListGenerator::generateRegexList(vector<RegularExpression> &regexList) {
    for (auto regularExpression = regexList.begin(); regularExpression != regexList.end(); regularExpression++) {
        if (regex_match(regularExpression->getExpression(), regex(keywordPunctuationPattern))) {
            *regularExpression = ((new RegexGenerator(new KeywordPunctuationStrategy()))->generateRegex(
                    *regularExpression.base(),
                    getRegularDefinitionList()));
        } else if (regex_match(regularExpression->getExpression(), regex(expressionPattern))) {
            *regularExpression = (new RegexGenerator(new ExpressionStrategy()))->generateRegex(
                    *regularExpression.base(),
                    getRegularDefinitionList());
        }
    }
    for (int i = 0; i < regexList.size();) {
        if (regexList[i].getName() == "KeywordPunctuation") {
            string keywordDefinition = regexList[i].getExpression();
            string segment;
            stringstream stream(keywordDefinition);
            while (getline(stream, segment, '|')) {
                regexList.emplace(regexList.begin(), regex_replace(segment, regex(R"((\\)([^\s]+))"), "$2"), segment);
                i++;
            }
            regexList.erase(regexList.begin() + i);
        } else {
            i++;
        }
    }
}

void RegexListGenerator::setRegularDefinitionList(const vector<RegularDefinition> &newRegularDefinitionList) {
    RegexListGenerator::regularDefinitionList = newRegularDefinitionList;
}
