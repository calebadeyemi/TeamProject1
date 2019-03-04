//
// Created by Henning Futrell on 2019-02-28.
//

#include <regex>
#include "QueryParser.h"
int QueryParser::getIndexOfAttribute(vector<string>attributes, string attribute) {
    vector<string>::iterator it = find(attributes.begin(), attributes.end(), attribute);
    return it - attributes.begin();
}

// Run against a record using attributes for position
bool QueryParser::eval(vector<string> attributes, Record *record, string expr) {
    stringstream stream(expr);
    bool isFirstLevel = false;
    bool parenEvaled = false;
    bool result = false;
    string lhs;
    string rhs;
    regex lparen("^\\(.*");
    regex rparen(".*\\)");

    // get the comparator (first level)
    string curr;
    while(stream.good()) {
        curr = "";
        stream >> curr;
        if (regex_match(curr, lparen)) {
            isFirstLevel = true;
            parenEvaled = true;
            curr = curr.substr(1, curr.size());
            string inParen;
            while (!regex_match(curr, rparen)) {
                inParen += curr + " ";
                stream >> curr;
            }
            curr = curr.substr(0, curr.size() - 1);
            inParen += curr;
            result = eval(attributes, record, inParen);
        } else if (curr == "AND") {
            bool isNot;
            isFirstLevel = true;
            streampos preNot = stream.tellg();
            stream >> curr;
            if (curr == "NOT") {
                isNot = true;
            } else {
                stream.seekg(preNot);
            }
            while (stream.good()) {
                stream >> curr;
                rhs += curr + " ";
            }
            bool rhsEval =  eval(attributes,record, rhs);
            if (isNot) {
                rhsEval = !rhsEval;
            }
            if (parenEvaled) {
                result = result && rhsEval;
            } else {
                result = eval(attributes, record, lhs) && rhsEval;
            }
        } else if (curr == "OR") {
            bool isNot;
            isFirstLevel = true;
            streampos preNot = stream.tellg();
            stream >> curr;
            if(curr == "NOT") {
                isNot = true;
            } else {
                stream.seekg(preNot);
            }
            while (stream.good()) {
                stream >> curr;
                rhs += curr + " ";
            }
            bool rhsEval = eval(attributes, record, rhs);
            if (isNot) {
                rhsEval = !rhsEval;
            }
            if (parenEvaled) {
                result = result || rhsEval;
            } else {
                result = eval(attributes, record, lhs) || eval(attributes, record, rhs);
            }
        } else {
            lhs += curr + " ";
        }
    }
    // clear the flags
    stream.clear();
    stream.seekg(0);

    if (!isFirstLevel) {
        string comparator;
        stream >> lhs;
        stream >> comparator;
        stream >> rhs;
        lhs = record->operator[](getIndexOfAttribute(attributes, lhs));
        if (comparator == ">") {
            result = lhs > rhs;
        } else if (comparator == "<") {
            result = lhs < rhs;
        } else if (comparator == "=") {
            result = lhs == rhs;
        } else if (comparator == ">=") {
            result = lhs >= rhs;
        } else if (comparator == "<=") {
            result = lhs <= rhs;
        }
    }

    // if a comparator run eval on the lhs and rhs
    // return do comparator on the value of lhs, rhs
    return result;
};
