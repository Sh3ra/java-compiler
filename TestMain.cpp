#include <iostream>

using namespace std;

#include "DFA.h"

int main() {
    Node *start = new Node();
    generate_NFA_from_regex(start);
    map <char, Node*> mp = start->get_edges();
    cout << (mp.find(' ') != mp.end());

    DFA_Node *root = new DFA_Node();
    root = convert_nfa_to_dfa(start);
    cout << root->get_edges().size();

    return 0;
}
