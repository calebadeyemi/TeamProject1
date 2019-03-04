//
// Created by Henning Futrell on 2019-02-28.
//

#ifndef DATABASE_QUERYPARSER_H
#define DATABASE_QUERYPARSER_H

#include <regex>
#include <sstream>
#include <algorithm>
#include "Record.h"

using namespace std;

class QueryParser {
    vector<string> left;
    vector<string> right;
    vector<char> comparisons;
    vector<bool> results;

public:
    int getIndexOfAttribute(vector<string>attributes, string attribute);

    // Run against a record using attributes for position
    bool eval(vector<string> attributes, Record *record, string expr);
};

#endif //DATABASE_QUERYPARSER_H
