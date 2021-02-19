//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//
using namespace std;

#include <string>
#include "../include/connectionHandler.hpp"

#ifndef ASSIGNMENT3CLIENT_KEYBOARDINPUT_HPP
#define ASSIGNMENT3CLIENT_KEYBOARDINPUT_HPP

class Keyboardinput {
public:
    ~Keyboardinput();

    Keyboardinput(ConnectionHandler &CH);

    void input();

private:
    vector<string> split(const string &stringToSplit, char delimiter);

    ConnectionHandler &ch;

    string bookName(int start, int end, vector<string> all);
};

#endif //ASSIGNMENT3CLIENT_KEYBOARDINPUT_HPP


