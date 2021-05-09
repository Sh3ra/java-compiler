//
// Created by marwan_ashraf on 06-May-21.
//

#include "RegularExpression.h"
#include "RegularDefinition.h"
#include "RegexGenerationStrategy.h"
#include <regex>

class ExpressionStrategy : public RegexGenerationStrategy {
public:
    RegularExpression
    generateRegex(RegularExpression &regularExpression, const vector<RegularDefinition> regDefList) override {
        for (RegularDefinition regularDefinition:regDefList) {
            regularExpression.setExpression(
                    regex_replace(regularExpression.getExpression(), regex("\\b" + regularDefinition.getName() + "\\b"),
                                  "(" + regularDefinition.getDefinition() + ")"));
        }
        regularExpression.setExpression(regex_replace(regularExpression.getExpression(), regex("\\s+"), ""));
        string segment;
        stringstream stream(regularExpression.getExpression());
        getline(stream, segment, ':');
        regularExpression.setName(segment);
        getline(stream, segment, ':');
        regularExpression.setExpression(segment);
        return regularExpression;
    }
};

class KeywordStrategy : public RegexGenerationStrategy {
public:
    RegularExpression
    generateRegex(RegularExpression &regularExpression, const vector<RegularDefinition> regDefList) override {
        regularExpression.setExpression(
                regex_replace(regularExpression.getExpression(), regex(R"(\s*\{\s*|\s*\}\s*)"), ""));
        regularExpression.setExpression(regex_replace(regularExpression.getExpression(), regex("\\s+"), "|"));
        regularExpression.setName("Keyword");
        return regularExpression;
    }
};

class PunctuationStrategy : public RegexGenerationStrategy {
public:
    RegularExpression
    generateRegex(RegularExpression &regularExpression, const vector<RegularDefinition> regDefList) override {
        regularExpression.setExpression(
                regex_replace(regularExpression.getExpression(), regex(R"(\s*\[\s*|\s*\]\s*)"), ""));
        regularExpression.setExpression(regex_replace(regularExpression.getExpression(), regex("\\s+"), "|"));
        regularExpression.setName("Punctuation");
        return regularExpression;
    }
};
