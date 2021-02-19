//
// Created by orsmo@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_ACTIONJOIN_HPP
#define ASSIGNMENT3CLIENT_ACTIONJOIN_HPP
//#include "../include/actionJoin.hpp"
using namespace std;

#include <string>
#include <boost/system/error_code.hpp>
#include "action.hpp"


class actionJoin : public action {
public:
    actionJoin(string genre);

    virtual void act() override final ;
    ~actionJoin();

private:
    string genre;
};

#endif //ASSIGNMENT3CLIENT_ACTIONJOIN_HPP
