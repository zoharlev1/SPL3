//
// Created by orsmo@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "../include/actionExit.hpp"
#include <string>
#include <iostream>

actionExit::actionExit(string genre) : genre(genre) {}

void actionExit::act() {
    cout << "Exited club " + genre << endl;
}

actionExit::~actionExit() = default;










