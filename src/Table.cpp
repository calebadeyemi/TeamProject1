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

void Table::deleteAttribute(string attribute_name){
    cout << "deleted function called " << endl;

}


void Table::insertAttribute(string record){
    cout << "inserts function called " << endl;
}

void Table::addAttribute(string attribute_name){
    cout << "add function called" << endl;
}

string Table::getAttribute(){
    cout << "get attribute function called" << endl;
    return "";
}

string Table::getSize (){
    cout << "get size function called" << endl;
    return "";
}

string Table::individualRecord(string record){
    cout << "individual record function called" << endl;
    return "";
}

string Table::nameKey(string attribute_name){
    cout << "this attribute is now a key for the table" << endl;
    return "";
}

string Table::crossJoin(string table1, string table2){
    cout << "one table is now produced" << endl;
    return "";
}

string Table::naturalJoin(string table1, string table2){
    cout << "one table is now produced but multiple things are checked before" << endl;
    return "";
}

string Table::calculations(string attribute_name){
    cout << "count, min, and max calculated" << endl;
    return "";
}



