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

    void deleteAttribute(string attribute_name);
    void insertAttribute(string record);

    void addAttribute(string attribute_name);
    string getAttribute();
    string getSize ();

    string individualRecord(string record);
    string nameKey(string attribute_name);

    string crossJoin(string table1, string table2);
    string naturalJoin(string table1, string table2);
    string calculations(string attribute_name);

};


#endif //TABLE_TABLE_H

