//
// Created by orsmo@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "../include/Book.hpp"
#include <string>

using namespace std;

Book::Book(string givenName, string lender) : name(givenName), lender(lender) {}

string Book::getLender() {
    return lender;
}
