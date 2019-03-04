//
// Created by Henning Futrell on 2019-02-28.
//

#include <string>
#include "gtest/gtest.h"
#include "QueryParser.h"

using namespace std;

TEST(QueryParserTests, ParsesSimpleQuery) {
    QueryParser parser;
    vector<string> attributes = {"that", "this", "other", "new", "extra"};

    Record* r = new Record(4);
    r->operator[](0) = "5";
    r->operator[](1) = "3";
    r->operator[](2) = "blue";
    r->operator[](3) = "blue";
    r->operator[](3) = "ocean";

    string query1 = "(that > 4 OR this = 3) AND other = blue";
    string query2 = "that < 4 AND NOT other = blue";
    string query3 = "(that < 4 OR this > 2) AND NOT (other = red)";

    ASSERT_TRUE(parser.eval(attributes, r, query1));
    ASSERT_TRUE(parser.eval(attributes, r, query3));
    ASSERT_FALSE(parser.eval(attributes, r, query2));
}

TEST(QueryParserTests, ParsesComplexQuery) {
    QueryParser parser;
    vector<string> attributes = {"that", "this", "other", "new", "extra"};

    Record* r = new Record(4);
    r->operator[](0) = "5";
    r->operator[](1) = "3";
    r->operator[](2) = "blue";
    r->operator[](3) = "blue";
    r->operator[](3) = "ocean";

    string query1 = "(that < 4 OR (this > 2 AND extra = ocean)) AND NOT other = red";

    ASSERT_TRUE(parser.eval(attributes, r, query1));
}
