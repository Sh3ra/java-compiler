#include <iostream>
using namespace std;
#include "NFA.h"

int main() {
    Node * start = new Node();
    generate_NFA_from_regex(start);
    return 0;
}
