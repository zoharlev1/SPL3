//
// Created by orsmo@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "../include/actionJoin.hpp"

using namespace std;

#include <string>
#include <iostream>

actionJoin::actionJoin(string genre) : genre(genre) {}

void actionJoin::act() {
    cout << "Joined club " + genre << endl;
}

actionJoin::~actionJoin() = default;










