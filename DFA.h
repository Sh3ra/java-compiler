#include <iostream>
#include <bits/stdc++.h>
#include "NFA.h"
using namespace std;

class DFA_Node
{
private:
    map<char, DFA_Node *> edges;
    vector<Node *> covered_nfa_nodes;
    bool end = false;

public:
    void add_edge(char key,DFA_Node* value)
    {
        edges[key]=value;
    }
    void set_edges(map<char, DFA_Node *> &new_edges)
    {
        this->edges = new_edges;
    }
    map<char, DFA_Node *> get_edges()
    {
        return this->edges;
    }

    void add_covered_node(Node *node)
    {
        covered_nfa_nodes.push_back(node);
    }
    vector<Node *> get_covered_vector()
    {
        return this->covered_nfa_nodes;
    }
    Node *get_covered_nfa_node(int i)
    {
        return covered_nfa_nodes[i];
    }
    void set_end(bool new_end)
    {
        this->end = new_end;
    }

    bool get_end()
    {
        return this->end;
    }
};

vector<DFA_Node *> all_dfa_nodes;

void add_all_epsillon(DFA_Node *dfa_node)
{
    queue<Node *> q;

    for (int i = 0; i < dfa_node->get_covered_vector().size(); i++)
    {
        Node *nfa_node = dfa_node->get_covered_nfa_node(i);
        q.push(nfa_node);
    }
    while (!q.empty())
    {
        Node *nfa_node = q.front();
        q.pop();
        for (char c = 255; c > 128; c--)
        {
            if ((nfa_node->get_edges().find(c) != nfa_node->get_edges().end()) &&
                find(dfa_node->get_covered_vector().begin(), dfa_node->get_covered_vector().end(), nfa_node->get_edges()[c]) == dfa_node->get_covered_vector().end())
            {
                dfa_node->add_covered_node(nfa_node->get_edges()[c]);
                q.push(nfa_node->get_edges()[c]);
            }
            else
                break;
        }
    }
}

vector<char> get_inputs()
{
    return vector<char>();
}

void check_input(char input, DFA_Node *dfa_node,DFA_Node* new_dfa_node)
{
    for (int i = 0; i < dfa_node->get_covered_vector().size(); i++)
    {
        Node *nfa_node = dfa_node->get_covered_nfa_node(i);
        if (nfa_node->get_edges().find(input) != nfa_node->get_edges().end())
        {
            new_dfa_node->add_covered_node(nfa_node);
        }
    }
}

bool check_covered_vector_exist(DFA_Node* dfa_node)
{

    return false;
}

DFA_Node *convert_nfa_to_dfa(Node *root)
{
    vector<char> inputs = get_inputs();
    //start with the first node and cover all epsillon
    DFA_Node start;
    DFA_Node *start_ptr = &start;
    start_ptr->add_covered_node(root);
    add_all_epsillon(start_ptr);
    queue<DFA_Node *> q;
    q.push(start_ptr);
    while (!q.empty())
    {
        DFA_Node *temp = q.front();
        q.pop();
        all_dfa_nodes.push_back(temp);
        //test all input
        for (int i = 0; i < inputs.size(); i++)
        {
            DFA_Node new_dfa_node;
            DFA_Node* new_dfa_pointer;
            check_input(inputs[i], temp,new_dfa_pointer);
            add_all_epsillon(new_dfa_pointer);
            if(!check_covered_vector_exist(new_dfa_pointer))
            {
                temp->add_edge(inputs[i],new_dfa_pointer);
                q.push(new_dfa_pointer);
            }
        }
    }

    return start_ptr;
}