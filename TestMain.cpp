//
// Created by marwan_ashraf on 07-May-21.
//

#include <iostream>
#include <regex>
#include "InputProcessor.h"

int main(){
    InputProcessor inputProcessor;
    inputProcessor.processInput();
    inputProcessor.generateRegexList();
    vector<RegularExpression> regexList = inputProcessor.getRegexList();
    for(RegularExpression regularExpression:regexList){
        cout << regularExpression.getName() << " " << regularExpression.getExpression() << endl;
    }
    inputProcessor.getPossibleCharacters();
    return 0;
}