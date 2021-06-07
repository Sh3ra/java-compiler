#include "Facade.h"
#include <bits/stdc++.h>

using namespace std;

map<string ,map<string ,pair<pair<bool,bool>,vector<FatherOfAllThingsTerminal>>>> generatePredictiveParsingTableForTheGrammar()
{
    map<string ,map<string ,pair<pair<bool,bool>,vector<FatherOfAllThingsTerminal>>>>table;
    Facade facade;
    vector<NonTerminal*>all_non_terminals=facade.getNonTerminals();
    for(int i=0;i<all_non_terminals.size();i++)
    {
        vector<pair<Terminal, vector<FatherOfAllThingsTerminal>>>First=all_non_terminals[i]->getFirst();
        for(int j=0;j<First.size();j++) {
            all_non_terminals[i]->addToPredictiveTable({false,false},First[j].second,First[j].first.getName());
        }
        vector<Terminal>Follow=all_non_terminals[i]->getFollow();
        for(int j=0;j<Follow.size();j++)
        {
            if(all_non_terminals[i]->isGoesToEpsilon())
            {
                all_non_terminals[i]->addToPredictiveTable({false,true},vector<FatherOfAllThingsTerminal>(),Follow[j].getName());
            }
            else
            {
                 all_non_terminals[i]->addToPredictiveTable({true,false},vector<FatherOfAllThingsTerminal>(),Follow[j].getName());
            }
            table[all_non_terminals[i]->getName()]=all_non_terminals[i]->getPredictiveTableRow();
        }

    }

    return table;
}
