//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <actionJoin.hpp>
#include "../include/ServerReader.hpp"


ServerReader::ServerReader(ConnectionHandler &CH) : ch(CH) {}

void ServerReader::read() {
    string message = "";

    while (ch.getloggedIn()) {

        message = "";
        ch.getLine(message);
        vector<string> strs;
        boost::split(strs, message, boost::is_any_of("\n"));

        int i = 0;
        if (strs[0].size() == 0) {
            i = 1;
        }
        if (strs.size() > 1) {
            strs[i] = strs[i].substr(0, strs[i].size() - 1);

            if (strs[i] == "ERROR") {
                //printing error message header
                cout << strs[i + 1] << endl;
            }
            if (strs[i] == "RECEIPT") {
                vector<string> receiptstring;
                boost::split(receiptstring, strs[i + 1], boost::is_any_of(":"));
                int recieptIdNum;
                std::istringstream(receiptstring[1]) >> recieptIdNum;
                ch.getClient().actByReceipt(recieptIdNum);
            }
            if (strs[i] == "MESSAGE") {
                //parsing message body
                vector<string> messageBodyVec;
                boost::split(messageBodyVec, strs[i + 4], boost::is_any_of(" "));
                vector<string> des;
                boost::split(des, strs[i + 3], boost::is_any_of(":"));

                string bookName;
                for (unsigned i = 5; i < messageBodyVec.size(); i++) {
                    bookName = bookName + messageBodyVec[i];
                    if (i < messageBodyVec.size() - 1) {
                        bookName = bookName + " ";
                    }
                }


                //asserting type of message
                if (messageBodyVec[0] == "Returning") {
                    if (messageBodyVec[messageBodyVec.size() - 1] == ch.getClient().getUserName()) {
                        string name = "";
                        for (unsigned i = 1; i < messageBodyVec.size() - 2; i++) {
                            name = name + messageBodyVec[i];
                            if (i < messageBodyVec.size() - 3) { name = name + " "; }

                        }

                        ch.getClient().addBook(des[1], name, ch.getClient().findBookLender(name, des[1]));
                        ch.getClient().returnedBook(name);
                    }

                } else if (messageBodyVec[0] == "Taking") {
                    bookName = messageBodyVec[1];
                    for (unsigned i = 2; i < messageBodyVec.size() - 2; i++)
                        bookName = bookName + " " + messageBodyVec[i];
                    if (messageBodyVec[messageBodyVec.size() - 1] == ch.getClient().getUserName()) {
                        ch.getClient().lending(des[1], bookName);
                    }
                } else {
                    vector<string> des;
                    boost::split(des, strs[4], boost::is_any_of(":"));
                    if (messageBodyVec.size() > 1) {
                        if (messageBodyVec[1] == "status") {
                            string output1 = "";
                            output1 = "SEND";
                            output1 = output1 + '\n';
                            output1 = output1 + "destination:" + des[1] + '\n';
                            output1 = output1 + '\n';
                            string books = ch.getClient().genreGetBooks(des[1]);
                            output1 = output1 + ch.getClient().getUserName() + ":" + books + '\n';
                            output1 = output1 + '\0';
                            ch.sendLine(output1);

                        } else if (messageBodyVec[1] == "wish") {
                            string bookName;
                            for (unsigned i = 4; i < messageBodyVec.size(); i++) {
                                bookName = bookName + messageBodyVec[i];
                                if (i < messageBodyVec.size() - 1) {
                                    bookName = bookName + " ";
                                }
                            }
                            if (ch.getClient().hasBook(des[1], bookName)) {
                                string output = "";
                                output = "SEND";
                                output = output + '\n';
                                output = output + "destination:" + des[1] + '\n';
                                output = output + ch.getClient().getUserName() + " has " + bookName + '\n';
                                output = output + '\0';
                                ch.sendLine(output);
                            }
                        } else if (messageBodyVec[1] == "has") {
                            if (messageBodyVec[2] != "added") {
                                string bookName;
                                for (unsigned i = 2; i < messageBodyVec.size(); i++) {
                                    bookName = bookName + messageBodyVec[i];
                                    if (i < messageBodyVec.size() - 1)
                                        bookName = bookName + " ";
                                }
                                if (ch.getClient().inWishlist(bookName)) {
                                    ch.getClient().addBook(des[1], bookName, messageBodyVec[0]);
                                    ch.getClient().deleteFromWishlist(bookName);
                                    string output = "";
                                    output = "SEND";
                                    output = output + '\n';
                                    output = output + "destination:" + des[1] + '\n';
                                    output = output + "Taking " + bookName + " from " + messageBodyVec[0] + '\n';
                                    output = output + '\0';
                                    ch.sendLine(output);
                                }
                            }

                        }
                    } else {
                        ///book status info that is returned, displaying to user
                        cout << messageBodyVec[0] << endl;
                    }

                }
            }
        }
        string message = "";
    }
}
