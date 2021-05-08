//
// Created by hydroxide on ٣‏/٥‏/٢٠٢١.
//

#ifndef JAVA_COMPILER_NFA_H
#define JAVA_COMPILER_NFA_H
#define lambda (char)150
#include <iostream>
#include <bits/stdc++.h>
#include "InputProcessor.h"

using namespace std;


class Node {
private:
    map <char, Node*> edges;
    bool end = false;
    string regex_name = "";

public:
    void set_regex_name(string re) {
        this->regex_name = re;
    }
    string get_regex_name() {
        return this->regex_name;
    }

    void set_edges(map <char, Node*> &new_edges) {
        this->edges = new_edges;
    }
    map <char, Node*> get_edges() {
        return this->edges;
    }

    void set_end(bool new_end) {
        this->end = new_end;
    }

    bool get_end() {
        return this->end;
    }
};

const vector  <char> reserved{'+', '-', '*', '|', '(', ')'};

bool is_reserved(char ch) {
    for(int i = 0;i<reserved.size();i++){
        if(ch == reserved[i]) return true;
    }
    return false;
}

void add_eps_edge(Node * from, Node* to) {
    char i = (char)255;
    map<char, Node*> mp = from->get_edges();
    while(mp.find(i) != mp.end()) i--;
    mp[i] = to;
    from->set_edges(mp);
}

void remove_eps_edge(Node * node, Node* node_to_remove) {
    map <char, Node*> mp = node->get_edges();
    for(int i = 255;i>=128;i--){
        if(mp.find((char)i) != mp.end() && mp[(char)i] == node_to_remove)  {
            mp.erase((char)i);
            for(int j = i-1;j>=128;j--) {
                if(mp.find((char)j) != mp.end()) {
                    mp[(char)(j+1)] = mp[(char)j];
                }
            }
            break;
        }
    }
    node->set_edges(mp);
}

void add_edge(Node* from, Node* to, char no) {
    map<char, Node*> mp = from->get_edges();
    mp[no] = to;
    from->set_edges(mp);
}

void remove_edge(Node* node, char no) {
    map<char, Node*> mp = node->get_edges();
    mp[no] = nullptr;
    node->set_edges(mp);
}


void add_connection (Node* from, Node* to, Node* end, char sym) {
    if(sym == lambda) {
        add_eps_edge(from, to);
    } else {
        add_edge(from, to, sym);
    }
    remove_eps_edge(from, end);
    add_eps_edge(to, end);
}

void add_closure(Node* from, Node* to,Node* end, char sym) {
    Node * new_node = new Node();
    add_connection(from, new_node, end, sym);
    remove_eps_edge(new_node, end);
    add_eps_edge(new_node, to);
    add_eps_edge(to, end);
    add_eps_edge(from, to);
    add_eps_edge(new_node, from);
}

void add_or_char(Node* curr, Node* new_node, char f, char s, Node* end) {
    Node * temp;
    for(int i = (int)f; i <=(int)s; i++) {
        temp = new Node();
        add_connection(curr, temp, end, (char)i);
        remove_eps_edge(temp, end);
        add_eps_edge(temp, new_node);
    }
    add_eps_edge(new_node, end);
}

