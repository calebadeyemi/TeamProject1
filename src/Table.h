//
// Created by Sausha-Rae Brown on 2/11/19.
//

#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Table{

public:


    Table(vector<string> attribute);
    Table();


    string getAttribute();
    string getSize ();
    string individualRecord(string record);

    void nameKey(string attribute_name);
    void crossJoin(string table1, string table2);
    void naturalJoin(string table1, string table2);
    void calculations(string attribute_name);
    void deleteAttribute(string attribute_name);
    void insertAttribute(string record);
    void addAttribute(string attribute_name);
};

#endif //TABLE_TABLE_H
