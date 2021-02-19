//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include <string>
#include <iostream>
#include <Client.hpp>


void Client::updateReceipt() {
    receiptID = receiptID + 1;
}

void Client::actByReceipt(int receiptNum) {
    for (unsigned i = 0; i < receiptAct.size(); ++i) {
        if (receiptAct[i].first == receiptNum) {
            receiptAct[i].second->act();
        }

    }
}


void Client::addBook(string genreName, string bookName, string lender) {
    map<string, vector<Book>>::iterator itr;
    itr = inventory.find(genreName);
    if (itr == inventory.end()) {
        vector<Book> temp;
        temp.push_back(Book(bookName, lender));
        inventory.insert({genreName, temp});
    } else {
        itr->second.push_back(Book(bookName, lender));
    }
}

void Client::insertReceiptAction(int r, action *act) {
    pair<int, action *> me = make_pair(r, act);
    receiptAct.push_back(me);
}

string Client::genreGetBooks(string genreName) {
    map<string, vector<Book>>::iterator itr;
    itr = inventory.find(genreName);
    string output = "";
    if (itr != inventory.end()) {
        for (unsigned i = 0; i < itr->second.size(); i++) {
            output = output + itr->second[i].name;
            if (i != itr->second.size() - 1)
                output = output + ",";
        }
        return output;
    }
    return output;
}

string Client::findBookLender(string bookName, string genre) {
    map<string, vector<Book>>::iterator itr;
    itr = inventory.find(genre);
    if (itr != inventory.end()) {
        for (unsigned i = 0; i < itr->second.size(); i++) {
            if (itr->second.at(i).name == bookName) {
                return itr->second.at(i).getLender();
            }
        }
    }
    for (unsigned i = 0; i < lentBooks.size(); i++) {
        if (lentBooks.at(i).name == bookName) {
            return lentBooks.at(i).getLender();
        }
    }
    return "";
}


void Client::addToWishlist(string bookName) {
    wishlist.push_back(bookName);
}

bool Client::hasBook(string genre, string name) {
    map<string, vector<Book>>::iterator itr;
    itr = inventory.find(genre);
    if (itr != inventory.end()) {
        for (unsigned i = 0; i < itr->second.size(); i++) {
            if (itr->second[i].name == name)
                return true;
        }
    }
    return false;
}

bool Client::inWishlist(string bookname) {
    for (unsigned i = 0; i < wishlist.size(); i++) {
        if (wishlist[i] == bookname)
            return true;
    }
    return false;
}

void Client::deleteFromWishlist(string name) {
    for (unsigned i = 0; i < wishlist.size(); i++) {
        if (wishlist[i] == name) {
            wishlist.erase(wishlist.begin() + i);
        }
    }
}

void Client::lending(string genre, string bookName) {
    map<string, vector<Book>>::iterator itr;
    itr = inventory.find(genre);
    if (itr != inventory.end()) {
        for (unsigned i = 0; i < itr->second.size(); i++) {
            if (itr->second[i].name == bookName) {
                Book toLend = itr->second[i];
                itr->second.erase(itr->second.begin() + i);
                lentBooks.push_back(toLend);
            }
        }
    }
}


Client::Client(string username, string password) : userName(username), password(password), subID(0), receiptID(1),
                                                   inventory(map<string, vector<Book>>()), lentBooks(vector<Book>()),
                                                   wishlist(vector<string>()),
                                                   receiptAct(vector<pair<int, action *>>()),
                                                   subscriptionIdmap(map<string, int>()) {
}

string Client::getUserName() {
    return userName;
}

int Client::getReceipt() {
    return receiptID;
}


void Client::insertSubId(string genre) {
    pair<string, int> x = make_pair(genre, subID);
    subscriptionIdmap.insert(x);
    subID = subID + 1;
}

int Client::getSubId(string genre) {
    return subscriptionIdmap.at(genre);
}

void Client::returnedBook(string name) {
    vector<Book>::iterator itr;
    for (unsigned i = 0; i < lentBooks.size(); i++) {
        if (lentBooks[i].name == name)
            lentBooks.erase(lentBooks.begin() + i);
    }
}

void Client::deleteBookInventory(string bookName, string des) {
    map<string, vector<Book>>::iterator itr;
    itr = inventory.find(des);
    if (itr != inventory.end()) {
        for (unsigned i = 0; i < itr->second.size(); i++) {
            if (itr->second[i].name == bookName) {
                itr->second.erase(itr->second.begin() + i);
            }
        }
    }
}

Client::~Client() {
    inventory.clear();
    lentBooks.clear();
    wishlist.clear();
    subscriptionIdmap.clear();

}




