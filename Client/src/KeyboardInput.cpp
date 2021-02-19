//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include "../include/KeyboardInput.hpp"
#include "../include/connectionHandler.hpp"
#include "../include/actionJoin.hpp"
#include "../include/actionExit.hpp"
#include "../include/actionLogout.hpp"
#include <boost/algorithm/string.hpp>


Keyboardinput::Keyboardinput(ConnectionHandler &CH) : ch(CH) {}


void Keyboardinput::input() {


    while (ch.getloggedIn()) {
        string input;
        getline(cin, input);
        vector<string> strs;
        string output = "";
        boost::split(strs, input, boost::is_any_of(" "));
        if (strs[0] == "login") {
            output = "CONNECT" + '\n';
            output = output + "accept version:1.2" + '\n';
            output = output + "host:stomp.cs.bgu.ac.il" + '\n';
            output = output + "login:" + strs[2] + '\n';
            output = output + "password:" + strs[3] + '\n';
            output = output + '\n';
            output = output + '\0';
        }
        if (strs[0] == "join") {
            string temp = "SUBSCRIBE";
            output = temp + '\n';
            output = output + "destination:" + strs[1] + '\n';
            ch.getClient().insertSubId(strs[1]);
            output = output + "id:" + to_string(ch.getClient().getSubId(strs[1])) + '\n';
            output = output + "receipt:" + to_string(ch.getClient().getReceipt()) + '\n';
            action *act;
            actionJoin actJ(strs[1]);
            act = &actJ;
            ch.getClient().insertReceiptAction(ch.getClient().getReceipt(), act);
            ch.getClient().updateReceipt();
            output = output + '\n';
            output = output + '\0';


        }
        if (strs[0] == "exit") {
            string temp = "UNSUBSCRIBE";
            output = temp + '\n';
            output = output + "destination:" + strs[1] + '\n';
            output = output + "id:" + to_string(ch.getClient().getSubId(strs[1])) + '\n';
            output = output + "receipt:" + to_string(ch.getClient().getReceipt()) + '\n';
            action *act;
            actionExit actE(strs[1]);
            act = &actE;
            ch.getClient().insertReceiptAction(ch.getClient().getReceipt(), act);
            ch.getClient().updateReceipt();
            output = output + '\n';
            output = output + '\0';
        }
        if (strs[0] == "add") {
            string temp = "SEND";
            output = temp + '\n';
            output = output + "destination:" + strs[1] + '\n';
            output = output + ch.getClient().getUserName() + " has added the book ";
            output = output + bookName(2, strs.size(), strs);
            ch.getClient().addBook(strs[1], bookName(2, strs.size(), strs), "");

            output = output + '\n';
            output = output + '\n';
            output = output + '\0';
        }
        if (strs[0] == "borrow") {
            string temp = "SEND";
            output = temp + '\n';
            output = output + "destination:" + strs[1] + '\n';
            output = output + '\n';
            output = output + ch.getClient().getUserName() + " wish to borrow " + bookName(2, strs.size(), strs) + '\n';
            ch.getClient().addToWishlist(bookName(2, strs.size(), strs));
            output = output + '\0';

        }
        if (strs[0] == "return") {
            string temp = "SEND";
            output = temp + '\n';
            output = output + "destination:" + strs[1] + '\n';
            output = output + '\n';
            output = output + "Returning " + bookName(2, strs.size(), strs) + " to " +
                     ch.getClient().findBookLender(bookName(2, strs.size(), strs), strs[1]) + '\n';
            output = output + '\0';
            ch.getClient().deleteBookInventory(bookName(2, strs.size(), strs), strs[1]);
        }

        if (strs[0] == "status") {
            string temp = "SEND";
            output = temp + '\n';
            output = output + "destination:" + strs[1] + '\n';
            output = output + '\n';
            output = output + "book status" + '\n';
            output = output + '\0';
        }
        if (strs[0] == "logout") {
            string temp = "DISCONNECT";
            output = temp + '\n';
            output = output + "receipt:" + to_string(ch.getClient().getReceipt()) + '\n';
            action *act;
            actionLogout actL(&ch);
            act = &actL;
            ch.getClient().insertReceiptAction(ch.getClient().getReceipt(), act);
            ch.getClient().updateReceipt();
            output = output + '\n';
            output = output + '\0';
            ch.setloggedIn(false);
        }
        ch.sendLine(output);
        strs.clear();
    }


}


string Keyboardinput::bookName(int start, int end, vector<string> all) {
    string name = "";
    for (unsigned i = start; i < (unsigned) end; i++) {
        name = name + all.at(i);
        if (i < (unsigned) end - 1)
            name = name + " ";
    }
    return name;
}

Keyboardinput::~Keyboardinput() {
}





