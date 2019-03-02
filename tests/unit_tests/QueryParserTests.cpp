//
// Created by Henning Futrell on 2019-02-28.
//

#include <string>
#include "gtest/gtest.h"
#include "QueryParser.h"

using namespace std;

TEST(QueryParserTests, ParsesSimpleQuery) {
    QueryParser parser;
    vector<string> attributes = {"that", "other", "new"};

    Record* r = new Record(2);
    r->operator[](0) = "5";
    r->operator[](1) = "blue";
    r->operator[](2) = "blue";

    string query1 = "that > 4 AND other = new";
    string query2 = "that < 4 AND other = new";
    ASSERT_TRUE(parser.eval(attributes, r, query1));
    ASSERT_FALSE(parser.eval(attributes, r, query1));
}
