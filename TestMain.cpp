//
// Created by marwan_ashraf on 07-May-21.
//

#include <iostream>
#include "InputProcessor.h"

int main(){
    InputProcessor inputProcessor;
    inputProcessor.processInput();
    inputProcessor.generateRegexList();
    /*for(RegularDefinition regularDefinition:inputProcessor.regexListGenerator.getRegularDefinitionList()){
        cout << regularDefinition.getName() << " " << regularDefinition.getDefinition() << endl;
    }
    for(RegularExpression regularExpression:inputProcessor.regexList){
        cout << regularExpression.getName() << " " << regularExpression.getExpression() << endl;
    }*/
    return 0;
}