#include <iostream>

using namespace std;

#include "DFA_minimization.h"

DFA_Node * getMinimizedDFA() {
    Node *start = new Node();
    generate_NFA_from_regex(start);
    DFA_Node *root;
    convert_nfa_to_dfa(start);
    root = minimize();
    return root;
}
