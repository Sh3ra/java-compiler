//
// Created by maroa on 01-May-21.
//

#include "RegexGenerator.h"

RegexGenerator::RegexGenerator(RegexGenerationStrategy *generationStrategy){
    this->generationStrategy = generationStrategy;
}

RegularExpression RegexGenerator::generateRegex(RegularExpression &regex,
                                                const vector<RegularDefinition> &RegularDefinitionList) {
    return generationStrategy->generateRegex(regex, RegularDefinitionList);
}

