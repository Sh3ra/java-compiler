#include <iostream>

using namespace std;

#include "testCode.h"

int main() {
    Node *start = new Node();
    generate_NFA_from_regex(start);
    DFA_Node *root = new DFA_Node();
    root = convert_nfa_to_dfa(start);
    root = minimize();
    getTokens(root);
    return 0;
}
