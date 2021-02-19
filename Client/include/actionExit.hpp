//
// Created by orsmo@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_ACTIONEXIT_HPP
#define ASSIGNMENT3CLIENT_ACTIONEXIT_HPP
//#include "../include/actionExit.hpp"
using namespace std;

#include <string>
#include "action.hpp"


class actionExit : public action {
public:
    actionExit(string genre);

    virtual void act() override final;
    ~actionExit();


private:
    string genre;
};

#endif //ASSIGNMENT3CLIENT_ACTIONEXIT_HPP
