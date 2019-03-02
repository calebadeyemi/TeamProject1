//
// Created by Henning Futrell on 2019-02-28.
//

#include <regex>
#include "QueryParser.h"

void QueryParser::parse(string query) {
    string exp;
    vector<string> unevaled;

    //
    regex andR("(AND)");
    regex_replace(query, andR, "&");
}
