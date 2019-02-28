//
// Created by Sausha-Rae Brown on 2/11/19.
//


#include "Table.h"
#include "Record.h"
#include "DbError.h"
#include <algorithm>
#include <map>

using namespace std;


Table::Table(vector<string> attributes){
    Record r(attributes.size());

    for(int i=0; i < attributes.size(); i++){
        r[i] =  attributes.at(i);
    }
    records.push_back(r);
}

void Table::deleteAttribute(string attribute){
    // find the attribute's index
    int attrIndex = -1;
    for(int i = 0; i < records.at(0).size(); i++){
        if(records.at(0)[i] == attribute){
            attrIndex = i;
            records.erase(records.begin(), records.begin() + i);
            break;
        }
    }
    if (attrIndex < 0) {
        throw DbError("attempted to delete non existant attribute");
    }

    // delete attribute from all indexes
    for(int i = 0; i < records.size(); i++){
        records[i].deleteAttribute(attrIndex);
    }
}

void Table::insert(Record record){
    records.push_back(record);
}

void Table::addAttribute(string attribute){
    records.at(0).addAttribute(attribute);

    // increase size of all records
    for (auto &record : records) {
        record.addAttribute();
    }
}

vector<string> Table::getAttributes(){
    vector<string> attributes(records.at(0).size());
    for(int i=0; i < attributes.size(); ++i){
        attributes[i] = records.at(0)[i];
    }
    return attributes;
}

int Table::getSize(){
    return records.size();
}

vector<Record> Table::getRecords() {
    return records;
}

void Table::makeKey(string attribute){
    bool keySet = false;
    key = attribute;
    auto attributes = getAttributes();
    for(int i = 0; i < attributes.size(); i++) {
        if (attributes[i] == key) {
            keyIndex = i;
            keySet = true;
            break;
        }
    };
    if (!keySet) {
        throw DbError("attempted to set key on non existant attribute");
    }
}

string Table::getKey() {
    return key;
}

int Table::getKeyIndex() {
    return keyIndex;
}

Table Table::crossJoin(Table table1, Table table2){
    // Join the attribute lists
    vector<string> attributes;
    for(int i=0; i < table1.getAttributes().size(); i++){
        attributes.push_back(table1.getAttributes()[i]);
    }

    for(int j=0; j < table2.getAttributes().size(); j++){
        attributes.push_back(table1.getAttributes()[j]);
    }

    // Build new table
    Table t(attributes);

    // Cross join
    for(int i = 1; i < table1.getSize(); i++){
        for(int j = 1; j < table2.getSize(); j++){
            Record r(attributes.size());
            for(int k = 0; k < table1.getAttributes().size(); k++){
                r[k] = table1.getRecord(i)[k];
            }

            int offset = table1.getAttributes().size() - 1;
            for(int k = 0; k < table2.getAttributes().size(); k++){
                r[offset + k] = table2.getRecord(j)[k];
            }
            t.records.push_back(r);
        }
    }

    return t;
}

Table Table::naturalJoin(Table table1, Table table2){
    vector<string>::iterator it;
    if(table2.key.empty()){
        throw DbError("No key to natural join on.");
    };

    int matchIndex;
    try {
        matchIndex = table1.getAttributeIndex(table2.key);
    } catch (DbError e) {
        throw DbError("no matching index found to natural join");
    }

    Table joinedTable(table1.getAttributes());
    for (int i =0; i < table2.getAttributes().size(); i++) {
        if(i != table2.getKeyIndex()) {
            joinedTable.addAttribute(table2.getAttributes()[i]);
        }
    }

    int keyIndex = table2.getKeyIndex();
    map <string, Record> uniqueKeys;
    for(int i = 1; i < table2.getSize(); i++) {
        uniqueKeys[table2.getRecords().at(i)[keyIndex]] = table2.getRecords()[i];
    };

    for(int i = 1; i < table1.getRecords().size(); i++) {
        // rows that match in the map should be updated
        Record matchRecord = uniqueKeys.at(table1.getRecord(i)[matchIndex]);
        // if record was not found
        if (matchRecord.size() == 0) {
            continue;
        }
        else {
            Record newRecord(table1.getAttributes().size() + table2.getAttributes().size());
            for (int j = 0; j < table1.getAttributes().size(); j++) {
                newRecord[j] = table1.getRecord(i)[j];
            }

            for (int j = 0; j < matchRecord.size() - 1; j++) {
                if (j != keyIndex) {
                    // add the matching attributes to the other record
                    newRecord[table1.getAttributes().size() - 1 + j] = matchRecord[j];
                }
            }
            joinedTable.insert(newRecord);
        }
    }

    return joinedTable;
}

int Table::count(string attribute) {
    int index;
    int count;
    for(int i=0; i < getAttributes().size(); i++) {
        if (getAttributes()[i] == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < records.size(); j++){
        if(getRecord(j)[index] != " "){
            count++;
        }
    }
    return 0;
}

string Table::min(string attribute) {
    int index;
    vector<string> attributeVec;
    for(int i=0; i < getAttributes().size(); i++) {
        if (getRecord(0)[i] == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < records.size(); j++){
        attributeVec.push_back(records.at(j)[index]);
    }
    sort(attributeVec.begin(), attributeVec.end());
    return attributeVec.at(0);
}

string Table::max(string attribute) {
    int index;
    vector<string> attributeVec;
    for(int i=0; i < getAttributes().size(); i++) {
        if (records.at(0)[i] == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < records.size(); j++){
        attributeVec.push_back(getRecord(j)[index]);
    }
    sort(attributeVec.begin(), attributeVec.end());

    return attributeVec.at(attributeVec.size() - 1);
}

Record Table::getRecord(int i) {
    return records.at(i);
}

int Table::getAttributeIndex(string attribute) {
    auto attributes = getAttributes();
    bool found = false;
    for (int i = 0; i < attributes.size(); i++) {
        if (attributes.at(i) == attribute) {
            return i;
        }
    }
    if (!found) {
        throw DbError("index requested for non existent attribute");
    }
}
