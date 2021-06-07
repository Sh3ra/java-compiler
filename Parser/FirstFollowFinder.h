//
// Created by marwan_ashraf on 07-Jun-21.
//

#ifndef JAVA_COMPILER_FIRSTFOLLOWFINDER_H
#define JAVA_COMPILER_FIRSTFOLLOWFINDER_H


#include "Facade.h"

class FirstFollowFinder {
private:
    Facade *facade;
public:
    explicit FirstFollowFinder(Facade *facade);

    void findFirst();
    void findFollow();
};


#endif //JAVA_COMPILER_FIRSTFOLLOWFINDER_H
