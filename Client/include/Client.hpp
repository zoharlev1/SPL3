//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_CLIENT_HPP
#define ASSIGNMENT3CLIENT_CLIENT_HPP

#include <map>
#include <string>
#include <vector>
//#include <bits/unordered_map.h>
#include <unordered_map>

using namespace std;

#include "../include/Book.hpp"
#include "../include/action.hpp"


class Client {
private:
    string userName;
    string password;
    int subID;
    int receiptID;
    map<string, vector<Book>> inventory;
    vector<Book> lentBooks;
    vector<string> wishlist;
    vector<pair<int, action *>> receiptAct;
    map<string, int> subscriptionIdmap;


public:
    ~Client();

    Client(string username, string password);

    void deleteFromWishlist(string name);

    bool inWishlist(string bookname);

    void addToWishlist(string bookName);

    bool hasBook(string genre, string name);

    string getUserName();

    int getReceipt();

    void updateReceipt();

    void insertReceiptAction(int r, action *act);

    void actByReceipt(int receiptNum);

    void addBook(string genreName, string bookName, string lender);

    void lending(string genreName, string bookName);

    string genreGetBooks(string genreName);

    string findBookLender(string bookName, string genre);

    void insertSubId(string genre);

    int getSubId(string genre);

    void returnedBook(string name);

    void deleteBookInventory(string bookName, string des);

    void clearReceiptAct();
};

#endif //ASSIGNMENT3CLIENT_CLIENT_HPP
