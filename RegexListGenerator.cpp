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
        if (regex_match(regularExpression->getExpression(), regex(keywordPattern))) {
            *regularExpression = ((new RegexGenerator(new KeywordStrategy()))->generateRegex(*regularExpression.base(),
                                                                                             getRegularDefinitionList()));
        } else if (regex_match(regularExpression->getExpression(), regex(punctuationPattern))) {
            *regularExpression = (new RegexGenerator(new PunctuationStrategy()))->generateRegex(
                    *regularExpression.base(), getRegularDefinitionList());
        } else if (regex_match(regularExpression->getExpression(), regex(expressionPattern))) {
            *regularExpression = (new RegexGenerator(new ExpressionStrategy()))->generateRegex(
                    *regularExpression.base(),
                    getRegularDefinitionList());
        }
    }
    for (auto regularExpression = regexList.begin(); regularExpression != regexList.end();) {
        if (regularExpression->getName() == "Keyword") {
            string keywordDefinition = regularExpression->getExpression();
            string segment;
            stringstream stream(keywordDefinition);
            cout << regularExpression - regexList.begin() << endl;
            while (getline(stream, segment, '|')) {
                regexList.emplace_back(segment, segment);
                cout << regularExpression - regexList.begin() << endl;
            }
            regularExpression = regexList.erase(regularExpression);
        } else {
            regularExpression++;
        }
    }
}

void RegexListGenerator::setRegularDefinitionList(const vector<RegularDefinition> &newRegularDefinitionList) {
    RegexListGenerator::regularDefinitionList = newRegularDefinitionList;
}
