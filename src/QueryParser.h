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

    bool isNumber(string s) {
        regex num("[0-9]+");
        return regex_match(s, num);
    }

public:
    // Parse a query into a stack
    void parse(string query);

    int getIndexOfAttribute(vector<string>attributes, string attribute) {
        vector<string>::iterator it = find(attributes.begin(), attributes.end(), attribute);
        return it - attributes.begin();
    }

    // Run against a record using attributes for position
    bool eval(vector<string> attributes, Record *record, string expr) {
        stringstream stream(expr);
        bool result;
        bool isNot = false;
        string lhs;
        string rhs;

        // get the comparator (first level)
        string curr;
        while(stream.good()) {
            stream >> curr;
            if (curr == "AND") {
                while (stream.good()) {
                    stream >> curr;
                    rhs += curr + " ";
                }
                result = eval(attributes, record, lhs) && eval(attributes, record, rhs);
            }
            else if (curr == "OR") {
                while (stream.good()) {
                    stream >> curr;
                    rhs += curr + " ";
                }
                result = eval(attributes, record, rhs) || eval(attributes, record, rhs);
            }
            else
                lhs += curr + " ";
        }
        // clear the flags
        stream.clear();
        stream.seekg(0);

        while (stream.good()) {
            stream >> curr;
            if (curr == "NOT")
                isNot = true;
        }
        stream.clear();

        while(stream.good()) {
            stream >> curr;
            if (curr == ">") {
                while (stream.good()) {
                    stream >> curr;
                    rhs += curr + " ";
                }

            }
        }

        // if a comparator run eval on the lhs and rhs
        // return do comparator on the value of lhs, rhs
        if (isNot)
            return !result;
        else
            return result;
    }
};

#endif //DATABASE_QUERYPARSER_H
