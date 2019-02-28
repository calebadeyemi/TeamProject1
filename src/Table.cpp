//
// Created by Sausha-Rae Brown on 2/11/19.
//

#include <map>
#include "Table.h"
#include "Record.h"
#include "DbError.h"


using namespace std;

Table::Table(vector<string> attributes){
    auto r = new Record(attributes.size());

    for(int i=0; i < attributes.size(); i++){
        r->operator[](i) =  attributes.at(i);
    }
    records.push_back(r);
}

void Table::deleteAttribute(string attribute){
    // find the attribute's index
    int attrIndex = -1;
    for(int i = 0; i < records.at(0)->size(); i++){
        if(getHeaderRecord()->operator[](i) == attribute){
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
        records[i]->deleteAttribute(attrIndex);
    }
}

void Table::insert(Record* record){
    records.push_back(record);
}

void Table::addAttribute(string attribute){
    getHeaderRecord()->addAttribute(attribute);

    // increase size of all records
    for (int i = 1; i < getSize(); i++) {
        getRecord(i)->addAttribute();
    }
}

vector<string> Table::getAttributes(){
    vector<string> attributes(getHeaderRecord()->size());
    for(int i=0; i < attributes.size(); ++i){
        attributes[i] = getHeaderRecord()->operator[](i);
    }
    return attributes;
}

int Table::getSize(){
    return records.size();
}

vector<Record*> Table::getRecords() {
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

Table* Table::crossJoin(Table* table1, Table* table2){
    // Join the attribute lists
    vector<string> attributes;
    for(int i=0; i < table1->getAttributes().size(); i++){
        attributes.push_back(table1->getAttributes()[i]);
    }

    for(int j=0; j < table2->getAttributes().size(); j++){
        attributes.push_back(table2->getAttributes()[j]);
    }

    // Build new table
    auto t = new Table(attributes);

    // Cross join
    for(int i = 1; i < table1->getSize(); i++){
        for(int j = 1; j < table2->getSize(); j++){
            auto r = new Record(attributes.size());
            for(int k = 0; k < table1->getAttributes().size(); k++){
                r->operator[](k) = table1->getRecord(i)->operator[](k);
            }

            int offset = table1->getAttributes().size();
            for(int k = 0; k < table2->getAttributes().size(); k++){
                r->operator[](offset + k) = table2->getRecord(j)->operator[](k);
            }
            t->records.push_back(r);
        }
    }

    return t;
}

Table* Table::naturalJoin(Table* table1, Table* table2){
    vector<string>::iterator it;
    if(table2->getKey().empty()){
        throw DbError("No key to natural join on.");
    };

    int matchIndex;
    try {
        matchIndex = table1->getAttributeIndex(table2->getKey());
    } catch (DbError e) {
        throw DbError("no matching index found to natural join");
    }

    auto joinedTable = new Table(table1->getAttributes());
    for (int i =0; i < table2->getAttributes().size(); i++) {
        if(i != table2->getKeyIndex()) {
            joinedTable->addAttribute(table2->getAttributes()[i]);
        }
    }

    int keyIndex = table2->getKeyIndex();
    map <string, Record*> uniqueKeys;
    for(int i = 1; i < table2->getSize(); i++) {
        uniqueKeys[table2->getRecords().at(i)->operator[](keyIndex)] = table2->getRecord(i);
    };

    for(int i = 1; i < table1->getRecords().size(); i++) {
        // rows that match in the map should be updated
        auto matchRecord = uniqueKeys.at(table1->getRecord(i)->operator[](matchIndex));
        // if a matching record was not found, skip
        if (!matchRecord) {
            continue;
        }
        else {
            auto newRecord = new Record(table1->getAttributes().size() + table2->getAttributes().size() - 1);
            int offset = table1->getAttributes().size();
            for (int j = 0; j < offset; j++) {
                newRecord->operator[](j) = table1->getRecord(i)->operator[](j);
            }

            for (int j = 0; j < matchRecord->size(); j++) {
                if (j != keyIndex) {
                    // add the matching attributes to the other record
                    newRecord->operator[](offset + j) = matchRecord->operator[](j);
                } else {
                    offset--;
                }
            }
            joinedTable->insert(newRecord);
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
        if(getRecord(j)->operator[](index) != " "){
            count++;
        }
    }
    return 0;
}

string Table::min(string attribute) {
    int index;
    vector<string> attributeVec;
    for(int i=0; i < getAttributes().size(); i++) {
        if (getHeaderRecord()->operator[](i) == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < records.size(); j++){
        attributeVec.push_back(getRecord(j)->operator[](index));
    }
    sort(attributeVec.begin(), attributeVec.end());
    return attributeVec.at(0);
}

string Table::max(string attribute) {
    int index;
    vector<string> attributeVec;
    for(int i=0; i < getAttributes().size(); i++) {
        if (getHeaderRecord()->operator[](i) == attribute){
            index = i;
            break;
        }
    }
    for(int j=1; j < records.size(); j++){
        attributeVec.push_back(getRecord(j)->operator[](index));
    }
    sort(attributeVec.begin(), attributeVec.end());

    return attributeVec.at(attributeVec.size() - 1);
}

Record* Table::getRecord(int i) {
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

Record* Table::getHeaderRecord() {
    return getRecord(0);
}
