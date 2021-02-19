//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "connectionHandler.hpp"

#ifndef ASSIGNMENT3CLIENT_SERVERREADER_HPP
#define ASSIGNMENT3CLIENT_SERVERREADER_HPP

class ServerReader {
public:
    ServerReader(ConnectionHandler &CH);

    void read();

private:
    ConnectionHandler &ch;
};

#endif //ASSIGNMENT3CLIENT_SERVERREADER_HPP
