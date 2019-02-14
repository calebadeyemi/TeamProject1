//
// Created by Sausha-Rae Brown on 2/11/19.
//


#include "Table.h"
#include "Record.h"

using namespace std;


Table::Table(vector<string> attribute) : Table() {
    for(int i =0 ; i < attribute.size(); ++i) {
        cout << attribute[i] << " ";
    }
    cout << "\n";
}

Table::Table(){
    cout << "empty table" << endl;
}

void Table::deleteAttribute(string attribute){
    cout << "deleted function called " << endl;

}


void Table::insert(Record record){
    cout << "inserts function called " << endl;
}

void Table::addAttribute(string attribute){
    cout << "add function called" << endl;
}

vector<string> Table::getAttributes(){
    cout << "get attribute function called" << endl;
    return vector<string>();
}

int Table::getSize(){
    cout << "get size function called" << endl;
    return 0;
}

vector<Record> Table::getRecords() {
    cout << "individual record function called" << endl;
    return vector<Record>();
}

void Table::makeKey(string attribute){
    cout << "this attribute is now a key for the table" << endl;
}

Table Table::crossJoin(Table table1, Table table2){
    cout << "one table is now produced" << endl;
    return Table();
}

Table Table::naturalJoin(Table table1, Table table2){
    cout << "one table is now produced but multiple things are checked before" << endl;
    return Table();
}

int Table::count(string attribute) {
    return 0;
}

int Table::min(string attribute) {
    return 0;
}

int Table::max(string attribute) {
    return 0;
}



