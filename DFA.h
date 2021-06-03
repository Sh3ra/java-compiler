#include <iostream>
#include <bits/stdc++.h>
#include "NFA.h"

using namespace std;

class DFA_Node {
private:
    map<char, DFA_Node *> edges;
    vector<Node *> covered_nfa_nodes;
    map<Node *, bool> covered_nfa_nodes_map;
    bool end = false;
    bool isRoot = false;
    string token;
    int priority = INT_MAX;
public:
    void add_edge(char key, DFA_Node *value) {
        edges[key] = value;
    }

    void set_edges(map<char, DFA_Node *> &new_edges) {
        this->edges = new_edges;
    }

    map<char, DFA_Node *> get_edges() {
        return this->edges;
    }

    void add_covered_node(Node *node) {
        covered_nfa_nodes.push_back(node);
        covered_nfa_nodes_map[node] = true;
    }

    vector<Node *> get_covered_vector() {
        return this->covered_nfa_nodes;
    }

    map<Node *, bool> get_covered_map() {
        return this->covered_nfa_nodes_map;
    }

    Node *get_covered_nfa_node(int i) {
        return covered_nfa_nodes[i];
    }

    void set_end(bool new_end) {
        this->end = new_end;
    }

    bool get_end() {
        return this->end;
    }

    void set_token(string t) {
        int newPriority = inputProcessor.getPriority(t);
        if (newPriority < this->priority) {
            this->priority = newPriority;
            this->token = t;
        }
    }

    string get_token() {
        return this->token;
    }

    void set_isRoot()
    {
        this->isRoot=true;
    }

    bool get_isRoot()
    {
        return  this->isRoot;
    }

};

DFA_Node *get_node_from_map(DFA_Node *pNode);

vector<DFA_Node *> all_dfa_nodes;

void add_all_epsillon(DFA_Node *dfa_node) {
    queue<Node *> q;

    for (int i = 0; i < dfa_node->get_covered_vector().size(); i++) {
        Node *nfa_node = dfa_node->get_covered_nfa_node(i);
        q.push(nfa_node);
    }
    while (!q.empty()) {
        Node *nfa_node = q.front();
        q.pop();
        map<char, Node *> mp = nfa_node->get_edges();

        for (int c = 255; c >= 128; c--) {
            if ((mp.find(c) != mp.end()) && !(dfa_node->get_covered_map()[nfa_node->get_edges()[c]])) {
                dfa_node->add_covered_node(nfa_node->get_edges()[c]);
                q.push(nfa_node->get_edges()[c]);
                if (nfa_node->get_edges()[c]->get_end()) {
                    dfa_node->set_end(true);
                    dfa_node->set_token(nfa_node->get_edges()[c]->get_regex_name());
                }
            } else
                break;
        }
    }
}

vector<char> get_inputs() {
    return InputProcessor::getPossibleCharacters();
}

void check_input(char input, DFA_Node *dfa_node, DFA_Node *new_dfa_node) {
    for (int i = 0; i < dfa_node->get_covered_vector().size(); i++) {
        Node *nfa_node = dfa_node->get_covered_nfa_node(i);
        map<char, Node *> mp = nfa_node->get_edges();

        if (mp.find(input) != mp.end()) {
            new_dfa_node->add_covered_node(nfa_node->get_edges()[input]);
        }
    }
}

template<typename Map>
bool map_compare(Map const &lhs, Map const &rhs) {
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(),
                                                  rhs.begin());
}

bool check_covered_vector_exist(DFA_Node *dfa_node) {
    if (dfa_node->get_covered_vector().size() == 0)return true;
    for (int i = 0; i < all_dfa_nodes.size(); i++) {
        if ((dfa_node != all_dfa_nodes[i]) &&
            map_compare(dfa_node->get_covered_map(), all_dfa_nodes[i]->get_covered_map())) {
            return true;
        }
    }

    return false;
}

DFA_Node *convert_nfa_to_dfa(Node *root) {
    vector<char> inputs = get_inputs();
    //start with the first node and cover all epsilon
    DFA_Node *start_ptr = new DFA_Node();
    start_ptr->add_covered_node(root);
    add_all_epsillon(start_ptr);
    all_dfa_nodes.push_back(start_ptr);
    queue<DFA_Node *> q;
    q.push(start_ptr);
    while (!q.empty()) {
        DFA_Node *temp = q.front();
        q.pop();
        //test all input
        for (int i = 0; i < inputs.size(); i++) {
            DFA_Node *new_dfa_pointer = new DFA_Node();
            check_input(inputs[i], temp, new_dfa_pointer);
            add_all_epsillon(new_dfa_pointer);
            if (!check_covered_vector_exist(new_dfa_pointer)) {
                temp->add_edge(inputs[i], new_dfa_pointer);
                q.push(new_dfa_pointer);
                all_dfa_nodes.push_back(new_dfa_pointer);
            } else if ((new_dfa_pointer->get_covered_vector().size() != 0)) {
                temp->add_edge(inputs[i], get_node_from_map(new_dfa_pointer));
            }
        }
    }

    return start_ptr;
}

DFA_Node *get_node_from_map(DFA_Node *dfa_node) {
    for (int i = 0; i < all_dfa_nodes.size(); i++) {
        if (map_compare(dfa_node->get_covered_map(), all_dfa_nodes[i]->get_covered_map())) {
            return all_dfa_nodes[i];
        }
    }
    return nullptr;
}
