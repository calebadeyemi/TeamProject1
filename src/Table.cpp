//
// Created by Sausha-Rae Brown on 2/11/19.
//


#include "table.h"
using namespace std;


Table::Table(vector<string> attribute){
    for(int i =0 ; i < attribute.size(); ++i) {
        cout << attribute[i] << " ";
    }
    cout << "\n";
}

Table::Table(){
    cout << "empty table" << endl;
}

void Table::delete_attribute(string attribute_name){
    cout << "deleted function called " << endl;

}


void Table::insert_attribute(string record){
    cout << "inserts function called " << endl;
}

void Table::add_attribute(string attribute_name){
    cout << "add function called" << endl;
}

string Table::get_attribute(){
    cout << "get attribute function called" << endl;
    return "";
}

string Table::get_size (){
    cout << "get size function called" << endl;
    return "";
}

string Table::individual_record(string record){
    cout << "individual record function called" << endl;
    return "";
}

string Table::name_key(string attribute_name){
    cout << "this attribute is now a key for the table" << endl;
    return "";
}

string Table::cross_join(string table1, string table2){
    cout << "one table is now produced" << endl;
    return "";
}

string Table::natural_join(string table1, string table2){
    cout << "one table is now produced but multiple things are checked before" << endl;
    return "";
}

string Table::calculations(string attribute_name){
    cout << "count, min, and max calculated" << endl;
    return "";
}



