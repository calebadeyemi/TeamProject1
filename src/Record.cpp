//
//  Record.cpp
//  
//
//  Created by Caleb Adeyemi on 2/13/19.
//

#include "Record.h"
#include <algorithm>

int Record::size(){
    return content.size();
}

Record::Record() {
}

Record::Record(int newRecordSize){
    content.resize(newRecordSize);
}

string Record::operator[](int i) const{
    return content[i];
}

string& Record::operator[](int i){
    return content[i];
}

void Record::deleteRecordAttribute(int index){
    content.erase(content.begin(), content.begin() + index);
}

void Record::addRecordAttribute(string attribute){
    content.push_back(attribute);
}

void Record::addRecordAttribute(){
    content.resize(content.size()+1);
}

string &Record::operator[](string attribute) {
    for (int i = 0; i < content.size() -1; i++) {
        if (content.at(i) == attribute) {
            return content.at(i);
        }
    }
}