void thompson_construction(Node* curr, Node* end_node, string re, int *index) {
    Node * temp_end = new Node();
    add_eps_edge(temp_end, end_node);
    int or_in_lvl = 0;
    int op = 0;
    int end_index = *index;
    for(;end_index<re.length();end_index++){
        if(re[end_index] == '(' && re[end_index-1] != '\\' ) op++;
        if(re[end_index] == ')' && re[end_index-1] != '\\' ) op--;
        if(re[end_index] == '|' && re[end_index-1] != '\\' && op == 1) or_in_lvl++;
        if(op == 0) break;
    }
    (*index)++;
    vector <Node*> v(or_in_lvl+1);
    int node_iter = 0;
    remove_eps_edge(curr, end_node);
    for(auto & n : v) {
        n = new Node();
        add_eps_edge(curr, n);
        add_eps_edge(n, temp_end);
    }

    stack<char> stk;
    for(; *index < end_index; (*index)++) {
        char ch = re[*index];
        while(!stk.empty() && ch != '-' && ch != '*' && ch != '+') {
            Node * new_node = new Node();
            remove_eps_edge(v[node_iter], temp_end);
            add_connection(v[node_iter], new_node, temp_end, stk.top());
            v[node_iter] = new_node;
            stk.pop();
        }
        if (is_reserved(ch)) {
            switch (ch) {
                case '|': {
                    node_iter++;
                    break;
                }
                case '(': {
                    Node * new_end = new Node();
                    remove_eps_edge(v[node_iter], temp_end);
                    add_eps_edge(v[node_iter], new_end);
                    add_eps_edge(new_end, temp_end);
                    thompson_construction(v[node_iter], new_end, re, index);
                    v[node_iter] = new_end;
                    break;
                }
                case ')': {
                    break;
                }
                case '*': {
                    Node * new_node = new Node();
                    add_closure(v[node_iter], new_node, temp_end, stk.top());
                    v[node_iter] = new_node;
                    stk.pop();
                    break;
                }
                case '-': {
                    Node* new_node = new Node();
                    char second = re[(*index)+1];
                    add_or_char(v[node_iter], new_node, stk.top(), second, temp_end);
                    v[node_iter] = new_node;
                    (*index)++;
                    stk.pop();
                    break;
                }
                case '+': {
                    Node * new_node = new Node();
                    add_connection(v[node_iter], new_node, temp_end, stk.top());
                    remove_eps_edge(v[node_iter], temp_end);
                    v[node_iter] = new_node;

                    new_node = new Node();
                    add_closure(v[node_iter], new_node, temp_end, stk.top());
                    v[node_iter] = new_node;
                    stk.pop();
                    break;
                }
                default : {
                    cout << "Error reserved character not found :( \n";
                    break;
                }
            }
        } else {
            if (ch == '\\') {
                (*index)++;
                if(re[*index] == 'L') {
                    stk.push(lambda);
                } else {
                    stk.push(re[*index]);
                }
            } else {
                stk.push(ch);
            }
        }
    }

    if(!stk.empty()) {
        Node * new_node = new Node();
        remove_eps_edge(v[node_iter], temp_end);
        add_connection(v[node_iter], new_node, temp_end, stk.top());
        v[node_iter] = new_node;
        stk.pop();
    }

    if((*index)+1<re.length() && (re[(*index)+1] == '*' || re[(*index)+1] == '+')) {
        (*index)++;
        char ch = re[*index];
        if(ch == '*') {
            add_eps_edge(curr, end_node);
            add_eps_edge(temp_end, curr);
        } else if (ch == '+') {
            add_eps_edge(temp_end, curr);
        }
    }
}


string add_parenthesis(string re) {
    return "(" + re + ")";
}

void generate_NFA_from_regex(Node * start) {
    InputProcessor inputProcessor;
    inputProcessor.processInput();
    inputProcessor.generateRegexList();
    vector<RegularExpression> regexList = inputProcessor.getRegexList();
    vector <Node *> start_nodes(regexList.size());
    vector <Node *> end_nodes(regexList.size());
    int * index;
    int x = 0;
    index = &x;
    for (int i = 0;i<regexList.size();i++) {
        start_nodes[i] = new Node();
        end_nodes[i] = new Node();
        x = 0;
        add_eps_edge(start, start_nodes[i]);
        add_eps_edge(start_nodes[i], end_nodes[i]);
        end_nodes[i]->set_end(true);
        end_nodes[i]->set_regex_name(regexList[i].getName());
        thompson_construction(start_nodes[i], end_nodes[i], add_parenthesis(regexList[i].getExpression()), index);
    }
}

#endif //JAVA_COMPILER_NFA_H
