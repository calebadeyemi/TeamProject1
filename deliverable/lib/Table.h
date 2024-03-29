//
// Created by Sausha-Rae Brown on 2/11/19.
//

#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "Record.h"


using namespace std;

class Table{

public:
    // Builds an empty table
    Table();

    // Builds a table with a list of attributes
    explicit Table(vector<string> attribute);

    // Adds an attribute to the table
    void addAttribute(string attribute);

    // Removes an attribute from the table
    void deleteAttribute(string attribute);

    // Adds a record
    void insert(Record record);

    // Gets a list of the attributes available
    vector<string> getAttributes();

    // Gets number of records
    int getSize();

    // Gets all records in a table
    vector<Record> getRecords();

    // Makes an attribute the key
    void makeKey(string attribute);

    // Cross joins two tables and returns the join table
    Table crossJoin(Table table1, Table table2);

    // Natural joins two tables and returns the join table
    Table naturalJoin(Table table1, Table table2);

    // Returns a count of non-null in your attribute
    int count(string attribute);

    // Returns index of min record
    int min(string attribute);

    // Returns index of max record
    int max(string attribute);
};

#endif //TABLE_TABLE_H
