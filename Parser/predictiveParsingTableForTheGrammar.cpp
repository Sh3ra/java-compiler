#include "Facade.h"
#include <bits/stdc++.h>

using namespace std;
Facade facade;

map<string ,map<string ,pair<pair<bool,bool>,vector<FatherOfAllThingsTerminal>>>> generatePredictiveParsingTableForTheGrammar()
{
    map<string ,map<string ,pair<pair<bool,bool>,vector<FatherOfAllThingsTerminal>>>>table;
    vector<NonTerminal*>all_non_terminals=facade.getNonTerminals();
    for(auto & all_non_terminal : all_non_terminals)
    {
        vector<pair<Terminal, vector<FatherOfAllThingsTerminal>>>First=all_non_terminal->getFirst();
        for(auto & j : First) {
            all_non_terminal->addToPredictiveTable({false,false},j.second,j.first.getName());
        }
        vector<Terminal>Follow=all_non_terminal->getFollow();
        for(auto & j : Follow)
        {
            if(all_non_terminal->goesToEpsilon())
            {
                all_non_terminal->addToPredictiveTable({false,true},vector<FatherOfAllThingsTerminal>(),j.getName());
            }
            else
            {
                 all_non_terminal->addToPredictiveTable({true,false},vector<FatherOfAllThingsTerminal>(),j.getName());
            }
            table[all_non_terminal->getName()]=all_non_terminal->getPredictiveTableRow();
        }

    }

    return table;
}
