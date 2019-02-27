//
// Created by Sausha-Rae Brown on 2/11/19.
//


#include "Table.h"
#include "Record.h"

using namespace std;


Table::Table(vector<string> attribute){
    Record r(attribute.size());

    for(int i=0; i < attribute.size(); i++){
        r[i] =  attribute.at(i);
        cout << r[i] << endl;
    }
    this->rows.push_back(r);
}

Table::Table(){

}

void Table::deleteAttribute(string attribute){
    int index;
    for(int i =0; i < rows.at(0).size(); i++){
        if(rows.at(0)[i] == attribute){
            index = i;
            rows.erase(rows.begin(), rows.begin() + i);
            break;
        }
    }
    for(int i =0; i < rows.size(); i++){
        rows[i].deleteRecordAttribute(index);

    }

}


void Table::insert(Record record){
    rows.push_back(record);
}

void Table::addAttribute(string attribute){
    rows.at(0).addRecordAttribute(attribute);
}

vector<string> Table::getAttributes(){
    vector<string> attributes;
    for(int i=0; i < rows.at(0).size(); ++i){
        attributes.push_back(rows.at(0)[i]);
    }
    return attributes;
}

int Table::getSize(){
    int size = rows.size()-1;
    return size;
}

Record Table::getRecords() {
    //return vector<Record>();
}

void Table::makeKey(string attribute){
    this->key = attribute;
}

Table Table::crossJoin(Table table, Table table2){

    vector<string> attributes;
    int index;

    int tableSize = table.rows.size();
    int table2Size = table2.rows.size();
    int newTableSize = (tableSize * table2Size) - 1;

    for(int i=0; i < table.rows.at(0).size(); i++){
        attributes.push_back(table.rows.at(0)[i]);
    }

    for(int j=0; j < table2.rows.at(0).size(); j++){
        attributes.push_back(table.rows.at(0)[j]);
    }

    Table t(attributes);

    for(int i=1; i < table.rows.size(); i++){
        for(int j=1; j < table2.rows.size(); j++){
            Record r(attributes.size());
            for(int k =0; k < table.rows.at(i).size(); k++){
                r[k] = table.rows.at(i)[k];
                index = k;
            }
            for(int k =0; k < table2.rows.at(j).size(); k++){
                r[index + k] = table2.rows.at(j)[k];
            }
            t.rows.push_back(r);
        }
    }


}

Table Table::naturalJoin(Table table, Table table2){


    cout << "one table is now produced but multiple things are checked before" << endl;
    return Table();
}

int Table::count(string attribute) {
    int index;
    int count;
    for(int i=0; i < rows.at(0).size(); i++) {
        if (rows.at(0)[i] == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < rows.size(); j++){
        if(rows.at(j)[index] != " "){
            count++;
        }
    }
    return 0;
}

string Table::min(string attribute) {
    int index;
    vector<string> attributeVec;
    for(int i=0; i < rows.at(0).size(); i++) {
        if (rows.at(0)[i] == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < rows.size(); j++){
        attributeVec.push_back(rows.at(j)[index]);
    }
    sort(attributeVec.begin(), attributeVec.end());
    return attributeVec.at(0);
}

string Table::max(string attribute) {
    int index;
    vector<string> attributeVec;
    for(int i=0; i < rows.at(0).size(); i++) {
        if (rows.at(0)[i] == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < rows.size(); j++){
        attributeVec.push_back(rows.at(j)[index]);
    }
    sort(attributeVec.begin(), attributeVec.end());

    return attributeVec.at(attributeVec.size() - 1);
}



