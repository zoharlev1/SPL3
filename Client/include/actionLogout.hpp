//
// Created by orsmo@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_ACTIONLOGOUT_HPP
#define ASSIGNMENT3CLIENT_ACTIONLOGOUT_HPP

#include "../include/action.hpp"
#include "../include/connectionHandler.hpp"

using namespace std;

#include <string>

class actionLogout : public action {
public:
    virtual void act() override final;

    actionLogout(ConnectionHandler const *CH);

    actionLogout &operator=(const actionLogout &other);

    actionLogout(const actionLogout &sess);
    ~actionLogout();

private:
    ConnectionHandler *ch;

};

#endif //ASSIGNMENT3CLIENT_ACTIONLOGOUT_HPP
