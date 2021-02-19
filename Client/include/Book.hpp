//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef ASSIGNMENT3CLIENT_BOOK_HPP
#define ASSIGNMENT3CLIENT_BOOK_HPP

#include <string>

using namespace std;

class Book {
public:
    Book(string givenName, string lender);

    string name;

    string getLender();

private:
    string lender;


};


#endif //ASSIGNMENT3CLIENT_BOOK_HPP
