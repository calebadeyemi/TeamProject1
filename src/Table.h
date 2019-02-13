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

private:


public:


    Table(vector<string> attribute);
    Table();

    void delete_attribute(string attribute_name);
    void insert_attribute(string record);

    void add_attribute(string attribute_name);
    string get_attribute();
    string get_size ();

    string individual_record(string record);
    string name_key(string attribute_name);

    string cross_join(string table1, string table2);
    string natural_join(string table1, string table2);
    string calculations(string attribute_name);

};


#endif //TABLE_TABLE_H

