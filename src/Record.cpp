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

void Record::deleteAttribute(int index){
    content.erase(content.begin() + index);
}

void Record::addAttribute(string attribute){
    content.push_back(attribute);
}

void Record::addAttribute(){
    content.resize(content.size()+1);
}
