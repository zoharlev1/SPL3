//
// Created by orsmo@wincs.cs.bgu.ac.il on 10/01/2020.
//
#include "../include/KeyboardInput.hpp"

#include "../include/actionLogout.hpp"


void actionLogout::act()  {
    ch->close();
}


actionLogout::actionLogout(ConnectionHandler const *CH) : ch((ConnectionHandler *) CH) {}

actionLogout &actionLogout::operator=(const actionLogout &other) {
    return *this;
}

actionLogout::actionLogout(const actionLogout &sess) : ch() {
}

actionLogout::~actionLogout() = default;





